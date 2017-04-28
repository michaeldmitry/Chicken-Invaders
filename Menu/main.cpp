

//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include "Menu.hpp"
#include <iostream>

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    string x="earth background.jpg";

    //Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + x)) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    Button b(sf::Vector2f(260, 100), sf::Color::Red, sf::Vector2f(270, 50), font, 50, "Highscores", sf::Color::White);
    Button n(sf::Vector2f(200, 100), sf::Color::Black, sf::Vector2f(300, 190), font, 50, "nour", sf::Color::White);

    Menu menu(sf::Vector2f(800, 600));
    menu.addButton(b);
    menu.addButton(n);
    menu.setBackground(&texture);
    menu.loadMusic("nice_music.ogg");
    
    // Create a graphical text to display
    
    sf::Text text("Hello SFML", font, 50);
    text.setColor(sf::Color::Black);
    
    // Load a music to play
    //sf::Music music;
    //if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
      //  return EXIT_FAILURE;
    //}
    // Play the music
   // music.play();
    std::cout << menu.getNumOfButtons() << std::endl;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(menu.isClicked(1, window)){
                    cout<<"true" << endl;
                }
            }
            
        }
        
        // Clear screen
        window.clear();
        
        // Draw the sprite
      // window.draw(sprite);
        menu.drawMenu(window);

        // Draw the string
        window.draw(text);
        
        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
