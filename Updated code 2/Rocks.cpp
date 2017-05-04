#include "Rocks.hpp"

Rocks::Rocks()
{
    base_pos = sf::Vector2f(0,0);
    offset = sf::Vector2f(7,7);
    counter = 0;
}

Rocks::~Rocks()
{
}

void Rocks::setBasePos(const::sf::Vector2f& base)
{
    base_pos = base;
}

void Rocks:: setNumOfRocks()
{
    rocks.resize(1);
}

void Rocks:: setRockPosition(const::sf::Vector2f& pos,sf::RenderWindow & window)
{
    int w_size_y = window.getSize().y;
    int number_y = w_size_y / 40;
    int r_y=35;
    
    int w_size_x=200;
    int number_x=w_size_x/10;
    int r_x=10;
    
    int w_size_z=0;
    int number_z=0;
    int r_z=0;
    
    for (int i = 0; i < rocks.size(); i++)
    {    if(rand()%2==0)
        {
            w_size_z=w_size_y;
            number_z=number_y;
            r_z=r_y;
        }
    else
        {
            w_size_z=w_size_x;
            number_z=number_x;
            r_z=r_x;
        }
            rocks[i].setEnemyPosition(sf::Vector2f(0, (rand()% number_z) * r_z));
    }
}

void Rocks::setRockOffset(const sf::Vector2f& o)
{
    offset = o;
}

void Rocks::setRockTexture(sf::Texture *pic)
{
    for (int i = 0; i < rocks.size(); i++)
        rocks[i].setEnemyTexture(pic);
}


bool Rocks::isRockHitByBullet(Player& p, Enemy& rock)
{
        for(int i = 0; i < p.getNumOfBullets(); i++)
            if(rock.getEnemyGlobalBounds().intersects(p.getProjectileGlobalBounds(i)))
            {
                counter++;
                p.eraseProjectile(i);
                return true;
            }
        return false;
}

void Rocks::createRockWave(Enemy& rock, int x,sf::RenderWindow &window)
{
    for(int i=0;i<x;i++)
    {
        rocks.push_back(rock);

        //rocks[i].setEnemyPosition(sf::Vector2f(0,rand()%500));

        
    }
}

void Rocks::moveRocks()
{
    for (int i = 0; i < rocks.size(); i++)
        rocks[i].move();
}

void Rocks::rotateRocks(float a)
{
    
    for (int i = 0; i < rocks.size(); i++)
        rocks[i].rotate(a);
}

int Rocks::getNumOfRocks() const
{
    return rocks.size();
}

const sf::Vector2f& Rocks::getBasePos() const
{
    return base_pos;
}

const sf::Vector2f& Rocks::getRockOffset() const
{
    return offset;
}

void Rocks::playerStatus(Player& player)
{
    for(int i = 0; i < rocks.size(); i++)
            if(rocks[i].isPlayerDead(player))
                player.killplayer();
}

void Rocks::eraseRock(Player& p)
{
    for (int i = 0; i < rocks.size(); i++)
        if(isRockHitByBullet(p, rocks[i]) && counter == 6)
        {
            rocks.erase(rocks.begin() + i);
            i--;
            counter=0;
        }
}

void Rocks::drawRockWave(sf::RenderWindow& window)
{
    for (int i = 0; i < rocks.size(); i++)
        rocks[i].drawEnemy(window);
}

bool Rocks::hasRockWaveEnded()
{
    return (rocks.size() == 0);
}
