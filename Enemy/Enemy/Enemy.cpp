#include "Enemy.hpp"
#include "ResourcePath.hpp"
#include <iostream>

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

Enemy::Enemy(const sf::Vector2f& f,const sf::Vector2f& pos,sf::Color col)
{
    setEnemyScale(f);
    setEnemyPosition(pos);
    setEnemyColor(col);
}

void Enemy::setEnemyScale(const sf::Vector2f& f)
{
    chicken.setScale(f);
}

void Enemy::setEnemyPosition(const sf::Vector2f& pos)
{
    chicken.setPosition(pos);
}

void Enemy::setEnemyColor(const sf::Color& col)
{
    chicken.setColor(col);
}

void Enemy::setEnemyTexture(const sf::Texture* pic)
{
    chicken.setTexture(*pic);
}
void Enemy::setProjTexture(sf::Texture* pic)
{
    proj_texture = pic;
}


void Enemy::setEnemyTextureRect(const sf::IntRect& R)
{
    chicken.setTextureRect(R);
}

void Enemy::setEnemyOffset(const sf::Vector2f& o)
{
    offset = o;
}

const sf::Vector2f& Enemy::getEnemyOffset() const
{
    return offset;
}
void Enemy::setProjOffset(const sf::Vector2f& o)
{
    proj_offset = o;
}
void Enemy:: setProjColor(const sf::Color& col)
{
    proj_color=col;
}
void Enemy:: setProjSize(const sf::Vector2f& s)
{
    proj_size=s;
}
void Enemy::setProjStartingOffset(sf::Vector2f& s)
{
    proj_startingOffset=s;
}
void Enemy::drawEnemy(sf::RenderWindow& window)
{
    window.draw(chicken);
    for(int i = 0; i < eggs.size(); i++)
        if(eggs[i].getProjectilePosition().y < 0)
            eraseProj(i--);
        else
            eggs[i].drawProjectile(window);
}

sf::Vector2f Enemy::getEnemySize() const
{
    return sf::Vector2f (chicken.getGlobalBounds().width, chicken.getGlobalBounds().height);
}

const sf::Vector2f& Enemy::getEnemyPosition() const
{
    return chicken.getPosition();
    
}

const sf::Color& Enemy::getEnemyColor() const
{
    return chicken.getColor();
}


void Enemy::dropEgg(sf::RenderWindow& window)
{
    
    Projectile egg;
    
    egg.setProjectileColor(proj_color);
    egg.setProjectileTexture(proj_texture);
    egg.setProjectileOffset(proj_offset);
    egg.setProjectileSize(proj_size);
    egg.setProjectilePosition(sf::Vector2f(getEnemyPosition().x + proj_startingOffset.x, getEnemyPosition().y + proj_startingOffset.y));
    
    egg.fire();
    eggs.push_back(egg);
}

void Enemy::move()
{
    chicken.move(offset);
}

sf::FloatRect Enemy::getEnemyGlobalBounds()
{
    return chicken.getGlobalBounds();
}

bool Enemy::isPlayerDead(Player& p)
{
    for (int i = 0; i < eggs.size(); i++)
    if (eggs[i].getProjectileGlobalBounds().intersects(p.getPlayerGlobalBounds()))
        return true;
    if(p.getPlayerGlobalBounds().intersects(getEnemyGlobalBounds()))
        return true;
    
    return false;
}

void Enemy::killPlayer(Player& p)
{
    if (isPlayerDead(p))
    {   p.killplayer();
        p.decrementLives();
    }
}

void Enemy::eraseProj(int i)
{
    if(i < eggs.size() && i >= 0)
        eggs.erase(eggs.begin() + i);
}


