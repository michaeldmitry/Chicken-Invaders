#ifndef Projectile_hpp
#define Projectile_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Projectile
{
private:
    sf::RectangleShape bomb;
    sf::Vector2f offset;
    bool fired;
    
public:
    Projectile();
    ~Projectile();
    Projectile(sf::Color& col, sf::Vector2f& size, sf::Vector2f& pos, sf::Texture* pic);
    
    void setProjectileColor(const sf::Color& col);
    void setProjectileSize(const sf::Vector2f& size);
    void setProjectilePosition(const sf::Vector2f& pos);
    void setProjectileTexture(sf::Texture* pic);
    void setProjectileOffset(const sf::Vector2f& o);
    
    void drawProjectile(sf::RenderWindow& window);
    
    void fire();
    void stopFire();
    bool isFired();
    
    void moveX(float p);
    void moveY(float p);
    void move(float, float);
    void move();
    void rotate(float a);
    
    sf::Vector2f getProjectilePosition() const;
    
    sf::Color getProjectileColor();
    sf::Vector2f getProjectileSize();
    sf::Vector2f getProjectilePosition();
};
#endif /* Projectile_hpp */
