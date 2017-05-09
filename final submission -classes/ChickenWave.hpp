#ifndef Wave_hpp
#define Wave_hpp
#include <stdio.h>
#include "Enemy.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "PickUp.hpp"
#include "ResourcePath.hpp"
#include "HighScores.h"

class ChickenWave
{
private:
    vector <vector<Enemy>> chickens;
    sf::Vector2f offset;
    sf::Clock chick_anim_clk;
    int chick_anim_counter;
    sf::Vector2f base_pos;
    int rate_eggs;
    sf::Sprite background;
    vector <PickUp> pickup;
    sf::Color pick_color;
    sf::Texture* pick_texture[3];
    sf::Texture pick_texture1;
    sf::Texture pick_texture2;
    sf::Texture pick_texture3;
    float pick_offset;
    sf::Clock player_killed_clk;
    sf::Clock player_immunity_clk;
    int score_counter;

    
public:
    ChickenWave();
    ~ChickenWave();
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
    
    void setBackgroundTexture(sf::Texture* t);
    
    void createRockWave();
    
    void setPickTexture(sf::Texture* a,sf::Texture* b, sf::Texture* c);
    void setPickScale(sf::Vector2f s);
    void setPickOffset(float a);
    void createPickUp(PickUp& pick);
    void dropPickUp(Enemy& enemy);
    void movePickUp();
    void erasePickUp(sf::RenderWindow& window);
    void playerCollects(Player& player);

    
    void moveChickens();
    bool shouldDropEgg();
    int getNumOfChickens() const;
    const sf::Vector2f& getBasePos() const;
    const sf::Vector2f& getChickenPosition() const;
    const sf::Vector2f& getChickenOffset() const;
    int getRateEggs() const;
    
    void playerStatus(Player& p, sf::RenderWindow& window);
    bool isChickenHitByBullet(Player& p, int x, int y);
    void eraseChicken(Player& p);
    void dropChickenEggs (sf::RenderWindow& window);
    
    
    void drawChickenWave(sf::RenderWindow& window);
    bool hasChickenWaveEndedNormally();
    bool hasChickenWaveEndedbyDeath(Player &player);
    void movePlayer(sf::RenderWindow& window, Player& player);
    bool playChickenWave(sf::RenderWindow& window, Player& player, int& my_score);
    
    int returnScore();
    void setPlayerName(const string& n);

};

#endif /* Wave_hpp */
