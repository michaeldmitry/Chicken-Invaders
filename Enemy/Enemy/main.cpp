#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Enemy.hpp"
#include"Player.hpp"


#define RATE_EGGS 1000
#define DOUBLE_FOR_LOOP for(int i = 0; i < E.size(); i++) for(int j = 0; j < E[i].size(); j++)

bool isChickenHitByBullet(Player& p, Enemy& e);
void eraseChicken(Player& p, vector <Enemy>& e);
void changeChickenAnimation(Enemy& chicken, int& counter);

bool checkChickenBoundary(const sf::RenderWindow& window, const Enemy& chicken);
bool shouldDropEgg();


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
    enemy.setProjSize(sf::Vector2f(40,40));
    enemy.setProjColor(sf::Color::White);
    
    sf::Vector2f off(enemy.getEnemySize().x/3, enemy.getEnemySize().y);
    enemy.setProjStartingOffset(off);
    
    vector<vector<Enemy>> E;
    
    for(int i = 0; i < 2; i++)
    {
        vector<Enemy> f;
        for(int j = 0; j < 5; j++)
        {
            f.push_back(enemy);
            f[j].setEnemyPosition(sf::Vector2f(base_pos.x + (f[j].getEnemySize().x + 20) * j, base_pos.y + (f[j].getEnemySize().y + 10) * i));
        }
        E.push_back(f);
    }
    
    
    
    
    sf::Clock chick_anim_clk;
    
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
        
        
        for(int i = 0; i < E.size(); i++)
            if(E[i].size() > 0)
                if(checkChickenBoundary(window, E[i][0]) || checkChickenBoundary(window, E[i][E[i].size()-1]))
                    for(int j = 0; j < E[i].size(); j++)
                        E[i][j].setEnemyOffset(sf::Vector2f(0, 0) - E[i][j].getEnemyOffset());
        
        DOUBLE_FOR_LOOP
        E[i][j].move();
        
        for(int i = 0; i < E.size(); i++)
            for(int j = 0; j < E[i].size(); j++)
                if(shouldDropEgg())
                {
                    E[i][j].dropEgg(window);
                }
        
        if(chick_anim_clk.getElapsedTime().asSeconds() >= 0.1)
        {
            chick_anim_counter= (chick_anim_counter +1) %3;
            
            for(int i = 0; i < E.size(); i++)
                for(int j = 0; j < E[i].size(); j++)
                    changeChickenAnimation(E[i][j], chick_anim_counter);
            
            chick_anim_clk.restart();
        }
        
        for(int i=0; i<E.size();i++){
            eraseChicken(player, E[i]);
        }
        
        for(int i = 0; i < E.size(); i++)
            for (int j = 0; j < E[i].size(); j++)
                if(E[i][j].isPlayerDead(player))
                    player.killplayer();
        
        
        // Clear screen
        window.clear();
        player.drawPlayer(window);
        
        for(int i = 0; i < E.size(); i++)
            for (int j = 0; j < E[i].size(); j++)
                E[i][j].drawEnemy(window);
        
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

void changeChickenAnimation(Enemy& chicken, int& counter)
{
    chicken.setEnemyTextureRect(sf::IntRect(0,counter * 70,99,70));
}

bool checkChickenBoundary(const sf::RenderWindow& window, const Enemy& chicken)
{
    if(chicken.getEnemyOffset().x > 0 && chicken.getEnemyPosition().x + chicken.getEnemySize().x + 10 > window.getSize().x)
        return true;
    
    if(chicken.getEnemyOffset().x < 0 && chicken.getEnemyPosition().x - 10 < 0)
        return true;
    
    return false;
}

bool shouldDropEgg()
{
    return (rand() % RATE_EGGS == rand() % RATE_EGGS);
}

