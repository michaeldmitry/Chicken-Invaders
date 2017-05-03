
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

#include "Projectile.hpp"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(30);
    
    Projectile x;
    x.setProjectileSize(sf::Vector2f(5, 15));
    x.setProjectileColor(sf::Color::Red);
    x.setProjectileOffset(sf::Vector2f(0, -10));
    x.setProjectilePosition(sf::Vector2f(400, 580));

    
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
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                x.fire();
            }
            
        }
        
        if(x.isFired() && x.getProjectilePosition().y < 0){
            x.stopFire();
        }
        // Clear screen
        window.clear();
        
        x.drawProjectile(window);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
