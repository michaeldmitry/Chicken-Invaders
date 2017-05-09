#include "ChickenWave.hpp"

ChickenWave::ChickenWave()
{
    chick_anim_counter=0;
    base_pos=sf::Vector2f (100, 100);
    rate_eggs=150;
    score_counter = 0;
}

ChickenWave::~ChickenWave()
{
}

void ChickenWave::setNumOfChickens()
{
    chickens.resize(1);
}

void ChickenWave:: setRateEggs(int x)
{
    rate_eggs=x;
}

void ChickenWave::setBasePos(const sf::Vector2f& base)
{
    base_pos=base;
}

bool ChickenWave:: shouldDropEgg()
{
    return (rand() % rate_eggs == rand() % rate_eggs);
}

void ChickenWave:: dropChickenEggs (sf::RenderWindow& window)
{
    for(int i = 0; i < chickens.size(); i++)
        for(int j = 0; j < chickens[i].size(); j++)
            if(shouldDropEgg())
            {
                chickens[i][j].dropEgg(window);
            }
}

void ChickenWave:: setPickTexture(sf::Texture* a,sf::Texture* b, sf::Texture* c)
{
    pick_texture[0]=a;
    pick_texture[1]=b;
    pick_texture[2]=c;
}
void ChickenWave:: setPickScale(sf::Vector2f s)
{
    for(int i=0;i<pickup.size();i++)
        pickup[i].setPickupScale(s);
}

void ChickenWave:: setPickOffset(float a)
{
    pick_offset=a;
}

void ChickenWave:: movePickUp()
{
    for(int i=0; i<pickup.size();i++)
        pickup[i].move(10);
}

void ChickenWave:: dropPickUp(Enemy& enemy)
{
    if(rand() % 5 == 0){
        PickUp pickups;
        
        
        //pickup.setPickupTexture(&pick_texture);
        pickups.setPickupPosition(sf::Vector2f(enemy.getEnemyPosition().x + enemy.getEnemySize().x/3, enemy.getEnemyPosition().y + enemy.getEnemySize().y));
        int x=rand()%3;
        pickups.setPickupTexture(pick_texture[x]);
        pickups.setType(PickUp::options(x));
        pickups.setPickupScale(sf::Vector2f (0.5,0.5));
        
        pickup.push_back(pickups);
    }
}

void ChickenWave:: erasePickUp(sf::RenderWindow& window)
{
    for(int i=0;i<pickup.size();i++)
        if(pickup[i].getPickUpPosition().y > window.getSize().y)
        {
            pickup.erase(pickup.begin()+i);
            i--;
        }
}

void ChickenWave:: playerCollects(Player& player)
{
    for(int i=0; i<pickup.size();i++)
        if(pickup[i].getPickUpGlobalBounds().intersects(player.getPlayerGlobalBounds()))
        {
            score_counter+=20;
            switch (pickup[i].getType())
            {
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
void ChickenWave::setChickenPosition(const sf::Vector2f& pos)
{
    
    for(int i = 0; i < chickens.size(); i++)
    {
        for(int j = 0; j < chickens[i].size(); j++)
        {
            chickens[i][j].setEnemyPosition(sf::Vector2f(pos.x + (chickens[i][j].getEnemySize().x + 20) * j, pos.y + (chickens[i][j].getEnemySize().y + 10) * i));
        }
    }
    
}

bool ChickenWave::checkChickenBoundary( sf::RenderWindow& window, const Enemy& chicken)
{
    if(chicken.getEnemyOffset().x > 0 && chicken.getEnemyPosition().x + chicken.getEnemySize().x + 10 > window.getSize().x)
        return true;
    
    if(chicken.getEnemyOffset().x < 0 && chicken.getEnemyPosition().x - 10 < 0)
        return true;
    
    return false;
}

void ChickenWave:: keepChickBounds (sf::RenderWindow& window)
{
    for(int i = 0; i < chickens.size(); i++)
        if(chickens[i].size() > 0)
            if(checkChickenBoundary(window, chickens[i][0]) || checkChickenBoundary(window, chickens[i][chickens[i].size()-1]))
                for(int j = 0; j < chickens[i].size(); j++)
                    chickens[i][j].setEnemyOffset(sf::Vector2f(0, 0) - chickens[i][j].getEnemyOffset());
}

void ChickenWave:: moveChickens()
{
    for(int i = 0; i < chickens.size(); i++)
        for(int j = 0; j < chickens[i].size(); j++)
            chickens[i][j].move();
}

void ChickenWave::setChickenOffset(const sf::Vector2f& o)
{
    offset = o;
}

void ChickenWave::setChickenTexture(sf::Texture *pic)
{
    for (int i = 0; i < chickens.size(); i++)
        for (int j = 0; j < chickens[i].size(); j++)
            chickens[i][j].setEnemyTexture(pic);
}

void ChickenWave::setChickenTextureRect(const sf::IntRect& R)
{
    for (int i = 0; i < chickens.size(); i++)
        for (int j = 0; j < chickens[i].size(); j++)
            chickens[i][j].setEnemyTextureRect(R);
}

void ChickenWave:: setBackgroundTexture(sf::Texture* t)
{
    background.setTexture(*t);
    background.setPosition(0, 0);
}

void ChickenWave::changeChickenAnimation()
{
    chick_anim_counter= (chick_anim_counter +1) %3;
    sf::IntRect I(0, 69 * chick_anim_counter, 99,69);
    setChickenTextureRect(I);
    chick_anim_clk.restart();
}

void ChickenWave::drawChickenWave(sf::RenderWindow& window)
{
    window.draw(background);
    
    for(int i=0;i<chickens.size();i++)
        for(int j=0; j<chickens[i].size();j++)
            chickens[i][j].drawEnemy(window);
    
    for(int i=0;i<pickup.size();i++)
        pickup[i].drawPickup(window);
}

void ChickenWave:: createChickenWave(Enemy& enemy, int rows, int cols)
{
    chickens.resize(0);
    for(int i = 0; i < rows; i++)
    {
        vector<Enemy> f;
        for(int j = 0; j < cols; j++)
        {
            f.push_back(enemy);
            f[j].setEnemyPosition(sf::Vector2f(base_pos.x + (f[j].getEnemySize().x + 20) * j, base_pos.y + (f[j].getEnemySize().y + 10) * i));
        }
        chickens.push_back(f);
    }
}

int ChickenWave::getNumOfChickens()const
{
    return chickens.size();
}

int ChickenWave:: getRateEggs() const
{
    return rate_eggs;
}

const sf::Vector2f& ChickenWave::getChickenPosition() const
{
    for(int i = 0; i < chickens.size(); i++)
        for (int j = 0; j < chickens[i].size(); j++)
            return chickens[i][j].getEnemyPosition();
}

const sf::Vector2f& ChickenWave::getChickenOffset() const
{
    for(int i = 0; i < chickens.size(); i++)
        for (int j = 0; j < chickens[i].size(); j++)
            return chickens[i][j].getEnemyOffset();
}

const sf::Vector2f& ChickenWave::getBasePos() const
{
    return base_pos;
}

void ChickenWave:: playerStatus(Player& player, sf::RenderWindow& window)
{
    for(int i = 0; i < chickens.size(); i++)
        for (int j = 0; j < chickens[i].size(); j++)
            if(chickens[i][j].didEnemyOrProjectilesHitPlayer(player) && player_killed_clk.getElapsedTime().asSeconds() > 1 && player_immunity_clk.getElapsedTime().asSeconds() > 3)
            {
                if(player.getNumOfLives()>1)
                    player.decrementLives();
                else
                    player.killplayer();
                player_killed_clk.restart();
                
                player.setPlayerPosition(sf::Vector2f(window.getSize().x/2-player.getPlayerSize().x/2 ,window.getSize().y - player.getPlayerSize().y - 20));
                
            }
}

bool ChickenWave::isChickenHitByBullet(Player& p, Enemy& chicken)
{
    for(int i = 0; i < p.getNumOfBullets(); i++)
        for(int j=0; j<p.getNumOfBullets(i);j++)
            if(chicken.getEnemyGlobalBounds().intersects(p.getProjectileGlobalBounds(i, j)))
            {
                p.eraseProjectile(i, j);
                return true;
            }
    return false;
}

void ChickenWave::eraseChicken(Player& player)
{
    for (int i = 0; i < chickens.size(); i++)
        for(int j=0; j<chickens[i].size();j++)
            if (isChickenHitByBullet(player, chickens[i][j]))
            {
                score_counter+=50;
                dropPickUp(chickens[i][j]);
                chickens[i].erase(chickens[i].begin() + j);
                j--;
            }
}
bool ChickenWave::hasChickenWaveEndedbyDeath(Player &player)
{
    return player.isDead();
}


bool ChickenWave:: hasChickenWaveEndedNormally()
{
    
    for(int i = 0; i < chickens.size(); i++)
    {
        if(chickens[i].size() > 0)
        {
            return false;}
    }
    return true;
}
bool ChickenWave:: playChickenWave(sf::RenderWindow& window, Player& player, int& my_score)
{
    score_counter=my_score;
    
    
    sf::Music wave1_music;
    if (!wave1_music.openFromFile(resourcePath() + "Music_4.ogg"))
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
    
    
    sf::Clock clock;
    
    wave1_music.play();
    
    int n = 0;
    // Start the game loop
    while (window.isOpen()&&!hasChickenWaveEndedNormally()&&!hasChickenWaveEndedbyDeath(player))
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
        
        movePlayer(window, player);
        playerStatus(player, window);
        playerCollects(player);
        
        keepChickBounds(window);
        moveChickens();
        changeChickenAnimation();
        
        dropChickenEggs(window);
        eraseChicken(player);
        
        movePickUp();
        erasePickUp(window);
        
        // Clear screen
        window.clear();
        drawChickenWave(window);
        player.drawPlayer(window);
        
        
        window.draw(lives);
        window.draw(score);
       
        
        
        //if(hasChickenWaveEnded())
        // window.close();
        
        // Update the window
        window.display();
    }
    
    my_score=score_counter;
}

void ChickenWave:: movePlayer(sf::RenderWindow& window, Player& player)
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

int ChickenWave::returnScore()
{
    return score_counter;
}
