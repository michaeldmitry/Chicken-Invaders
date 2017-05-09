//
//  Menu.cpp
//  class menu
//
//  Created by Nour Hesham on 4/25/17.
//  Copyright © 2017 Nour Ali 900160807. All rights reserved.
//

#include "Menu.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <iostream>

Menu::Menu()
{
}
Menu::Menu(const sf::Vector2f& s)
{
    R.setSize(s);
}

void Menu:: setSize (const sf::Vector2f& s)
{
    R.setSize(s);
}

void Menu:: setBackground (sf::Texture* t)
{
    R.setTexture(t);
}

bool Menu:: loadMusic(const string& m)
{
    if (!music.openFromFile(resourcePath()+ m))
    {
        return false;
    }
    
    music.play();
    music.setLoop(true);
    return true;
}
void Menu::stopMusic()
{
    music.stop();
       
}


void Menu:: setNumOfButtons(int n)
{
    men.resize(n);
    
}
int Menu:: getNumOfButtons() const
{
    return men.size();
}
void Menu:: setButton(int n, const Button& x)
{
    men[n]=x;
}

void Menu:: addButton (const Button& x)
{
    men.push_back(x);
}

void Menu:: setButton(int n, const sf::Vector2f &s, const sf::Color &c, const sf::Vector2f &pos)
{
    men[n].setButtonSize(s);
    men[n].setButtonColor(c);
    men[n].setButtonPosition(pos);
}

void Menu:: setButtonText(int n, const sf::Font &f, int ch, const std::string &str, const sf::Color &col)
{
    men[n].setTextFont(f);
    men[n].setTextCharacterSize(ch);
    men[n].setTextString(str);
    men[n].setTextColor (col);
}

bool Menu:: isClicked(int n, const sf::RenderWindow& window) const
{
    if(n < 0 || n >= men.size())
        return false;
    return (men[n].isClicked(window));
}

void Menu:: drawMenu(sf::RenderWindow &window) const
{
   window.draw(R);
    
    for(int i=0;i<men.size();i++)
    {
        men[i].draw(window);

    }
}
