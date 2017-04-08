#include "Button.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

Button::Button()
{
    key;    // This line does nothing. Remove it.
    text;   // This line does nothing. Remove it.
}

Button::Button(const sf::Vector2f& s, const sf::Color& c, const sf::Vector2f& p, const sf::Font& f, int ch, const std::string& str, const sf::Color& col, const sf::Vector2f& pos)
{
    setButtonSize(s);
    setButtonColor(c);
    setButtonPosition(p);
    
    setTextFont(f);
    setTextCharacterSize(ch);
    setTextString(str);
    setTextColor(col);
    setTextPosition(pos);
}

void Button::setButton(const sf::Vector2f& s, const sf::Color& c, const sf::Vector2f& p) // This function sets multiple things at once - remove it.
{
    setButtonSize(s);
    setButtonColor(c);
    setButtonPosition(p);
}

void Button::setButtonSize(const sf::Vector2f& s)
{
    key.setSize(sf::Vector2f(s));   // No need to write sf::Vector2f(s) .. just write s
}
void Button::setButtonColor(const sf::Color& c)
{
    key.setFillColor(c);
}

void Button::setButtonPosition(const sf::Vector2f& p)
{
    key.setPosition(p);
}

void Button::setText(const sf::Font& f, int ch, const std::string& str, const sf::Color& col, const sf::Vector2f& pos) // This function sets multiple things at once - remove it.
{
    setTextFont(f);
    setTextCharacterSize(ch);
    setTextString(str);
    setTextColor(col);
    setTextPosition(pos);
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

void Button::setTextPosition(const sf::Vector2f& pos)   // Does it make sense to put the text and key in different positions?
{
    text.setPosition(pos);
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

const std::string& Button::getTextString() const
{
    return text.getString();
}

const sf::Color& Button::getTextColor() const
{
    return text.getFillColor();
}

const sf::Vector2f& Button::getTextPosition() const // Redundant
{
    return text.getPosition();
}

Button::~Button()
{
}



