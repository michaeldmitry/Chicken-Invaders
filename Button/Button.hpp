#ifndef Button_hpp
#define Button_hpp
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <stdio.h>

// You shouldn't really give the user any hints of how the Button is implemented. The user shouldn't know about the RectangleShape and Text, only the Button as a whole. Check the comments marked (1)

class Button
{
private:
<<<<<<< HEAD
    sf::RectangleShape key;
    sf::Text text;
public:
    Button();
    Button(const sf::Vector2f& s, const sf::Color& c, const sf::Vector2f& p, const sf::Font& f, int ch, const std::string& str, const sf::Color& col, const sf::Vector2f& pos);
    
    void setButton(const sf::Vector2f& s, const sf::Color& c, const sf::Vector2f& p);
    void setButtonSize(const sf::Vector2f& s);
    void setButtonColor(const sf::Color& c);
    void setButtonPosition(const sf::Vector2f& p);
    
    void setText(const sf::Font& f, int ch, const std::string& str, const sf::Color& col, const sf::Vector2f& pos);
    void setTextFont(const sf::Font& f);
    void setTextCharacterSize(int ch);
    void setTextString(const std::string& str);
    void setTextColor(const sf::Color& col);
    void setTextPosition(const sf::Vector2f& pos);
    
    const sf::Vector2f& getButtonSize() const;
    const sf::Color& getButtonFillColor() const;
    const sf::Vector2f& getButtonPosition() const;

    int getTextCharacterSize() const;
    const std::string& getTextString() const;
    const sf::Color& getTextColor() const;
    const sf::Vector2f& getTextPosition() const;

=======
    sf::RectangleShape button;  // Think of renaming it as to not get confused between Button and button
    sf::Text text;
public:
    Button();
    Button(sf::RectangleShape b, sf::Text t); // (1)
    
    void setButton(sf::RectangleShape b); // (1)
    void setButtonSize(sf::Vector2f& s); // const reference
    void setButtonColor(sf::Color& c); // const reference
    void setButtonPosition(int& p); // Should the parameter be an int?
    
    void setText(sf::Text t); // (1)
    void setTextFont(sf::Font& f); // const reference
    void setTextCharacterSize(int& ch); // no need for reference for simple types like int
    void setTextString(std::string& str); // const reference
    void setTextColor(sf::Color& col); // const reference
    void setTextPosition(int& pos); // Should the parameter be an int?
    
    sf::Vector2f getButtonSize() const; // const reference return type
    sf::Color getButtonColor() const; // Rename to getButtonFillColor - const reference return type
    sf::Vector2f getButtonPosition() const; // const reference return type

    int getTextCharacterSize() const;
    std::string getTextString() const; // const reference return type
    sf::Color getTextColor() const; // const reference return type
    sf::Vector2f getTextPosition() const; // const reference return type
    
    sf::RectangleShape getButton() const; // (1)
    sf::Text getText() const; // (1)
>>>>>>> aa304019cc3751c716ef9312dd7bdae2a7bfe3a1
    ~Button();
};
#endif /* Button_hpp */
