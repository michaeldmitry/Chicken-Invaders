#include "Button.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

Button::Button()
{
<<<<<<< HEAD
=======
    key;    // This line does nothing. Remove it.
    text;   // This line does nothing. Remove it.
>>>>>>> c7fa4fed0a1d2bd27f6d06cf469a71f4d1e6f675
}

Button::Button(const sf::Vector2f& s, const sf::Color& c, const sf::Vector2f& pos, const sf::Font& f, int ch, const std::string& str, const sf::Color& col)
{
    setButtonSize(s);
    setButtonColor(c);
<<<<<<< HEAD
    setButtonPosition(pos);

=======
    setButtonPosition(p);
    
>>>>>>> c7fa4fed0a1d2bd27f6d06cf469a71f4d1e6f675
    setTextFont(f);
    setTextCharacterSize(ch);
    setTextString(str);
    setTextColor(col);
    setTextPosition(pos);
}

<<<<<<< HEAD
void Button::setButtonSize(const sf::Vector2f& s)
{
    key.setSize(s);
=======
void Button::setButton(const sf::Vector2f& s, const sf::Color& c, const sf::Vector2f& p) // This function sets multiple things at once - remove it.
{
    setButtonSize(s);
    setButtonColor(c);
    setButtonPosition(p);
}

void Button::setButtonSize(const sf::Vector2f& s)
{
    key.setSize(sf::Vector2f(s));   // No need to write sf::Vector2f(s) .. just write s
>>>>>>> c7fa4fed0a1d2bd27f6d06cf469a71f4d1e6f675
}
void Button::setButtonColor(const sf::Color& c)
{
    key.setFillColor(c);
}

<<<<<<< HEAD
void Button::setButtonPosition(const sf::Vector2f& pos)
=======
void Button::setButtonPosition(const sf::Vector2f& p)
{
    key.setPosition(p);
}

void Button::setText(const sf::Font& f, int ch, const std::string& str, const sf::Color& col, const sf::Vector2f& pos) // This function sets multiple things at once - remove it.
>>>>>>> c7fa4fed0a1d2bd27f6d06cf469a71f4d1e6f675
{
    key.setPosition(pos);
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
<<<<<<< HEAD
    
=======

const sf::Vector2f& Button::getTextPosition() const // Redundant
{
    return text.getPosition();
}

>>>>>>> c7fa4fed0a1d2bd27f6d06cf469a71f4d1e6f675
Button::~Button()
{
}



