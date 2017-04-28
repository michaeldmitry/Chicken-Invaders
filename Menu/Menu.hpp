//
//  Menu.hpp
//  class menu
//
//  Created by Nour Hesham on 4/25/17.
//  Copyright © 2017 Nour Ali 900160807. All rights reserved.
//

#ifndef Menu_hpp
#define Menu_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <stdio.h>
#include "Button.hpp"

using namespace std;

class Menu
{
    
private:
    vector <Button> men;
    sf::Music music;
    sf::RectangleShape R;

public:
    Menu();
    Menu(const sf::Vector2f&);
    void setSize(const sf::Vector2f&);
    void setBackground (sf::Texture* pic);
    bool loadMusic(const string& m);
    void addButton (const Button& x);
    void setNumOfButtons (int n);
    void setButton (int n, const Button& x);
    void setButton (int n,  const sf::Vector2f& s, const sf::Color& c,const sf::Vector2f& pos);
    void setButtonText(int n,const sf::Font& f, int ch, const std::string& str,const sf::Color& col);
    int getNumOfButtons() const;
    bool isClicked (int n, const sf::RenderWindow& window ) const;
    void drawMenu (sf::RenderWindow& window) const;

};


#endif /* Menu_hpp */
