#include "Player.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

Player::Player()
{
    lives = 3;
    bullets.resize(1);
    col = sf::Color::Red;
    lost = false;
}

Player::~Player()
{
}

Player::Player(const sf::Vector2f& size, const sf::Vector2f& pos,sf::Color c, sf::Texture* pic)
{
    setPlayerSize(size);
    setPlayerPosition(pos);
    setPlayerColor(c);
    setPlayerTexture(pic);
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

void Player::moveX(sf::RenderWindow& window, float p)
{
    if ((p > 0) && (player.getPosition().x < (window.getSize().x - player.getSize().x)))
        player.move(p, 0);
    else {
     if ((p < 0) && (player.getPosition().x > 0))
         player.move(p, 0);}
}

void Player::moveY(sf::RenderWindow& window, float p)
{
    if ((p > 0) && (player.getPosition().y+100 != (window.getSize().y)))
        player.move(0, p);
    else {
     if ((p < 0) && (player.getPosition().y > 0))
         player.move(0,p);}
}

void Player::move(float x, float y)
{
    player.move(x, y);
}

void Player::drawPlayer(sf::RenderWindow& window)
{
    if(!lost)
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

bool Player::isCollide(sf::RectangleShape& object, int i)
{
    return (bullets[i].getProjectileGlobalBounds().intersects(object.getGlobalBounds()));
}

void Player::eraseProjectile(sf::RectangleShape& object)
{
    for (int i = 0; i < bullets.size(); i++)
        if (isCollide(object, i))
        {
            bullets.erase(bullets.begin() + i);
            i--;
        }
}
void Player::eraseProjectile(int i)
{
    if(i < bullets.size() && i >= 0)
        bullets.erase(bullets.begin() + i);
}

void Player::erasePlayer()
{
    player.setFillColor(sf::Color::Transparent);
}

sf::Vector2f Player::getPlayerSize() const
{
    return player.getSize();
}

sf::Color Player::getPlayerColor() const
{
    return player.getFillColor();
}

sf::Vector2f Player::getPlayerPosition() const
{
    return player.getPosition();
}

int Player::getNumOfLives() const
{
    return lives;
}
int Player::getNumOfBullets() const
{
    return bullets.size();
}

void Player::fire()
{
    if(!lost){
        Projectile projectile;
        
        projectile.setProjectileColor(sf::Color::Red);
        projectile.setProjectileSize(sf::Vector2f(5, 15));
        projectile.setProjectilePosition(sf::Vector2f(getPlayerPosition().x + getPlayerSize().x/2 , getPlayerPosition().y - projectile.getProjectileSize().y));
        projectile.setProjectileOffset(sf::Vector2f(0, -15));
        
        if(clock.getElapsedTime().asSeconds()>= 0.125)
        {
            projectile.fire();
            bullets.push_back(projectile);
            clock.restart();
        }
    }
}

sf::Rect<float> Player::getProjectileGlobalBounds(int i)
{
    if (i < bullets.size() && i >= 0)
        return bullets[i].getProjectileGlobalBounds();
    else
        return sf::Rect<float>(sf::Vector2f(-10000, -10000), sf::Vector2f(0, 0));
}

sf::Rect<float> Player::getPlayerGlobalBounds()
{
    return player.getGlobalBounds();
}

void Player::killplayer(){
    lost = true;
}
