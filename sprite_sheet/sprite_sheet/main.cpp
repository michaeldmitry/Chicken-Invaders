
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    sf::Clock clk, clk1;
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "chicken sprite 3.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect(0,0,80,97));
    
    sf::Texture spaceship;
    if (!spaceship.loadFromFile(resourcePath() + "spaceship sprites.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite space(spaceship);
    space.setTextureRect(sf::IntRect(0,0,38,49));
    space.setPosition(300, 300);
    int counter = 0;
    int counter1=0;
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setColor(sf::Color::Black);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }


    // Play the music
    music.play();

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
        }

        
        if(clk.getElapsedTime().asSeconds() >= 0.1){
            clk.restart();
        counter= (counter +1) %3;
        sprite.setTextureRect(sf::IntRect(counter * 80,0,80,97));
        
        }
        if(clk1.getElapsedTime().asSeconds() >= 0.1){
            clk1.restart();
            counter1 = (counter1 +1) %3;
            space.setTextureRect(sf::IntRect(counter1 * 38,0,38,49));
            
        }

        
        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);
        window.draw(space);
        // Draw the string
        //window.draw(text);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
