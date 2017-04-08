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

void Button::setButtonSize(sf::RectangleShape b)
{
    button.setSize(sf::Vector2f(0));
}
void Button::setButtonColor(sf::RectangleShape b)
{
    button.setFillColor(sf::Color::Red);
}

void Button::setButtonPosition(sf::RectangleShape b)
{
    button.setPosition(100, 100);
}

void Button::setText(sf::Text t)
{
    text = t;
}

void Button::setTextFont(sf::Text t)
{
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
        text.setFont(font);
}
    
void Button::setTextCharacterSize(sf::Text t)
{
    text.setTextCharacterSize(20);
}
    
void Button::setTextString(sf::Text t)
{
    text.setTextString("");
}
    
void Button::setTextColor(sf::Text t)
{
    text.setFillColor(sf::Color::White);
}
    
void Button::setTextPosition(sf::Text t)
{
    text.setTextPosition(100,100);
}

sf::RectangleShape Button::getButtonSize() const
{
    return button.getSize();
}
    
sf::RectangleShape Button::getButtonColor() const
{
    return button.getFillColor();
}
    
sf::RectangleShape Button::getButtonPosition() const
{
    return button.getPosition();
}

sf::Text Button::getTextFont() const
{
    return text.getFont();
}
    
sf::Text Button::getTextCharacterSize() const
{
    return text.getCharacterSize();
}
    
sf::Text Button::getTextString() const
{
    return text.getString();
}
    
sf::Text Button::getTextColor() const
{
    return text.getFillColor();
}
    
sf::Text Button::getTextPosition() const
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


   
