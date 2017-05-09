//
//  PickUp.hpp
//  waves
//
//  Created by Nour Hesham on 5/5/17.
//  Copyright © 2017 Nour Ali 900160807. All rights reserved.
//

#ifndef PickUp_hpp
#define PickUp_hpp

#include <stdio.h>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Projectile.hpp"

class PickUp
{
public:
    PickUp();
    ~PickUp();
    PickUp(sf::Vector2f s, sf::Color c, sf::Vector2f p, sf::Texture *t);
    enum options{incrementBullets, incrementLives, immunity};
    
    options type;

    void setPickupScale(sf::Vector2f v);
    void setPickupColor(sf::Color c);
    void setPickupPosition(sf::Vector2f f);
    void setPickupTexture(sf::Texture *t);
    
    void move(float p);
    void drawPickup(sf::RenderWindow &window);
    
    sf::FloatRect getPickUpGlobalBounds();
    sf::Vector2f getPickUpPosition();
    
    void setType(options x);
    PickUp:: options getType();

    
private:
    sf::Sprite pickup;

};

#endif /* PickUp_hpp */
