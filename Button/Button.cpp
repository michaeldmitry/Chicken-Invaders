#include "Button.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <iostream>

Button::Button()
{
}

Button::Button(const sf::Vector2f& s, const sf::Color& c, const sf::Vector2f& pos, const sf::Font& f, int ch, const std::string& str, const sf::Color& col)
{
    setButtonSize(s);
    setButtonColor(c);
    setButtonPosition(pos);

    setTextFont(f);
    setTextCharacterSize(ch);
    setTextString(str);
    setTextColor(col);
}

void Button::setButtonSize(const sf::Vector2f& s)
{
    key.setSize(s);
}
void Button::setButtonColor(const sf::Color& c)
{
    key.setFillColor(c);
}

void Button::setButtonPosition(const sf::Vector2f& pos)
{
    key.setPosition(pos);
    text.setPosition(pos);
}

void Button::setTextFont(const sf::Font& f)
{
    text.setFont(f);
}
    
void Button::setTextCharacterSize(int ch)
{
    text.setCharacterSize(ch);
}
    
void Button::setTextString(const std::string& str)
{
    text.setString(str);
}
    
void Button::setTextColor(const sf::Color& col)
{
    text.setFillColor(col);
}

const sf::Vector2f& Button::getButtonSize() const
{
    return key.getSize();
}
    
const sf::Color& Button::getButtonFillColor() const
{
    return key.getFillColor();
}
    
const sf::Vector2f& Button::getButtonPosition() const
{
    return key.getPosition();
}
    
int Button::getTextCharacterSize() const
{
    return text.getCharacterSize();
}
    
const sf::String& Button::getTextString() const
{
    return text.getString();
}
    
const sf::Color& Button::getTextColor() const
{
    return text.getFillColor();
}
    
Button::~Button()
{
}

void Button::draw(sf::RenderWindow& window) const
{
    window.draw(key);
    window.draw(text);
}

bool Button::isClicked(const sf::RenderWindow& window) const
{
    //if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        return(key.getGlobalBounds().contains(localPosition.x, localPosition.y));
        
    }
        
}

void Button::moveLeft(float p)
{
    text.move(0 - p, 0);
}

void Button::moveRight(float p)
{
    text.move(p, 0);
}

void Button::moveUp(float p)
{
    text.move(0, 0 - p);
}

void Button::moveDown(float p)
{
    text.move(0, p);
}

void Button::setTexture(sf::Texture* pic)
{
    key.setTexture(pic);
}


