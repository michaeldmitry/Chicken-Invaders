//
//  RockWave.hpp
//  waves
//
//  Created by Nour Hesham on 5/6/17.
//  Copyright © 2017 Nour Ali 900160807. All rights reserved.
//

#ifndef RockWave_hpp
#define RockWave_hpp

#include <stdio.h>

#include <stdio.h>
#include "ResourcePath.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Highscores.h"

class RockWave
{
private:
    vector <Enemy> rocks;
    sf::Vector2f base_pos;
    sf::Vector2f offset;
    vector<int> counter;
    int rock_anim_counter;
    sf::Sprite background;
    vector <bool> hasRockMoved;
    int k = 0;
    sf::Clock Rock_anim_clk;
    sf::Clock rock_time;
    sf::Clock player_killed_clk,player_immunity_clk;
    int score_counter;
public:
    RockWave();
    ~RockWave();
    void setBasePos(const sf::Vector2f& base);
    void allowRockToMove();
    void setNumOfRocks();
    void setRockPosition(sf::RenderWindow & window);
    void setRockOffset(const sf::Vector2f& o);
    void setRockTexture(sf::Texture* pic);
    void setRockOrigin();
    void setRockTextureRect(const sf::IntRect& R);
    void changRockAnimation();
    void setUp(sf::RenderWindow& window, Enemy& rock);
    void setleft(sf::RenderWindow& window, Enemy& rock);
    void setWaveBackground(sf::Texture* t);
    void setPosition(sf::RenderWindow& window, Enemy &enemy);
    
    void playRockWave(sf::RenderWindow& window, Player& player, int& my_score);
    void playerMove(Player& player,sf::RenderWindow& window);
    //void setRockTextureRect(const sf::IntRect& R);
    //void changeRockAnimation();
    bool isRockHitByBullet(Player& p, Enemy& rock, int j);
    void createRockWave(Enemy& rock, int x, sf::RenderWindow& window);
    //bool checkRockBoundary( sf::RenderWindow& window, const Enemy& chicken);
    //void keepRockBounds (sf::RenderWindow& window);
    
    
    void moveRocks(sf::Vector2f x);
    void rotateRocks(float a);
    void setRockScale();
    
    int getNumOfRocks() const;
    const sf::Vector2f& getBasePos() const;
    const sf::Vector2f& getRockPosition() const;
    const sf::Vector2f& getRockOffset() const;
    
    void playerStatus(Player& p,sf::RenderWindow &window);
    void eraseRock(Player& p);
    
    bool hasRockWaveEndedNormally();
    int  returnScore();

    void drawRockWave(sf::RenderWindow& window);
    bool hasRockWaveEndedbyDeath(Player& p);
    
    
};

#endif /* RockWave_hpp */
