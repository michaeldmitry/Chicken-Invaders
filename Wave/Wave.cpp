#include "Wave.hpp"

Wave::Wave()
{
    chick_anim_counter=0;
}

Wave::~Wave()
{
}

void Wave::setNumOfChickens()
{
    chickens.resize(1);
}

void Wave::setChickenPosition(const sf::Vector2f& pos)
{
    
    for(int i = 0; i < chickens.size(); i++)
    {
        
        for(int j = 0; j < chickens[i].size(); j++)
        {
            chickens[i][j].setEnemyPosition(sf::Vector2f(pos.x + (chickens[i][j].getEnemySize().x + 20) * j, pos.y + (chickens[i][j].getEnemySize().y + 10) * i));
        }
    }

}

bool Wave::checkChickenBoundary( sf::RenderWindow& window, const Enemy& chicken)
{
    if(chicken.getEnemyOffset().x > 0 && chicken.getEnemyPosition().x + chicken.getEnemySize().x + 10 > window.getSize().x)
        return true;
    
    if(chicken.getEnemyOffset().x < 0 && chicken.getEnemyPosition().x - 10 < 0)
        return true;
    
    return false;
}

void Wave::setChickenOffset(const sf::Vector2f& o)
{
    offset = o;
}

void Wave::setChickenTexture(sf::Texture *pic)
{
    for (int i = 0; i < chickens.size(); i++)
        for (int j = 0; j < chickens[i].size(); j++)
            chickens[i][j].setEnemyTexture(pic);
}

void Wave::setChickenTextureRect(const sf::IntRect& R)
{
    for (int i = 0; i < chickens.size(); i++)
        for (int j = 0; j < chickens[i].size(); j++)
            chickens[i][j].setEnemyTextureRect(R);
}

void Wave::changeChickenAnimation()
{
    chick_anim_counter= (chick_anim_counter +1) %3;
    sf::IntRect I(0, 70 * chick_anim_counter, 99,70);
    setChickenTextureRect(I);
    chick_anim_clk.restart();
    
}

void Wave::drawWave(sf::RenderWindow& window)
{
    for(int i=0;i<chickens.size();i++)
        for(int j=0; j<chickens[i].size();j++)
            chickens[i][j].drawEnemy(window);
    
}

bool Wave::isChickenHitByBullet(Player& p, Enemy& e)
{
    for(int i = 0; i < p.getNumOfBullets(); i++)
        if(e.getEnemyGlobalBounds().intersects(p.getProjectileGlobalBounds(i)))
        {
            p.eraseProjectile(i);
            i--;
            return true;
        }
    return false;
}

void Wave::eraseChicken(Player& p)
{
    for (int i = 0; i < chickens.size(); i++)
        for (int j = 0; j < chickens[i].size(); j++)
        if (isChickenHitByBullet(p, chickens[i][j])==true)
        {
            chickens.erase(chickens.begin() + (i*j));
            i--;
        }
}

int Wave::getNumOfChickens()
{
    return chickens.size();
}

const sf::Vector2f& Wave::getChickenPosition()
{
    for(int i = 0; i < chickens.size(); i++)
        for (int j = 0; j < chickens[i].size(); j++)
            return chickens[i][j].getEnemyPosition();
}

const sf::Vector2f& Wave::getChickenOffset()
{
    for(int i = 0; i < chickens.size(); i++)
        for (int j = 0; j < chickens[i].size(); j++)
            return chickens[i][j].getEnemyOffset();
}
