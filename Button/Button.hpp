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
    void setButtonSize(sf::Vector2f& s);
    void setButtonColor(sf::Color& c);
    void setButtonPosition(int& p);
    
    void setText(sf::Text t);
    void setTextFont(sf::Font& f);
    void setTextCharacterSize(int& ch);
    void setTextString(std::string& str);
    void setTextColor(sf::Color& col);
    void setTextPosition(int& pos);
    
    sf::Vector2f getButtonSize() const;
    sf::Color getButtonColor() const;
    sf::Vector2f getButtonPosition() const;

    int getTextCharacterSize() const;
    std::string getTextString() const;
    sf::Color getTextColor() const;
    sf::Vector2f getTextPosition() const;
    
    sf::RectangleShape getButton() const;
    sf::Text getText() const;
    ~Button();
};
#endif /* Button_hpp */
