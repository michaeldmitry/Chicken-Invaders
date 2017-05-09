#ifndef BeastWave_hpp
#define BeastWave_hpp

#include <stdio.h>
#include "Player.hpp"
#include "Projectile.hpp"
#include "Enemy.hpp"
#include "PickUp.hpp"
#include "ChickenWave.hpp"
#include "Highscores.h"


class BeastWave
{
private:
    vector <Enemy> beast;
    vector <Projectile> eggs;
    vector <int> counter;
    sf::Vector2f offset;
    int x_size;
    int y_size;
    int numOfSprites;
    int beast_anim_counter;
    sf::Clock beast_anim_clk;
    sf::Clock beast_move_clk;
    sf::Color proj_color;
    sf::Vector2f proj_size;
    sf::Vector2f proj_startingOffset;
    sf::Texture* proj_texture;
    sf::Vector2f proj_offset;
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
    bool dead;
    int score_counter;

    
public:
    BeastWave();
    ~BeastWave();
    
    void setNumOfBeasts();
    void setBeastPosition(const sf::Vector2f& pos, int i);
    void setBeastPosition(float pos_x, float pos_y, int i);
    void setBeastScale(const sf::Vector2f& scale, int i);
    void setBeastOffset(const sf::Vector2f& o);
    void setBeastTexture(sf::Texture* pic, int i);
    void setBeastTextureRect(const sf::IntRect& R);
    void changeBeastAnimation();
    void setX_size(int x);
    void setY_size(int y);
    void setNumOfSprites(int num);
    void setWaveBackground(sf::Texture *t);
    
    void setProjTexture(sf::Texture* pic);
    void setProjOffset(const sf::Vector2f& o);
    void setProjColor(const sf::Color& col);
    void setProjSize(const sf::Vector2f& s);
    void setProjStartingOffset(sf::Vector2f& s);
    
    void killBeast(Player& p);
    bool isBeastHit(Player& p, int i);
    void eraseBeast(Player& p);
    void drawBeast(sf::RenderWindow& window);
    
    bool shouldDropEgg();
    void dropEgg(sf::RenderWindow& window, int i);
    void dropBeastEggs (sf::RenderWindow& window);
    bool didEnemyOrProjectilesHitPlayer(Player& p);

    
    void move(int i, sf::RenderWindow& window);
    
    const sf::Vector2f& getBeastPosition(int i);
    sf::Vector2f getBeastSize(int i);
    sf::FloatRect getBeastGlobalBounds(int i);
    
    bool isPlayerDead(Player& p);
    void killPlayer(Player& p);
    void eraseProj(int i);
    bool hasBeastWaveEndedNormally();
    bool hasBeastWaveEndedbyDeath(Player& p);
    void playBeastWave(Player& player, sf::RenderWindow &window, int& my_score);
    void movePlayer(Player &player, sf::RenderWindow& window);
    
    void setPickTexture(sf::Texture* a,sf::Texture* b, sf::Texture* c);
    void setPickScale(sf::Vector2f s);
    void setPickOffset(float a);
    void createPickUp(PickUp& pick);
    void dropPickUp();
    void movePickUp();
    void erasePickUp(sf::RenderWindow& window);
    void playerCollects(Player& player);
    void playerStatus(Player& player, sf::RenderWindow& window);
    int  returnScore();


};


#endif /* Beast_hpp */
