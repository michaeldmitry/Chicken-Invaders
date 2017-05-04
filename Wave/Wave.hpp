#ifndef Wave_hpp
#define Wave_hpp
#include <stdio.h>
#include "Enemy.hpp"
#include "Player.hpp"
#include "Projectile.hpp"

class Wave
{
private:
    vector <vector<Enemy>> chickens;
    sf::Vector2f offset;
    sf::Clock chick_anim_clk;
    int chick_anim_counter;
    
public:
    Wave();
    ~Wave();
    
    void setNumOfChickens();
    void setChickenPosition(const sf::Vector2f& pos);
    void setChickenOffset(const sf::Vector2f& o);
    void setChickenTexture(sf::Texture *pic);
    void setChickenTextureRect(const sf::IntRect& R);
    void changeChickenAnimation();
    void drawWave(sf::RenderWindow& window);
    bool isChickenHitByBullet(Player& p, Enemy& e);
    void eraseChicken(Player& p);
    
    bool checkChickenBoundary( sf::RenderWindow& window, const Enemy& chicken);
    
    int getNumOfChickens();
    const sf::Vector2f& getChickenPosition();
    const sf::Vector2f& getChickenOffset();
    
};

#endif /* Wave_hpp */
