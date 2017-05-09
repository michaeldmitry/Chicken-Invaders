#include "BeastWave.hpp"

BeastWave::BeastWave()
{
    counter.resize(0);
    x_size = 0;
    y_size = 0;
    numOfSprites = 2;
    beast_anim_counter = 0;
    rate_eggs = 100;
    dead=false;
    score_counter = 0;
}

BeastWave::~BeastWave()
{
}

void BeastWave::setNumOfBeasts()
{
    beast.resize(1);
    counter.push_back(0);
}

void BeastWave::setBeastPosition(const sf::Vector2f& pos, int i)
{
    if(i < beast.size() && i >= 0)
        beast[i].setEnemyPosition(pos);
}

void BeastWave::setBeastPosition(float pos_x, float pos_y, int i)
{
    if (i < beast.size() && i >= 0)
        beast[i].setEnemyPosition(sf::Vector2f(pos_x, pos_y));
}
void BeastWave::setBeastOffset(const sf::Vector2f& o)
{
    offset = o;
}

void BeastWave::setBeastTexture(sf::Texture* pic, int i)
{
    if(i < beast.size() && i >= 0)
        beast[i].setEnemyTexture(pic);
}

void BeastWave::setBeastScale(const sf::Vector2f& scale, int i)
{
    if(i < beast.size() && i >= 0)
        beast[i]. setEnemyScale(scale);
}


void BeastWave::setBeastTextureRect(const sf::IntRect& R)
{
    for (int i = 0; i < beast.size(); i++)
        beast[i].setEnemyTextureRect(R);
}

void BeastWave::changeBeastAnimation()
{
    if(beast_anim_clk.getElapsedTime().asSeconds() > 0.2){
        beast_anim_counter = (beast_anim_counter +1) % numOfSprites;
        sf::IntRect I(0, y_size * beast_anim_counter, x_size, y_size);
        setBeastTextureRect(I);
        beast_anim_clk.restart();
    }
    
}

void BeastWave::setX_size(int x)
{
    x_size = x;
}

void BeastWave::setY_size(int y)
{
    y_size = y;
}

void BeastWave::setNumOfSprites(int num)
{
    numOfSprites = num;
}

bool BeastWave::isBeastHit(Player& p, int x)
{
    for(int i = 0; i < p.getNumOfBullets(); i++)
        for(int j=0;j<p.getNumOfBullets(i); j++)
            if(beast[x].getEnemyGlobalBounds().intersects(p.getProjectileGlobalBounds(i, j)))
            {
                counter[x]++;
                p.eraseProjectile(i,j);
                return true;
            }
    return false;
}

void BeastWave::eraseBeast(Player& p)
{
    for (int i = 0; i < beast.size(); i++)
    {//if(i<beast.size()&&i<counter.size())
        if (isBeastHit(p, i) && counter[i] == 25)
        {
            score_counter+=100;
            counter.erase(counter.begin() + i);
            beast.erase(beast.begin() + i);
            dead=true;
            
        }
    }
    
}
void BeastWave::drawBeast(sf::RenderWindow& window)
{
    if(!dead)
    {
        for (int i = 0; i < beast.size(); i++)
        { beast[i].drawEnemy(window);
            //
            cout<<beast.size()<<endl;
        }
        for (int i = 0; i < eggs.size(); i++)
        {
            eggs[i].drawProjectile(window);
            
        }
        for(int i=0;i<pickup.size();i++)
            pickup[i].drawPickup(window);
        
    }
}

void BeastWave::setProjOffset(const sf::Vector2f& o)
{
    proj_offset = o;
}
void BeastWave:: setProjColor(const sf::Color& col)
{
    proj_color=col;
}
void BeastWave:: setProjSize(const sf::Vector2f& s)
{
    proj_size=s;
}
void BeastWave::setProjStartingOffset(sf::Vector2f& s)
{
    proj_startingOffset=s;
}

void BeastWave::setProjTexture(sf::Texture* pic)
{
    proj_texture = pic;
}

bool BeastWave:: shouldDropEgg()
{
    return (rand() % rate_eggs == rand() % rate_eggs);
}

void BeastWave::dropEgg(sf::RenderWindow& window, int i)
{
    Projectile egg;
    
    //  egg.setProjectileColor(proj_color);
    egg.setProjectileTexture(proj_texture);
    egg.setProjectileOffset(proj_offset);
    egg.setProjectileSize(proj_size);
    egg.setProjectilePosition(sf::Vector2f(getBeastPosition(i).x + proj_startingOffset.x, getBeastPosition(i).y + proj_startingOffset.y));
    
    egg.fire();
    eggs.push_back(egg);
}

void BeastWave:: dropBeastEggs (sf::RenderWindow& window)
{
    for(int i = 0; i < beast.size(); i++)
        if(shouldDropEgg()&& dead==false)
        {
            dropEgg(window, i);
        }
    if(rand()%750==rand()%750)
    {
        dropPickUp();
    }
}
bool BeastWave::didEnemyOrProjectilesHitPlayer(Player& p)
{
    for (int i = 0; i < eggs.size(); i++)
        if (eggs[i].getProjectileGlobalBounds().intersects(p.getPlayerGlobalBounds())&& player_killed_clk.getElapsedTime().asSeconds() > 1 )
        {
            eggs.erase(eggs.begin() + i);
            player_killed_clk.restart();
            cout <<"egg hit player" << endl;
            // p.decrementLives();
            return true;
        }
    for (int i = 0; i < beast.size(); i++)
        if(p.getPlayerGlobalBounds().intersects(getBeastGlobalBounds(i)))
            return true;
    
    return false;
}


void BeastWave::move(int i, sf::RenderWindow& window)
{
    if(beast_move_clk.getElapsedTime().asSeconds() > 1){
        int difference_x(0), difference_y(0);
        int num;
        
        switch(rand() % 4){
            case 0:
                num = int(beast[i].getEnemyPosition().y - 20);
                if(num < 1)
                    num = 1;
                if(num > 200)
                    num = num / 2;
                difference_y = 0 -  rand() % num;
                break;
            case 1:
                num = int(window.getSize().y - beast[i].getEnemyPosition().y - beast[i].getEnemySize().y - 20);
                if (num < 1)
                    num = 1;
                if(num > 200)
                    num = num / 2;
                difference_y = rand() % num;
                break;
            case 2:
                num = int(beast[i].getEnemyPosition().x - 20);
                if (num < 1)
                    num = 1;
                if(num > 200)
                    num = num / 2;
                difference_x = 0 - num;
                break;
            case 3:
                num = int(window.getSize().x - beast[i].getEnemyPosition().x - beast[i].getEnemySize().x - 20);
                if (num < 1)
                    num = 1;
                if(num > 200)
                    num = num / 2;
                difference_x = rand() % num;
                break;
        }
        
        beast_move_clk.restart();
        
        beast[i].move(sf::Vector2f(difference_x, difference_y));
    }
    
}

const sf::Vector2f& BeastWave::getBeastPosition(int i)
{
    if (i < beast.size() && i >= 0)
        return beast[i].getEnemyPosition();
    else
        sf::Vector2f(10000, 10000);
}

sf::Vector2f BeastWave::getBeastSize(int i)
{
    return beast[i].getEnemySize();
}

bool BeastWave::isPlayerDead(Player& p)
{
    
    for(int i = 0; i < beast.size(); i++)
        if(p.getPlayerGlobalBounds().intersects(getBeastGlobalBounds(i)))
            return true;
    
    return false;
}

void BeastWave::killPlayer(Player& p)
{
    if (isPlayerDead(p))
    {
        //p.killplayer();
        p.decrementLives();
    }
}

void BeastWave::eraseProj(int i)
{
    if(i < eggs.size() && i >= 0)
        eggs.erase(eggs.begin() + i);
}

sf::FloatRect BeastWave::getBeastGlobalBounds(int i)
{
    return beast[i].getEnemyGlobalBounds();
}
bool BeastWave:: hasBeastWaveEndedNormally()
{
    return beast.size()==0;
}

bool BeastWave::hasBeastWaveEndedbyDeath(Player& p)
{
    return p.isDead();
}

void BeastWave::playBeastWave(Player& player, sf::RenderWindow &window, int& my_score)
{
    score_counter=my_score;
    
    sf::Music wave3_music;
    if (!wave3_music.openFromFile(resourcePath() + "Music_6.ogg"))
        return EXIT_FAILURE;

    
    sf::Font font;
    if(!font.loadFromFile(resourcePath() + "font.ttf"))
        return EXIT_FAILURE;
    
    sf::Text lives;
    lives.setFont(font);
    lives.setFillColor(sf::Color::White);
    lives.setCharacterSize(25);
    lives.setPosition(0,0);
    
    //cout<<player.getNumOfLives()<<endl;
    sf::Text score;
    score.setFont(font);
    score.setFillColor(sf::Color::White);
    score.setCharacterSize(25);
    score.setPosition(100, 0);
    
    
    wave3_music.play();
    
    while (window.isOpen() &&
           !hasBeastWaveEndedbyDeath(player) &&
           !hasBeastWaveEndedNormally())
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
            //player.eraseProjectile(p);
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        movePlayer(player, window);
        playerStatus(player, window);
        playerCollects(player);
        
        move(0, window);
        eraseBeast(player);
        
        killPlayer(player);
        
        dropBeastEggs(window);
        movePickUp();
        erasePickUp(window);
        
        // Clear screen
        window.clear();
        
        window.draw(background);
        player.drawPlayer(window);
        changeBeastAnimation();
        drawBeast(window);
        
        window.draw(lives);
        window.draw(score);
        
        // Update the window
        window.display();
    }
    
    my_score=score_counter;
    
}

void BeastWave::movePlayer(Player &player, sf::RenderWindow& window)
{
    sf::SoundBuffer buffer_laser;
    buffer_laser.loadFromFile(resourcePath() + "Laser.ogg");
    
    sf::Sound sound_laser;
    sound_laser.setBuffer(buffer_laser);
    
    player.setPlayerTextureRect(sf::IntRect(38, 0, 38, 35));
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.moveX(window, 15);
        player.setPlayerTextureRect(sf::IntRect(76, 0, 38, 49));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.moveX(window,-15);
        player.setPlayerTextureRect(sf::IntRect(0, 0, 38, 49));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        player.moveY(window,-15);
        player.setPlayerTextureRect(sf::IntRect(38, 0, 38, 49));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        player.moveY(window,15);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        sound_laser.play();
        player.fire();
    }
}
void BeastWave::setWaveBackground(sf::Texture *t)
{
    background.setTexture(*t);
    background.setPosition(0,0);
    
}

void BeastWave:: setPickTexture(sf::Texture* a,sf::Texture* b, sf::Texture* c)
{
    pick_texture[0]=a;
    pick_texture[1]=b;
    pick_texture[2]=c;
}
void BeastWave:: setPickScale(sf::Vector2f s)
{
    for(int i=0;i<pickup.size();i++)
        pickup[i].setPickupScale(s);
}

void BeastWave:: setPickOffset(float a)
{
    pick_offset=a;
}

void BeastWave:: movePickUp()
{
    for(int i=0; i<pickup.size();i++)
        pickup[i].move(10);
}

void BeastWave:: dropPickUp()
{
    int i=0;
    //if(rand() % 5 == 0)
    {
        PickUp pickups;
        
        
        //pickup.setPickupTexture(&pick_texture);
        pickups.setPickupPosition(sf::Vector2f(getBeastPosition(i).x + getBeastSize(i).x/3, getBeastPosition(i).y + getBeastSize(i).y));
        
        int x=rand()%3;
        pickups.setPickupTexture(pick_texture[x]);
        pickups.setType(PickUp::options(x));
        pickups.setPickupScale(sf::Vector2f (0.5,0.5));
        
        pickup.push_back(pickups);
    }
}

void BeastWave:: erasePickUp(sf::RenderWindow& window)
{
    for(int i=0;i<pickup.size();i++)
        if(pickup[i].getPickUpPosition().y > window.getSize().y)
        {
            pickup.erase(pickup.begin()+i);
            i--;
        }
}

void BeastWave:: playerCollects(Player& player)
{
    for(int i=0; i<pickup.size();i++)
        if(pickup[i].getPickUpGlobalBounds().intersects(player.getPlayerGlobalBounds()))
        {
            switch (pickup[i].getType())
            {
                    score_counter+=20;
                case PickUp::incrementLives:
                    player.incrementLives();
                    break;
                case PickUp::incrementBullets:
                    player.incrementBullets();
                    break;
                case PickUp::immunity:
                    player_immunity_clk.restart();
                    
                    break;
            }
            pickup.erase(pickup.begin()+i);
            i--;
        }
}
void BeastWave:: playerStatus(Player& player, sf::RenderWindow& window)
{
    //for(int i = 0; i < beast.size(); i++)&& d
    if(didEnemyOrProjectilesHitPlayer(player) && player_immunity_clk.getElapsedTime().asSeconds() > 3 && player_killed_clk.getElapsedTime().asSeconds() > 1)
    {
        player.setPlayerPosition(sf::Vector2f(window.getSize().x/2 - player.getPlayerSize().x/2 ,window.getSize().y - player.getPlayerSize().y - 20));
        
        player.decrementLives();
        
        player_killed_clk.restart();

    }
}

int BeastWave::returnScore()
{
    return score_counter;
}
