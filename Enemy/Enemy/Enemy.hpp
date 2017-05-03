#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Projectile.hpp"
#include <stdlib.h>
#include <time.h>
class Player;
class Enemy
{
private:

    sf::RectangleShape chicken;
    vector <Projectile> eggs;
    sf::Vector2f offset;
    sf::Time time;
    sf::Clock clock;
    
public:
    Enemy();
    ~Enemy();
    Enemy(const sf::Vector2f& s, const sf::Vector2f& pos, const sf::Color& col); //sf::Texture* pic);
    
    void setEnemySize(const sf::Vector2f& s);
    void setEnemyPosition(const sf::Vector2f& pos);
    void setEnemyColor(const sf::Color& col);
    void setEnemyTexture(const sf::Texture* pic);
    void setEnemyOffset(const sf::Vector2f& o);
    void drawEnemy(sf::RenderWindow& window);
    
    sf::Rect<float> getEnemyGlobalBounds();
    
    sf::Vector2f getEnemySize() const;
    sf::Vector2f getEnemyPosition() const;
    sf::Color getEnemyColor() const;
    
    void dropEgg(sf::RenderWindow& window,sf::Texture *pic);
    //void dropPickup(sf::RenderWindow& window, const sf::Color& col, const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Texture* pic);
    void dropDrumStick(sf::RenderWindow& window, sf::Color& col, sf::Vector2f& size, sf::Vector2f& pos, sf::Texture* pic);
    
    void move();
    void moveX(sf::RenderWindow& window, float p);
    void moveY(sf::RenderWindow& window, float p);
    bool limitXpos(sf::RenderWindow& window, float p);
    bool limitXneg(sf::RenderWindow& window, float p);
    bool limitY(sf::RenderWindow& window, float p);
    
    bool isPlayerDead(Player& p);
    void killPlayer(Player& p);

    };

#endif /* Enemy_hpp */
