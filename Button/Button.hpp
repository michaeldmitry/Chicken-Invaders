#ifndef Button_hpp
#define Button_hpp
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <stdio.h>

class Button
{
private:
    sf::RectangleShape key;
    sf::Text text;
public:
    Button();
    ~Button();
    Button(const sf::Vector2f& s, const sf::Color& c, const sf::Vector2f& pos, const sf::Font& f, int ch, const std::string& str, const sf::Color& col);
    
    void setButtonSize(const sf::Vector2f& s);
    void setButtonColor(const sf::Color& c);
    void setButtonPosition(const sf::Vector2f& pos);

    void setTextFont(const sf::Font& f);
    void setTextCharacterSize(int ch);
    void setTextString(const std::string& str);
    void setTextColor(const sf::Color& col);
    
    const sf::Vector2f& getButtonSize() const;
    const sf::Color& getButtonFillColor() const;
    const sf::Vector2f& getButtonPosition() const;

    int getTextCharacterSize() const;
    const sf::String& getTextString() const;
    const sf::Color& getTextColor() const;
    
    void draw(sf::RenderWindow& window) const;
    bool isClicked(const sf::RenderWindow& window) const;
    
    void moveLeft(float p);
    void moveRight(float p);
    void moveUp(float p);
    void moveDown(float p);
    
    void setTexture(sf::Texture* pic);

};
#endif /* Button_hpp */
