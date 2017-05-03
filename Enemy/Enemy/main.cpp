#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Enemy.hpp"
#include"Player.hpp"

bool isChickenHitByBullet(Player& p, Enemy& e);
void eraseChicken(Player& p, vector <Enemy>& e);

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
     window.setFramerateLimit(20);
    
    sf::Texture pic;
    if(!pic.loadFromFile(resourcePath() + "big chicken 1.png"))
        return EXIT_FAILURE;
    
    sf::Texture spaceship;
    if(!spaceship.loadFromFile(resourcePath() + "airplane shooter-2.png"))
        return EXIT_FAILURE;
//create player
    Player player(sf::Vector2f(150,250),sf::Vector2f(400,500),sf::Color::White, &spaceship);
    //create enemy
    Enemy enemy(sf::Vector2f(200,200),sf::Vector2f(400,200),sf::Color::White);

    vector<Enemy> e;
    
    e.push_back(enemy);
    //e[0].setEnemyTexture(&pic);
    e[0].setEnemySprite(window);
    player.setPlayerTexture(&spaceship);
    
    //enemy.setEnemyTexture(&pic);
    
    sf::Texture egg;
    if(!egg.loadFromFile(resourcePath() + "egg.png"))
        return EXIT_FAILURE;

  
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
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.moveX(window, 15);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.moveX(window,-15);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.moveY(window,-15);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.moveY(window,15);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            player.fire();
        }
        
       // std::cout << e.size() << std::endl;

        for(int i = 0 ; i < e.size() ; i++){
        if(e[i].limitXneg(window, 15))
            e[i].moveX(window, 15);
        else
            if(e[i].limitXpos(window, -15))
            e[i].moveX(window, -15);
        }
        
        
        for(int i = 0 ; i < e.size(); i++){
            if(rand()%50==rand()%50)
                e[i].dropEgg(window, &egg);
                
        }

        eraseChicken(player, e);
  
        
        for(int i = 0; i < e.size(); i++)
            if(e[i].isPlayerDead(player))
                player.killplayer();
        
        
        // Clear screen
        window.clear();
        player.drawPlayer(window);

        for(int i = 0; i < e.size(); i++)
            e[i].drawEnemy(window);
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

bool isChickenHitByBullet(Player& p, Enemy& e)
{
    for(int i = 0; i < p.getNumOfBullets(); i++)
        if(e.getEnemyGlobalBounds().intersects(p.getProjectileGlobalBounds(i)))
        {
            p.eraseProjectile(i);
            i--;
            return true;
        }
    return false;
}

void eraseChicken(Player& player, vector <Enemy>& e)
{
    for (int i = 0; i < e.size(); i++)
    if (isChickenHitByBullet(player, e[i])==true)
    {
        e.erase(e.begin() + i);
        i--;
    }
    
}

