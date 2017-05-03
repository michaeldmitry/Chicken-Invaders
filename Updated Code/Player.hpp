#ifndef Player_hpp
#define Player_hpp
#include<iostream>
using namespace std;
#include<vector>
#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Projectile.hpp"
#include "Enemy.hpp"


class Player
{
private:
    sf::RectangleShape player;
    int lives;
    vector <Projectile> bullets;
    sf::Color col;
    sf::Clock clock;
    sf::Time time;
    bool lost;
public:
    
    Player();
    ~Player();
    Player(const sf::Vector2f& size, const sf::Vector2f& pos,sf::Color, sf::Texture* pic);
    
    void setPlayerSize(const sf::Vector2f& size);
    void setPlayerColor(const sf::Color& col);
    void setPlayerPosition(const sf::Vector2f& pos);
    void setPlayerTexture(sf::Texture* pic);
    void setNumOfLives();
    void incrementLives();
    void decrementLives();
    void setNumberOfBullets();
    void drawPlayer(sf::RenderWindow& window);
    void fire();
    
    void moveX(sf::RenderWindow& window, float p);
    void moveY(sf::RenderWindow& window, float p);
    void move(float, float);
    
    
    void killplayer();
    bool isDead();
    bool isCollide(sf::RectangleShape& object,int i);
    void eraseProjectile(sf::RectangleShape& object);
    void eraseProjectile(int i);
    void erasePlayer();
    
    sf::Rect<float> getProjectileGlobalBounds(int i);
    sf::Rect<float> getPlayerGlobalBounds();
    
    sf::Vector2f getPlayerSize() const;
    sf::Color getPlayerColor() const;
    sf::Vector2f getPlayerPosition() const;
    int getNumOfLives() const;
    int getNumOfBullets() const;
};

#endif /* Player_hpp */
