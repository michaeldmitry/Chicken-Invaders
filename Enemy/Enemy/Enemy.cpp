#include "Enemy.hpp"
#include <iostream>

Enemy::Enemy()
{
    
}

Enemy::~Enemy()
{
}

Enemy::Enemy(const sf::Vector2f& s,const sf::Vector2f& pos,const sf::Color& col) //sf::Texture* pic)
{
    setEnemySize(s);
    setEnemyPosition(pos);
    setEnemyColor(col);
   // setEnemyTexture(pic);
}

void Enemy::setEnemySize(const sf::Vector2f& s)
{
    chicken.setSize(s);
}

void Enemy::setEnemyPosition(const sf::Vector2f& pos)
{
        chicken.setPosition(pos);
}

void Enemy::setEnemyColor(const sf::Color& col)
{
    chicken.setFillColor(col);
}

void Enemy::setEnemyTexture(const sf::Texture* pic)
{
    chicken.setTexture(pic);
}

void Enemy::setEnemyOffset(const sf::Vector2f& o)
{
    offset = o;
}

void Enemy::drawEnemy(sf::RenderWindow& window)
{
        window.draw(chicken);
    for(int i = 0; i < eggs.size(); i++)
        if(eggs[i].getProjectilePosition().y < 0)
        {
            eggs.erase(eggs.begin() + i);
            i--;
        }
    for(int i = 0; i < eggs.size(); i++)
    {
        std::cout << eggs[i].getProjectilePosition().y << std::endl;
        eggs[i].drawProjectile(window);
    }
}

sf::Vector2f Enemy::getEnemySize() const
{
    return chicken.getSize();
}

sf::Vector2f Enemy::getEnemyPosition() const
{
    return chicken.getPosition();
}

sf::Color Enemy::getEnemyColor() const 
{
    return chicken.getFillColor();
}

void Enemy::dropEgg(sf::RenderWindow& window, sf::Texture *pic)
{
   
    Projectile egg;
            
            egg.setProjectileColor(sf::Color::White);
            egg.setProjectileSize(sf::Vector2f(50, 50));
            egg.setProjectilePosition(sf::Vector2f(getEnemyPosition().x + getEnemySize().x/2 , getEnemyPosition().y +getEnemySize().y));
            egg.setProjectileTexture(pic);
    
    egg.setProjectileOffset(sf::Vector2f(0, 7));
 
    time = clock.getElapsedTime();
   
    //if (rand()%10+2)
    {
        egg.fire();
        eggs.push_back(egg);
        clock.restart();
    }
  
}

/*
void Enemy::dropPickup(sf::RenderWindow& window, const sf::Color& col, const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Texture* pic)
{
            Projectile pickup;
            
            pickup.setProjectileColor(sf::Color::Blue);
            pickup.setProjectileSize(sf::Vector2f(5, 15));
            pickup.setProjectilePosition(sf::Vector2f(getEnemyPosition().x + getEnemySize().x/2 , getEnemyPosition().y - pickup.getProjectileSize().y));
            pickup.setProjectileOffset(sf::Vector2f(0, 7));
            pickup.fire();
    
}
 */

void Enemy::moveX(sf::RenderWindow& window, float p)
{
    if ((p > 0) && (chicken.getPosition().x < (window.getSize().x - chicken.getSize().x)))
        chicken.move(p, 0);
    else
    {
        if ((p < 0) && (chicken.getPosition().x > 0))
            chicken.move(p, 0);
    }
}

void Enemy::moveY(sf::RenderWindow& window, float p)
{
    if ((p > 0) && (chicken.getPosition().y+100 != (window.getSize().y)))
        chicken.move(0, p);
    else {
        if ((p < 0) && (chicken.getPosition().y > 0))
            chicken.move(0,p);}
}
void Enemy::move()
{
        chicken.move(offset);
}

bool Enemy::limitXpos(sf::RenderWindow& window, float p)
{
    if ((p > 0) && (chicken.getPosition().x < (window.getSize().x - chicken.getSize().x)))
        return false;

    else
        return true;
}
bool Enemy::limitXneg(sf::RenderWindow& window, float p)
{
        if ((p < 0) && (chicken.getPosition().x > 0))
            return true;
    else
        return false;
}
bool Enemy::limitY(sf::RenderWindow& window, float p)
{
    if ((p > 0) && (chicken.getPosition().y+100 != (window.getSize().y)))
        return false;
    else
        if ((p < 0) && (chicken.getPosition().y > 0))
            return false;
    else
        return true;
}


sf::Rect<float> Enemy::getEnemyGlobalBounds()
{
    return chicken.getGlobalBounds();
}

bool Enemy::isPlayerDead(Player& p)
{
    for (int i = 0; i < eggs.size(); i++)
    {if (eggs[i].getProjectileGlobalBounds().intersects(p.getPlayerGlobalBounds()))
        return true;
    else
        return false;}
}

void Enemy::killPlayer(Player& p)
{
    if (isPlayerDead(p))
    {   p.erasePlayer();
        p.decrementLives();
    }
}
