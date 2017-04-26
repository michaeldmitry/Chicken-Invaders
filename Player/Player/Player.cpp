#include "Player.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

Player::Player()
{
    lives = 3;
    bullets.resize(1);
    offset = sf::Vector2f(0,0);
    col = sf::Color::Red;
}

Player::~Player()
{
}

Player::Player(const sf::Vector2f& size, const sf::Color& col, const sf::Vector2f& pos)
{
    setPlayerSize(size);
    setPlayerColor(col);
    setPlayerPosition(pos);
    //setPlayerTexture(pic);
}

void Player::setPlayerSize(const sf::Vector2f& size)
{
    player.setSize(size);
}

void Player::setPlayerColor(const sf::Color& col)
{
    player.setFillColor(col);
}

void Player::setPlayerPosition(const sf::Vector2f& pos)
{
    player.setPosition(pos);
}

void Player::setPlayerTexture(sf::Texture* pic)
{
    player.setTexture(pic);
}

void Player::setPlayerOffset(const sf::Vector2f& o)
{
    offset = o;
}

void Player::setNumOfLives()
{
    lives = 3;
}

void Player::incrementLives()
{
    lives++;
}

void Player::decrementLives()
{
    lives--;
}

void Player::setNumberOfBullets()
{
    bullets.resize(1);
}

void Player::moveX(float p)
{
    player.move(p, 0);
}

void Player::moveY(float p)
{
    player.move(0, p);
}

void Player::move(float x, float y)
{
    player.move(x, y);
}
void Player::move()
{
    player.move(offset);
}

void Player::drawPlayer(sf::RenderWindow& window)
{
    window.draw(player);
    for(int i = 0; i < bullets.size(); i++)
        if(bullets[i].getProjectilePosition().y < 0)
        {
            bullets.erase(bullets.begin() + i);
            i--;
        }
    for(int i = 0; i < bullets.size(); i++)
    {
        bullets[i].drawProjectile(window);
    }
}

bool Player::isDead()
{
    if (lives == 0)
        return true;
    else
        return false;
}

sf::Vector2f Player::getPlayerSize()
{
    return player.getSize();
}

sf::Color Player::getPlayerColor()
{
    return player.getFillColor();
}

sf::Vector2f Player::getPlayerPosition()
{
    return player.getPosition();
}

int Player::getNumOfLives()
{
    return lives;
}
int Player::getNumOfBullets()
{
    return bullets.size();
}

void Player::fire()
{
    Projectile projectile;
    
    projectile.setProjectileColor(sf::Color::Red);
    projectile.setProjectileSize(sf::Vector2f(5, 15));
    projectile.setProjectilePosition(sf::Vector2f(getPlayerPosition().x + getPlayerSize().x/2 , getPlayerPosition().y - projectile.getProjectileSize().y));
    projectile.setProjectileOffset(sf::Vector2f(0, -7));
    projectile.fire();
    
    bullets.push_back(projectile);
}
