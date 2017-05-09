//
//  PickUp.cpp
//  waves
//
//  Created by Nour Hesham on 5/5/17.
//  Copyright © 2017 Nour Ali 900160807. All rights reserved.
//

#include "PickUp.hpp"


PickUp::PickUp()
{
}

PickUp::~PickUp()
{
}

PickUp::PickUp(sf::Vector2f s, sf::Color c, sf::Vector2f p, sf::Texture *t)
{
    setPickupScale(s);
    setPickupColor(c);
    setPickupTexture(t);
}

void PickUp::setPickupScale(sf::Vector2f s)
{
    pickup.setScale(s);
}

void PickUp::setPickupColor(sf::Color c)
{
    pickup.setColor(c);
}

void PickUp::setPickupPosition(sf::Vector2f f)
{
    pickup.setPosition(f);
}

void PickUp::setPickupTexture(sf::Texture*t)
{
    pickup.setTexture(*t);
}


void PickUp::drawPickup(sf::RenderWindow &window)
{
    window.draw(pickup);
}

void PickUp::move(float p)
{
    pickup.move(0, p);
}

sf::FloatRect PickUp::getPickUpGlobalBounds()
{
    return pickup.getGlobalBounds();
}

sf::Vector2f PickUp::getPickUpPosition()
{
    return pickup.getPosition();
}

void PickUp:: setType(options x)
{
    type=x;
}

PickUp:: options PickUp:: getType()
{
    return type;
    
}
