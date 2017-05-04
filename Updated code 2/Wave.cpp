#include "Wave.hpp"

Wave::Wave()
{
    chick_anim_counter=0;
    base_pos=sf::Vector2f (100, 100);
    rate_eggs=150;
}

Wave::~Wave()
{
}

void Wave::setNumOfChickens()
{
    chickens.resize(1);
}
void Wave:: setRateEggs(int x)
{
    rate_eggs=x;
}

void Wave::setBasePos(const sf::Vector2f& base)
{
    base_pos=base;
}

bool Wave:: shouldDropEgg()
{
    return (rand() % rate_eggs == rand() % rate_eggs);
}

void Wave:: dropChickenEggs (sf::RenderWindow& window)
{
    for(int i = 0; i < chickens.size(); i++)
        for(int j = 0; j < chickens[i].size(); j++)
            if(shouldDropEgg())
            {
                chickens[i][j].dropEgg(window);
            }
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

void Wave:: keepChickBounds (sf::RenderWindow& window)
{
    for(int i = 0; i < chickens.size(); i++)
        if(chickens[i].size() > 0)
            if(checkChickenBoundary(window, chickens[i][0]) || checkChickenBoundary(window, chickens[i][chickens[i].size()-1]))
                for(int j = 0; j < chickens[i].size(); j++)
                    chickens[i][j].setEnemyOffset(sf::Vector2f(0, 0) - chickens[i][j].getEnemyOffset());
}

void Wave:: moveChickens()
{
    for(int i = 0; i < chickens.size(); i++)
        for(int j = 0; j < chickens[i].size(); j++)
            chickens[i][j].move();
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

void Wave::drawChickenWave(sf::RenderWindow& window)
{
    for(int i=0;i<chickens.size();i++)
        for(int j=0; j<chickens[i].size();j++)
            chickens[i][j].drawEnemy(window);
    
}

void Wave:: createChickenWave(Enemy& enemy, int rows, int cols)
{
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

int Wave::getNumOfChickens()const
{
    return chickens.size();
}

int Wave:: getRateEggs() const
{
    return rate_eggs;
}

const sf::Vector2f& Wave::getChickenPosition() const
{
    for(int i = 0; i < chickens.size(); i++)
        for (int j = 0; j < chickens[i].size(); j++)
            return chickens[i][j].getEnemyPosition();
}

const sf::Vector2f& Wave::getChickenOffset() const
{
    for(int i = 0; i < chickens.size(); i++)
        for (int j = 0; j < chickens[i].size(); j++)
            return chickens[i][j].getEnemyOffset();
}

const sf::Vector2f& Wave::getBasePos() const
{
    return base_pos;
}

void Wave:: playerStatus(Player& player)
{
    for(int i = 0; i < chickens.size(); i++)
        for (int j = 0; j < chickens[i].size(); j++)
            if(chickens[i][j].isPlayerDead(player))
                    player.killplayer();
}

bool Wave::isChickenHitByBullet(Player& p, Enemy& chicken)
{
    for(int i = 0; i < p.getNumOfBullets(); i++)
        if(chicken.getEnemyGlobalBounds().intersects(p.getProjectileGlobalBounds(i)))
        {
            p.eraseProjectile(i);
            return true;
        }
    return false;
}

void Wave::eraseChicken(Player& player)
{
    for (int i = 0; i < chickens.size(); i++)
        for(int j=0; j<chickens[i].size();j++)
            if (isChickenHitByBullet(player, chickens[i][j]))
            {
                chickens[i].erase(chickens[i].begin() + j);
                j--;
            }
}

bool Wave:: hasChickenWaveEnded()
{
      return  (chickens.size()*chickens[0].size()==0);
}
