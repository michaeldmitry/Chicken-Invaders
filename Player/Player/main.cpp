
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
#include "Player.hpp"
#include "Projectile.hpp"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(20);

    Player player(sf::Vector2f(50,50),sf::Color::Blue,sf::Vector2f(400,500));

    


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
           
            
        }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        player.moveX(5);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.moveX(-5);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.moveY(-5);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.moveY(5);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        player.fire();
    }
        //for(int i = 0; i < projectileArray.size(); i++)
        //{
           // projectile.fire();
      //  }
    
        
        // Clear screen
        window.clear();
        player.drawPlayer(window);
       
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
