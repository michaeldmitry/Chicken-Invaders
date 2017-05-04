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
    sf::Vector2f base_pos;
    int rate_eggs;
    
public:
    Wave();
    ~Wave();
    void setRateEggs(int x);
    void setBasePos(const sf::Vector2f& base);
    
    void setNumOfChickens();
    void setChickenPosition(const sf::Vector2f& pos);
    void setChickenOffset(const sf::Vector2f& o);
    void setChickenTexture(sf::Texture *pic);
    void setChickenTextureRect(const sf::IntRect& R);
    void changeChickenAnimation();
    bool isChickenHitByBullet(Player& p, Enemy& chicken);
    void createChickenWave(Enemy& enemy, int rows, int cols);
    bool checkChickenBoundary( sf::RenderWindow& window, const Enemy& chicken);
    void keepChickBounds (sf::RenderWindow& window);
    
    void createRockWave();
    
    void moveChickens();
    bool shouldDropEgg();
    int getNumOfChickens() const;
    const sf::Vector2f& getBasePos() const;
    const sf::Vector2f& getChickenPosition() const;
    const sf::Vector2f& getChickenOffset() const;
    int getRateEggs() const;
    
    void playerStatus(Player& p);
    bool isChickenHitByBullet(Player& p, int x, int y);
    void eraseChicken(Player& p);
    void dropChickenEggs (sf::RenderWindow& window);
    
    
    void drawChickenWave(sf::RenderWindow& window);
    bool hasChickenWaveEnded();


};

#endif /* Wave_hpp */
