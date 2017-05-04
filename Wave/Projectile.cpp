#include "Projectile.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

Projectile::Projectile()
{
    offset = sf::Vector2f(0, 0);
    fired = false;
}

Projectile::~Projectile()
{
}

Projectile::Projectile(sf::Color& col, sf::Vector2f& size, sf::Vector2f& pos, sf::Texture* pic)
{
    fired = false;
    setProjectileColor(col);
    setProjectileSize(size);
    setProjectilePosition(pos);
    setProjectileTexture(pic);
}

void Projectile::setProjectileColor(const sf::Color& col)
{
    bomb.setFillColor(col);
}

void Projectile::setProjectileSize(const sf::Vector2f& size)
{
    bomb.setSize(size);
}

void Projectile::setProjectilePosition(const sf::Vector2f& pos)
{
    bomb.setPosition(pos);
}
void Projectile::setProjectileOffset(const sf::Vector2f& o)
{
    offset = o;
}

void Projectile::setProjectileTexture(sf::Texture* pic)
{
    bomb.setTexture(pic);
}

void Projectile::drawProjectile(sf::RenderWindow& window)
{
    // if(fired){
    window.draw(bomb);
    move();
    // }
}

void Projectile::stopFire()
{
    fired = false;
}

void Projectile::moveX(float p)
{
    bomb.move(p, 0);
}

void Projectile::move(float x, float y)
{
    bomb.move(x, y);
}

void Projectile::moveY(float p)
{
    bomb.move(0,p);
}
void Projectile::move()
{
    bomb.move(offset);
}
void Projectile::rotate(float a)
{
    bomb.rotate(a);
}

void Projectile::fire()
{
    fired = true;
}

bool Projectile::isFired()
{
    return fired;
}


sf::Color Projectile::getProjectileColor() const
{
    return bomb.getFillColor();
}

sf::Vector2f Projectile::getProjectileSize() const
{
    return bomb.getSize();
}

sf::Vector2f Projectile::getProjectilePosition() const
{
    return bomb.getPosition();
}

sf::Rect<float> Projectile::getProjectileGlobalBounds() const
{
    return bomb.getGlobalBounds();
}

