#ifndef Rocks_hpp
#define Rocks_hpp

#include <stdio.h>
#include "Enemy.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
class Rocks
{
private:
    vector<Enemy> rocks;
    sf::Vector2f base_pos;
    sf::Vector2f offset;
    int counter;
public:
    Rocks();
    ~Rocks();
    void setBasePos(const sf::Vector2f& base);
    
    void setNumOfRocks();
    void setRockPosition(const::sf::Vector2f& pos,sf::RenderWindow & window);
    void setRockOffset(const sf::Vector2f& o);
    void setRockTexture(sf::Texture *pic);
    //void setRockTextureRect(const sf::IntRect& R);
    //void changeRockAnimation();
    bool isRockHitByBullet(Player& p, Enemy& rock);
    void createRockWave(Enemy& rock, int x,sf::RenderWindow &window);
    //bool checkRockBoundary( sf::RenderWindow& window, const Enemy& chicken);
    //void keepRockBounds (sf::RenderWindow& window);

    
    void moveRocks();
    void rotateRocks(float a);
    int getNumOfRocks() const;
    const sf::Vector2f& getBasePos() const;
    const sf::Vector2f& getRockPosition() const;
    const sf::Vector2f& getRockOffset() const;
    
    void playerStatus(Player& p);
    void eraseRock(Player& p);
    
    
    void drawRockWave(sf::RenderWindow& window);
    bool hasRockWaveEnded();
    

};

#endif /* Rocks_hpp */
