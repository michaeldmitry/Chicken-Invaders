#ifndef Button_hpp
#define Button_hpp
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <stdio.h>

class Button
{
private:
    sf::RectangleShape button;
    sf::Text text;
public:
    Button();
    Button(sf::RectangleShape b, sf::Text t);
    
    void setButton(sf::RectangleShape b);
    void setButtonSize(sf::RectangleShape b);
    void setButtonColor(sf::RectangleShape b);
    void setButtonPosition(sf::RectangleShape b);
    
    void setText(sf::Text t);
    void setTextFont(sf::Text t);
    void setTextCharacterSize(sf::Text t);
    void setTextString(sf::Text t);
    void setTextColor(sf::Text t);
    void setTextPosition(sf::Text t);
    
    sf::RectangleShape getButtonSize() const;
    sf::RectangleShape getButtonColor() const;
    sf::RectangleShape getButtonPosition() const;
    
    sf::Text getTextFont() const;
    sf::Text getTextCharacterSize() const;
    sf::Text getTextString() const;
    sf::Text getTextColor() const;
    sf::Text getTextPosition() const;
    
    sf::RectangleShape getButton() const;
    sf::Text getText() const;
    ~Button();
};
#endif /* Button_hpp */
