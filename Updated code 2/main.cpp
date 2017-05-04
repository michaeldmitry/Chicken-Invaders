#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Enemy.hpp"
#include"Player.hpp"
#include "Wave.hpp"
#include "Rocks.hpp"

int main(int, char const**)
{
    srand(int(time(NULL)));
    
    int chick_anim_counter = 0;
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(20);
    
    sf::Texture pic;
    if(!pic.loadFromFile(resourcePath() + "chicken keteer.png"))
        return EXIT_FAILURE;
    
    sf::Texture rock;
    if(!rock.loadFromFile(resourcePath() + "rock.png"))
        return EXIT_FAILURE;
    
    sf::Texture spaceship;
    if(!spaceship.loadFromFile(resourcePath() + "spaceship sprites.png"))
        return EXIT_FAILURE;
    //create player
    Player player;
    player.setPlayerPosition(sf::Vector2f(400,500));
    player.setPlayerTexture(&spaceship);
    player.setPlayerTextureRect(sf::IntRect(38,0,38,35));
    player.setPlayerScale((sf::Vector2f(2,2)));
    //create enemy
    sf::Vector2f base_pos(100, 100);
    
    sf::Texture egg;
    if(!egg.loadFromFile(resourcePath() + "egg.png"))
        return EXIT_FAILURE;
    
    Enemy enemy;
    
    enemy.setEnemyPosition(base_pos);
    enemy.setEnemyTexture(&pic);
    enemy.setEnemyOffset(sf::Vector2f(5, 0));
    enemy.setProjTexture(&egg);
    enemy.setEnemyTextureRect(sf::IntRect(0,0,99,70));
    enemy.setProjOffset(sf::Vector2f(0, 7));
    enemy.setProjSize(sf::Vector2f(50,40));
    enemy.setProjColor(sf::Color::White);
    
    sf::Vector2f off(enemy.getEnemySize().x/3, enemy.getEnemySize().y);
    enemy.setProjStartingOffset(off);
    
    Enemy r;
    
    //r.setEnemyPosition(sf::Vector2f(0,rand()%(window.getSize().y)));
    r.setEnemyTexture(&rock);
    r.setEnemyOffset(sf::Vector2f(7, 7));
    
    
    Wave wave1;
    
    wave1.createChickenWave(enemy, 2, 5);
    
    Rocks rock1;
    rock1.createRockWave(r, 10, window);
    
  
    
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
            //player.eraseProjectile(p);
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        player.setPlayerTextureRect(sf::IntRect(38, 0, 38, 35));
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player.moveX(window, 15);
            player.setPlayerTextureRect(sf::IntRect(76, 0, 38, 49));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player.moveX(window,-15);
            player.setPlayerTextureRect(sf::IntRect(0, 0, 38, 49));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player.moveY(window,-15);
            player.setPlayerTextureRect(sf::IntRect(38, 0, 38, 49));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.moveY(window,15);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            player.fire();
        }
        
        wave1.keepChickBounds(window);
        wave1.moveChickens();
        wave1.dropChickenEggs(window);
        wave1.changeChickenAnimation();
        wave1.eraseChicken(player);
        wave1.playerStatus(player);
        
      //  rock1.rotateRocks(45);
        //rock1.moveRocks();
        
        
        // Clear screen
        window.clear();
        player.drawPlayer(window);
        wave1.drawChickenWave(window);
        if( wave1.hasChickenWaveEnded())
        {
            cout<<"the end"<<endl;
            rock1.drawRockWave(window);
        }
        
                // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
