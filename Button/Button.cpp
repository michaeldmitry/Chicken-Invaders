#include "Button.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

Button::Button()
{
    button;
    text;
}

Button::Button(sf::RectangleShape b, sf::Text t)
{
    button = b;
    text = t;
}

void Button::setButton(sf::RectangleShape b)
{
    button = b;
}

void Button::setButtonSize(sf::Vector2f& s)
{
    button.setSize(sf::Vector2f(s));
}
void Button::setButtonColor(sf::Color& c)
{
    button.setFillColor(c);
}

void Button::setButtonPosition(int& p)
{
    button.setPosition(p, p);
}

void Button::setText(sf::Text t)
{
    text = t;
}

void Button::setTextFont(sf::Font& f)
{
    text.setFont(f);
}
    
void Button::setTextCharacterSize(int& ch)
{
    text.setCharacterSize(ch);
}
    
void Button::setTextString(std::string& str)
{
    text.setString(str);
}
    
void Button::setTextColor(sf::Color& col)
{
    text.setFillColor(col);
}
    
void Button::setTextPosition(int& pos)
{
    text.setPosition(pos, pos);
}

sf::Vector2f Button::getButtonSize() const
{
    return button.getSize();
}
    
sf::Color Button::getButtonColor() const
{
    return button.getFillColor();
}
    
sf::Vector2f Button::getButtonPosition() const
{
    return button.getPosition();
}
    
int Button::getTextCharacterSize() const
{
    return text.getCharacterSize();
}
    
std::string Button::getTextString() const
{
    return text.getString();
}
    
sf::Color Button::getTextColor() const
{
    return text.getFillColor();
}
    
sf::Vector2f Button::getTextPosition() const
{
    return text.getPosition();
}

sf::RectangleShape Button::getButton() const
{
    return button;
}
    
sf::Text Button::getText() const
{
    return text;
}
    
Button::~Button()
{
}


   
