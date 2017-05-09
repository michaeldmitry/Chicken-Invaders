//
//  RockWave.cpp
//  waves
//
//  Created by Nour Hesham on 5/6/17.
//  Copyright © 2017 Nour Ali 900160807. All rights reserved.
//

#include "RockWave.hpp"

RockWave::RockWave()
{
    base_pos = sf::Vector2f(0, 0);
    offset = sf::Vector2f(7, 7);
}

RockWave::~RockWave()
{
}

void RockWave::setBasePos(const::sf::Vector2f& base)
{
    base_pos = base;
}

void RockWave::setNumOfRocks()
{
    rocks.resize(1);
}
void RockWave::setRockScale()
{
    for (int i = 0; i < rocks.size(); i++)
    {
        int x=rand()%2+1;
        rocks[i].setEnemyScale(sf::Vector2f(x,x));
    }
}

void RockWave::setUp(sf::RenderWindow &window, Enemy &rock)
{
    rock.setEnemyPosition(sf::Vector2f(rand()% (window.getSize().x /3), -150));
}
void RockWave::setleft(sf::RenderWindow &window,Enemy &rock)
{
    rock.setEnemyPosition(sf::Vector2f(-150, rand() % int(window.getSize().y )));
}
void RockWave::setPosition(sf::RenderWindow &window, Enemy &enemy)
{
    if (rand() % 4 > 2)
        setUp(window, enemy);
    else
        setleft(window, enemy);
}

void RockWave::setRockOffset(const sf::Vector2f& o)
{
    offset = o;
}

void RockWave::setRockTexture(sf::Texture *pic)
{
    for (int i = 0; i < rocks.size(); i++)
        rocks[i].setEnemyTexture(pic);
}



bool RockWave::isRockHitByBullet(Player& p, Enemy& rock, int x)
{
    for (int i = 0; i < p.getNumOfBullets(); i++)
        for(int j=0; j<p.getNumOfBullets(i);j++)
            if (rock.getEnemyGlobalBounds().intersects(p.getProjectileGlobalBounds(i,j)))
            {
                counter[x]++;
                p.eraseProjectile(i, j);
                return true;
            }
    return false;
}

void RockWave::createRockWave(Enemy& rock, int x, sf::RenderWindow& window)
{
    for (int i = 0; i<x; i++)
    {
        
        rocks.push_back(rock);
        hasRockMoved.push_back(false);
        counter.push_back(0);
        setPosition(window, rocks[i]);
        
        
    }
}


void RockWave::moveRocks(sf::Vector2f x)
{
    for (int i = 0; i < rocks.size(); i++)
        if (hasRockMoved[i])
            rocks[i].move(x);
}


int RockWave::getNumOfRocks() const
{
    return rocks.size();
}

const sf::Vector2f& RockWave::getBasePos() const
{
    return base_pos;
}

const sf::Vector2f& RockWave::getRockOffset() const
{
    return offset;
}

void RockWave::playerStatus(Player& player,sf::RenderWindow &window)
{
    for (int i = 0; i < rocks.size(); i++)
        if (hasRockMoved[i])
            if (rocks[i].didEnemyOrProjectilesHitPlayer(player)&& player_killed_clk.getElapsedTime().asSeconds() > 1 && player_immunity_clk.getElapsedTime().asSeconds() > 3)
                
            {
                if(player.getNumOfLives()>1)
                    player.decrementLives();
                else
                    player.killplayer();
                player_killed_clk.restart();
                
                player.setPlayerPosition(sf::Vector2f(window.getSize().x/2-player.getPlayerSize().x/2 ,window.getSize().y - player.getPlayerSize().y - 20));
                
            }
}

void RockWave::eraseRock(Player& p)
{
    for (int i = 0; i < rocks.size(); i++)
        if (hasRockMoved[i] && isRockHitByBullet(p, rocks[i],i) && counter[i] == 5)
        {
            score_counter+=100;
            rocks.erase(rocks.begin() + i);
            counter.erase(counter.begin() + i);
            hasRockMoved.erase(hasRockMoved.begin() + i);
            i--;
        }
}

void RockWave::drawRockWave(sf::RenderWindow& window)
{
    for (int i = 0; i < rocks.size(); i++)
    {
        
        if (rand()%100==rand()%100)
        {
            hasRockMoved[i] = true;
            if (rocks[i].getEnemyPosition().x < 0)
                rocks[i].move(sf::Vector2f(140, 0));
            if (rocks[i].getEnemyPosition().y < 0)
                rocks[i].move(sf::Vector2f(0, 140));
        }
        if (hasRockMoved[i])
        {
            rocks[i].drawEnemy(window);
            
        }
        
        if (rocks[i].getEnemyPosition().y >window.getSize().y){
            rocks.erase(rocks.begin() + i);
            counter.erase(counter.begin() + i);
            hasRockMoved.erase(hasRockMoved.begin() + i);
            i--;
        }
        
    }
}
bool RockWave::hasRockWaveEndedNormally()
{
    return rocks.size()==0;
}
bool RockWave::hasRockWaveEndedbyDeath(Player& p)
{
    return p.isDead();
}
void RockWave::setRockTextureRect(const sf::IntRect& R)
{
    for (int i = 0; i < rocks.size(); i++)
        rocks[i].setEnemyTextureRect(R);
}

void RockWave::changRockAnimation()
{
    rock_anim_counter = (rock_anim_counter + 1) % 4;
    sf::IntRect I(rock_anim_counter*59, 0 , 59, 54);
    if (Rock_anim_clk.getElapsedTime().asSeconds() > 0.125)
    {
        setRockTextureRect(I);
        Rock_anim_clk.restart();
    }
}
void RockWave::playRockWave(sf::RenderWindow &window, Player& player, int& my_score)
{
    score_counter = my_score;
    
    sf::Music wave2_music;
    if (!wave2_music.openFromFile(resourcePath() + "Music_5.ogg"))
        return EXIT_FAILURE;

    sf::Font font;
    if(!font.loadFromFile(resourcePath() + "font.ttf"))
        return EXIT_FAILURE;
    
    sf::Text lives;
    lives.setFont(font);
    lives.setFillColor(sf::Color::White);
    lives.setCharacterSize(25);
    lives.setPosition(0,0);
    
    sf::Text score;
    score.setFont(font);
    score.setFillColor(sf::Color::White);
    score.setCharacterSize(25);
    score.setPosition(100, 0);
    
    
    wave2_music.play();   
    
    while (window.isOpen()&&!hasRockWaveEndedNormally() && !hasRockWaveEndedbyDeath(player))
    {
        lives.setString("Lives: " + to_string(player.getNumOfLives()));
        score.setString("Score: " + to_string(score_counter));
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        playerMove(player, window);
        changRockAnimation();
        moveRocks(sf::Vector2f(2, 2));
        eraseRock(player);
        playerStatus(player,window);
        
        
        // Clear screen
        window.clear();
        window.draw(background);
        player.drawPlayer(window);
        
        window.draw(lives);
        window.draw(score);
        
        drawRockWave(window);
        // Update the window
        window.display();
    }
    
    my_score = score_counter;
}
void RockWave::playerMove(Player &player,sf::RenderWindow &window)
{
    sf::SoundBuffer buffer_laser;
    buffer_laser.loadFromFile(resourcePath() + "Laser.ogg");
    
    sf::Sound sound_laser;
    sound_laser.setBuffer(buffer_laser);
    
    player.setPlayerTextureRect(sf::IntRect(38, 0, 38, 35));
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.setPlayerTextureRect(sf::IntRect(76, 0, 38, 49));
        
        player.moveX(window, 15);
        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.setPlayerTextureRect(sf::IntRect(0, 0, 38, 49));
        
        player.moveX(window, -15);
        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        player.setPlayerTextureRect(sf::IntRect(38, 0, 38, 49));
        player.moveY(window, -15);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        player.moveY(window, 15);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        player.fire();
    }
}
void RockWave::setWaveBackground(sf::Texture *t)
{
    background.setTexture(*t);
    background.setPosition(0, 0);
}

int RockWave::returnScore()
{
    return score_counter ;
}
