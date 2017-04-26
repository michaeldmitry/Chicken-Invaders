#ifndef Player_hpp
#define Player_hpp
#include<iostream>
using namespace std;
#include<vector>
#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Projectile.hpp"


class Player
{
private:
    sf::RectangleShape player;
    int lives;
    vector <Projectile> bullets;
    sf::Vector2f offset;
    sf::Color col;
public:
    Player();
    ~Player();
    Player(const sf::Vector2f& size, const sf::Color& col, const sf::Vector2f& pos);
    
    void setPlayerSize(const sf::Vector2f& size);
    void setPlayerColor(const sf::Color& col);
    void setPlayerPosition(const sf::Vector2f& pos);
    void setPlayerTexture(sf::Texture* pic);
    void setPlayerOffset(const sf::Vector2f& o);
    void setNumOfLives();
    void incrementLives();
    void decrementLives();
    void setNumberOfBullets();
    void drawPlayer(sf::RenderWindow& window);
    void fire();
    
    void moveX(float p);
    void moveY(float p);
    void move(float, float);
    void move();
    
    bool isDead();
    
    sf::Vector2f getPlayerSize();
    sf::Color getPlayerColor();
    sf::Vector2f getPlayerPosition();
    int getNumOfLives();
    int getNumOfBullets();
};

#endif /* Player_hpp */
