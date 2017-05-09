#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "ChickenWave.hpp"
#include "RockWave.hpp"
#include "BeastWave.hpp"
#include "Button.hpp"
#include "Menu.hpp"
#include "Highscores.h"

void drawText(sf::RenderWindow& window, const string& word, const sf::Vector2f& pos, const sf::Font& font, const sf::Texture& b);

int main(int, char const**)
{
    srand(int(time(NULL)));
    
    sf::Clock starting_clock;
    
    int chick_anim_counter = 0;
    
    int lives_counter;
    
    vector<Highscores::data> scores;
    
    Highscores score("Source1.txt");
    
    if (!score.openScores())
        std::cout << "Error" << std::endl;
    
    score.getScore(scores);
    
    sf::Font Font;
    if(!Font.loadFromFile(resourcePath() + "sansation.ttf"))
        return EXIT_FAILURE;
    
    sf::Text header;
    header.setFont(Font);
    header.setString("Enter Your Name:");
    header.setPosition(300, 100);
    header.setCharacterSize(40);
    
    
    sf::Text highscore_window;
    highscore_window.setFont(Font);
    highscore_window.setString("Player Name       Score ");
    highscore_window.setCharacterSize(40);
    sf::Text text;
    text.setFont(Font);
    vector<sf::Text> scoreText;
    
    sf::Text enter_your_name;
    enter_your_name.setCharacterSize(35);
    enter_your_name.setFont(Font);
    
    int which_window = 9;
    
    sf::Sprite menuSprite1, menuSprite2;
    sf::Texture menuTexture1, menuTexture2;
    if (!menuTexture1.loadFromFile(resourcePath()+"Chickeninvaders.jpg"))
        return EXIT_FAILURE;
    if (!menuTexture2.loadFromFile(resourcePath()+"big chicken 1.png"))
        return EXIT_FAILURE;
    menuSprite1.setTexture(menuTexture1);
    menuSprite1.setPosition(150, 0);
    menuSprite2.setTexture(menuTexture2);
    menuSprite2.setPosition(300, 200);
    
    sf::Texture usernameBackground;
    if (!usernameBackground.loadFromFile(resourcePath()+"spaceshp background.jpg"))
        return EXIT_FAILURE;
    sf::RectangleShape usernameSprite;
    usernameSprite.setTexture(&usernameBackground);
    usernameSprite.setSize(sf::Vector2f(800, 600));
    
    
    sf::Sprite fork;
    sf::Texture forkTexture;
    if (!forkTexture.loadFromFile(resourcePath()+"fork.png"))
        return EXIT_FAILURE;
    fork.setTexture(forkTexture);
    fork.setScale(2, 2);
    
    
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath()+"earth background.jpg"))
        return EXIT_FAILURE;
    
    
    
    Button b(sf::Vector2f(300, 50), sf::Color(64, 0, 128), sf::Vector2f(270, 240), Font, 35, "Begin Your Journey", sf::Color::White);
    Button n(sf::Vector2f(210, 50), sf::Color(64, 0, 128), sf::Vector2f(270, 380), Font, 35, "Hall of Fame", sf::Color::Cyan);
    Button c(sf::Vector2f(100, 50), sf::Color(64, 0, 128), sf::Vector2f(270, 500), Font, 35, "Quit", sf::Color::Cyan);
    
    Menu menu(sf::Vector2f(800, 600));
    menu.addButton(b);
    menu.addButton(n);
    menu.addButton(c);
    menu.setBackground(&texture);
    menu.loadMusic("Main_Menu.ogg");
    
    sf::Texture background;
    if(!background.loadFromFile(resourcePath() + "space background.jpg"))
        return EXIT_FAILURE;
    
    sf::RectangleShape highscore_background;
    highscore_background.setTexture(&background);
    highscore_background.setSize(sf::Vector2f(800, 600));
    
    sf::SoundBuffer buffer_laser, buffer_chicken;
    buffer_laser.loadFromFile(resourcePath() + "Laser.ogg");
    buffer_chicken.loadFromFile(resourcePath() + "Chicken.ogg");
    
    sf::Sound sound_laser, sound_chicken;
    sound_laser.setBuffer(buffer_laser);
    sound_chicken.setBuffer(buffer_chicken);

    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(20);
    
    Enemy menu_chicken;
    menu_chicken.setEnemyPosition(sf::Vector2f(rand() % window.getSize().y, -10));
    menu_chicken.setEnemyTexture(&menuTexture2);
    menu_chicken.setEnemyOffset(sf::Vector2f(0, 2));
    menu_chicken.setEnemyScale(sf::Vector2f(0.5, 0.5));
    vector<Enemy>menu_chickens;
    menu_chickens.push_back(menu_chicken);

    
    sf::Texture pic;
    if(!pic.loadFromFile(resourcePath() + "chicken keteer.png"))
        return EXIT_FAILURE;
    sf::Texture spaceship;
    if(!spaceship.loadFromFile(resourcePath() + "spaceship sprites.png"))
        return EXIT_FAILURE;
    
    sf::Texture pickup1;
    if(!pickup1.loadFromFile(resourcePath() + "gift copy.png"))
        return EXIT_FAILURE;
    sf::Texture pickup2;
    if(!pickup2.loadFromFile(resourcePath() + "gift 3.png"))
        return EXIT_FAILURE;
    sf::Texture pickup3;
    if(!pickup3.loadFromFile(resourcePath() + "gift 2.png"))
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
    sf::Texture r1;
    if(!r1.loadFromFile(resourcePath() + "rock.png"))
        return EXIT_FAILURE;
    sf::Texture b1;
    if(!b1.loadFromFile(resourcePath() + "Beast3_sprite.png"))
        return EXIT_FAILURE;
    sf::Texture b2;
    if(!b2.loadFromFile(resourcePath() + "Beast4_sprite.png"))
        return EXIT_FAILURE;
    sf::Texture b3;
    if(!b3.loadFromFile(resourcePath() + "Beast1_sprite.png"))
        return EXIT_FAILURE;
    
    string str;
    
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
    
    ChickenWave chickenwave1;
    
    chickenwave1.createChickenWave(enemy, 2 , 3);
    chickenwave1.setBackgroundTexture(&background);
    chickenwave1.setPickTexture(&pickup1, &pickup2, &pickup3);
    
    Enemy rock;
    
    RockWave rockwave;
    rockwave.createRockWave(rock, 7, window);
    
    rockwave.setRockTexture(&r1);
    rockwave.setRockOffset(sf::Vector2f(3,3));
    rockwave.setRockTextureRect(sf::IntRect(0,0,59,54));
    rockwave.setRockScale();
    rockwave.setWaveBackground(&background);
    
    BeastWave beast;
    beast.setNumOfBeasts();
    beast.setBeastPosition(200,200, 0);
    beast.setBeastTexture(&b1, 0);
    beast.setBeastTextureRect(sf::IntRect(0,0,193,170));
    beast.setBeastScale(sf::Vector2f(1.25,1.25),0);
    beast.setX_size(193);
    beast.setY_size(170);
    beast.setNumOfSprites(2);
    beast.setWaveBackground(&background);
    beast.setProjTexture(&egg);
    beast.setProjOffset(sf::Vector2f(0,7));
    beast.setProjSize(sf::Vector2f(50,40));
    beast.setProjColor(sf::Color::White);
    beast.setPickTexture(&pickup1,&pickup2, &pickup3);
    
    sf::Vector2f offset(beast.getBeastSize(0).x/3, beast.getBeastSize(0).y);
    beast.setProjStartingOffset(offset);
    //beast.playBeastWave(player, window);
    
    ChickenWave chickenwave2;
    
    chickenwave2.createChickenWave(enemy, 3 , 4);
    chickenwave2.setBackgroundTexture(&background);
    chickenwave2.setPickTexture(&pickup1, &pickup2, &pickup3);
    
    
    RockWave rockwave2;
    rockwave2.createRockWave(rock, 13, window);
    
    rockwave2.setRockTexture(&r1);
    rockwave2.setRockOffset(sf::Vector2f(3,3));
    rockwave2.setRockTextureRect(sf::IntRect(0,0,59,54));
    rockwave2.setRockScale();
    rockwave2.setWaveBackground(&background);
    
    BeastWave beast2;
    beast2.setNumOfBeasts();
    beast2.setBeastPosition(200,200, 0);
    beast2.setBeastTexture(&b2, 0);
    beast2.setBeastTextureRect(sf::IntRect(0,0,193,170));
    beast2.setBeastScale(sf::Vector2f(1.25,1.25),0);
    beast2.setX_size(193);
    beast2.setY_size(170);
    beast2.setNumOfSprites(2);
    beast2.setWaveBackground(&background);
    beast2.setProjTexture(&egg);
    beast2.setProjOffset(sf::Vector2f(0,7));
    beast2.setProjSize(sf::Vector2f(50,40));
    beast2.setProjColor(sf::Color::White);
    beast2.setProjStartingOffset(offset);
    beast2.setPickTexture(&pickup1,&pickup2, &pickup3);
    
    
    ChickenWave chickenwave3;
    
    chickenwave3.createChickenWave(enemy, 4 , 4);
    chickenwave3.setBackgroundTexture(&background);
    chickenwave3.setPickTexture(&pickup1, &pickup2, &pickup3);
    
    
    RockWave rockwave3;
    rockwave3.createRockWave(rock, 20, window);
    
    rockwave3.setRockTexture(&r1);
    rockwave3.setRockOffset(sf::Vector2f(3,3));
    rockwave3.setRockTextureRect(sf::IntRect(0,0,59,54));
    rockwave3.setRockScale();
    rockwave3.setWaveBackground(&background);
    
    BeastWave beast3;
    beast3.setNumOfBeasts();
    beast3.setBeastPosition(200,200, 0);
    beast3.setBeastTexture(&b3, 0);
    beast3.setBeastTextureRect(sf::IntRect(0,0,193,170));
    beast3.setBeastScale(sf::Vector2f(1.25,1.25),0);
    beast3.setX_size(193);
    beast3.setY_size(170);
    beast3.setNumOfSprites(2);
    beast3.setWaveBackground(&background);
    beast3.setProjTexture(&egg);
    beast3.setProjOffset(sf::Vector2f(0,7));
    beast3.setProjSize(sf::Vector2f(50,40));
    beast3.setProjColor(sf::Color::White);
    beast3.setProjStartingOffset(offset);
    beast3.setPickTexture(&pickup1,&pickup2, &pickup3);
    
    
    sf::Clock change_windows;
    change_windows.restart();
    
    int my_score = 0;
    
    while(change_windows.getElapsedTime().asSeconds()<=3){}
    
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
        if (event.type == sf::Event::Closed)
            {
            window.close();
            }
        
        // Escape pressed: exit
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            if(event.type == sf::Event::TextEntered)
            {
                // Handle ASCII characters only
              
                
             if (event.text.unicode == 10)
                {
                  //cout<<"here"<<endl;
                  which_window = 10;
                }
             else  if (event.text.unicode >32 && event.text.unicode<=126)
             {
                 str += static_cast<char>(event.text.unicode);
                 enter_your_name.setString(str);
                 enter_your_name.setPosition(sf::Vector2f(300, 200));
             }
              else  if (event.text.unicode ==8)
                {
                    str = str.substr(0, str.length() - 1);
                    enter_your_name.setString(str);
                }
            }
            
            if (event.type == sf::Event::MouseMoved)
            {
                fork.setPosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
                
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (menu.isClicked(0, window))
                        which_window = 0;
                    else if (menu.isClicked(1, window))
                        which_window = 11;
                }
            }
        }
        player.setPlayerName(str);
        
    switch(which_window)
    {
            case 0:
                menu.stopMusic();
                drawText(window, "Level 1", sf::Vector2f(300, 200), Font, background);
                drawText(window, "Wave 1: Revenge of the Yolk", sf::Vector2f(100, 300), Font, background);
                //score.setScore(chickenwave1.returnScore(),player.getPlayerName());
                //score.saveScores();
                chickenwave1.playChickenWave(window, player, my_score);
                if (chickenwave1.hasChickenWaveEndedbyDeath(player))
                {
                    drawText(window, "YOU LOST!", sf::Vector2f(300, 250), Font, background);
                    //score.updateScores(player.getPlayerName(), my_score);
                    score.saveScores();
                    which_window = 11;
                }
                else if (chickenwave1.hasChickenWaveEndedNormally())
                {
                    drawText(window, "YOU WON!", sf::Vector2f(300, 250), Font, background);
                    which_window = 1;
                }

                break;
                
            case 1:
                drawText(window, "Wave 2: Heads Up", sf::Vector2f(200, 200), Font, background);
                rockwave.playRockWave(window, player, my_score);
            
               if (rockwave.hasRockWaveEndedbyDeath(player))
                {
                    drawText(window, "YOU LOST!", sf::Vector2f(300, 250), Font, background);
                   // score.saveScores();
                    which_window = 11;
                }

               else
               if (rockwave.hasRockWaveEndedNormally())
                {
                    drawText(window, "YOU WON!", sf::Vector2f(300, 250), Font, background);
                    which_window = 2;
                }
                                break;
                
            case 2:
                drawText(window, "Wave 3: Defeat the Beast", sf::Vector2f(150, 200), Font, background);
                beast.playBeastWave(player, window, my_score);
            
            if (beast.hasBeastWaveEndedbyDeath(player))
                {
                    drawText(window, "YOU LOST!", sf::Vector2f(300, 250), Font, background);
                    which_window = 11;
                }
            else
                if (beast.hasBeastWaveEndedNormally())
            {
                drawText(window, "YOU WON!", sf::Vector2f(300, 250), Font, background);
                which_window = 3;
            }
                break;
                
            case 3:
                drawText(window, "Level 2", sf::Vector2f(300, 200), Font,background);
                drawText(window, "Wave 1: The next Wave", sf::Vector2f(150, 300), Font,background);
                chickenwave2.playChickenWave(window, player, my_score);
            
            if (chickenwave2.hasChickenWaveEndedbyDeath(player))
                {
                    drawText(window, "YOU LOST!", sf::Vector2f(300, 250), Font,background);
                    which_window = 11;
                }
            else
                if (chickenwave2.hasChickenWaveEndedNormally())
            {
                drawText(window, "YOU WON!", sf::Vector2f(300, 250), Font,background);
                which_window = 4;
            }
                break;
                
            case 4:
                drawText(window, "Wave 2: Rock Your Way Out", sf::Vector2f(150, 200), Font,background);
                rockwave2.playRockWave(window, player, my_score);
            
            if (rockwave2.hasRockWaveEndedbyDeath(player))
                {
                    drawText(window, "YOU LOST!", sf::Vector2f(300, 250), Font,background);
                    which_window = 11;
                }
           else
               if (rockwave2.hasRockWaveEndedNormally())
            {
                drawText(window, "YOU WON!", sf::Vector2f(300, 250), Font,background);
                which_window = 5;
            }
                break;
                
            case 5:
                drawText(window, "Wave 3: Ghost Busters", sf::Vector2f(150, 200), Font, background);
                beast2.playBeastWave(player, window, my_score);
            
            if (beast2.hasBeastWaveEndedbyDeath(player))
                {
                    which_window = 11;
                }
            else
                if (beast2.hasBeastWaveEndedNormally())
            {
                drawText(window, "YOU WON!", sf::Vector2f(300, 250), Font, background);
                which_window = 6;
            }
            break;
            
            case 6:
                drawText(window, "Level 3", sf::Vector2f(300, 250), Font, background);
                drawText(window, "Wave 1: Ultimate Omelette", sf::Vector2f(100, 200), Font, background);
                chickenwave3.playChickenWave(window, player, my_score);
                
            
            if (chickenwave3.hasChickenWaveEndedbyDeath(player))
                {
                    drawText(window, "YOU LOST!", sf::Vector2f(300, 250), Font, background);
                    which_window = 11;
                }
            else
                if (chickenwave3.hasChickenWaveEndedNormally())
                {
                    drawText(window, "YOU WON!", sf::Vector2f(300, 250), Font, background);
                    which_window = 7;
                }
                break;
                
            case 7:
                drawText(window, "Wave 2: Rock Attack", sf::Vector2f(150, 200), Font, background);
                rockwave3.playRockWave(window, player, my_score);
                
            if (rockwave3.hasRockWaveEndedbyDeath(player))
                {
                    drawText(window, "YOU LOST!", sf::Vector2f(300, 250), Font, background);
                    which_window = 11;
                }
            else
                if (rockwave3.hasRockWaveEndedNormally())
            {
                drawText(window, "YOU WON!", sf::Vector2f(300, 250), Font, background);
                which_window = 8;
            }

                break;
                
            case 8:
                drawText(window, "Wave 3: Cluck of the Dark Side", sf::Vector2f(100, 200), Font, background);
                beast3.playBeastWave(player, window, my_score);
                
            if (beast3.hasBeastWaveEndedbyDeath(player))
                {
                    drawText(window, "YOU ARE ALMOST A TRUE CHICKEN INVADER!", sf::Vector2f(50, 200), Font, background);
                    which_window = 11;
                }
            else if (beast3.hasBeastWaveEndedNormally())
            {
                drawText(window, "YOU ARE A TRUE CHICKEN INVADER!", sf::Vector2f(70, 200), Font, background);
                which_window = 11;
            }
                break;
        case 9:
        {
            my_score = 0;
            window.clear();
            window.draw(usernameSprite);
            window.draw(header);
            window.draw(enter_your_name);
            window.display();
        }break;
            
        case 10:
        {
            my_score = 0;
            window.clear();
            menu.drawMenu(window);
            window.draw(menuSprite1);
            window.draw(menuSprite2);
            window.draw(fork);
            menu_chickens[0].move();
            menu_chickens[0].drawEnemy(window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (fork.getGlobalBounds().intersects(menu_chickens[0].getEnemyGlobalBounds())))
            {
                menu_chicken.setEnemyPosition(sf::Vector2f(rand() % window.getSize().y, -10));
                menu_chickens.push_back(menu_chicken);
                menu_chickens.erase(menu_chickens.begin());
            }
            window.display();
        }break;
        
        case 11:
        {
            score.setScore(my_score, player.getPlayerName());
            
           // score.saveScores();
           // score.openScores();
            score.getScore(scores);
            scoreText.resize(0);
            for (int i = 0; i < scores.size(); i++)
            {
                
                text.setString(scores[i].name + "       " + to_string(scores[i].score));
                scoreText.push_back(text);
                scoreText[i].setPosition(sf::Vector2f(100, 100+30 * i));
            }
            window.clear();
            window.draw(highscore_background);
            window.draw(highscore_window);
            for (int i = 0; i < scores.size(); i++)
                window.draw(scoreText[i]);
            //score.drawScoresToWindow(window);
            window.display();
        }break;
    
    }
}
    score.saveScores();
    std::cout << "Saving scores .." << std::endl;
    return EXIT_SUCCESS;
}

void drawText(sf::RenderWindow& window, const string& word, const sf::Vector2f& pos, const sf::Font& font, const sf::Texture& b)
{
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(40);
    text.setPosition(pos);
    text.setString(word);
    sf::Clock clk;
    sf::Sprite back(b);
    
    while (window.isOpen() && clk.getElapsedTime().asSeconds()<3)
    {
        window.clear();
        window.draw(back);
        window.draw(text);
        window.display();
    }
}
