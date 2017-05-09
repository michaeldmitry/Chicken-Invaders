#include "Player.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

Player::Player()
{
    lives = 3;
    bullets.resize(1);
    col = sf::Color::Red;
    lost = false;
    numberOfBullets=1;
}

Player::~Player()
{
}

Player::Player(const sf::Vector2f& scale, const sf::Vector2f& pos,sf::Color c, sf::Texture* pic)
{
    setPlayerScale(scale);
    setPlayerPosition(pos);
    setPlayerColor(c);
    setPlayerTexture(pic);
    numberOfBullets=1;
}

void Player::setPlayerScale(const sf::Vector2f& scale)
{
    player.setScale(scale);
}

void Player::setPlayerColor(const sf::Color& col)
{
    player.setColor(col);
}

void Player::setPlayerPosition(const sf::Vector2f& pos)
{
    player.setPosition(pos);
}

void Player::setPlayerTexture(sf::Texture* pic)
{
    player.setTexture(*pic);
}

void Player::setNumOfLives()
{
    lives = 3;
}

void Player::incrementLives()
{
    lives++;
}

void Player::decrementLives()
{
    lives--;

    if(lives < 1)
    {
        lost = true;
        
    }
    
    
}

void Player::setNumberOfBullets(int i)
{
    if(i<=3 && i>0)
    numberOfBullets=i;
}
void Player:: incrementBullets()
{
    if(numberOfBullets<=2)
        numberOfBullets++;
}

void Player:: decrementBullets()
{
    if(numberOfBullets>=1)
        numberOfBullets--;
}

void Player::moveX(sf::RenderWindow& window, float p)
{
    if ((p > 0) && (getPlayerPosition().x + getPlayerSize().x + p  + 5< (window.getSize().x)))
        player.move(p, 0);
    else {
        if ((p < 0) && (getPlayerPosition().x + p  - 5> 0))
            player.move(p, 0);}
}

void Player::moveY(sf::RenderWindow& window, float p)
 {
    if ((p > 0) && (player.getPosition().y + getPlayerSize().y + p  + 5< (window.getSize().y)))
        player.move(0, p);
    else {
        if ((p < 0) && (player.getPosition().y + p - 5 > 0))
            player.move(0,p);}
}

void Player::move(float x, float y)
{
    player.move(x, y);
}

void Player::drawPlayer(sf::RenderWindow& window)
{
   if(!isDead())
        window.draw(player);
    
    for(int i = 0; i < bullets.size(); i++)
        for(int j=0;j<bullets[i].size();j++)
            if(bullets[i][j].getProjectilePosition().y < 0)
        {
            bullets[i].erase(bullets[i].begin() + j);
            j--;
        }
    for(int i = 0; i < bullets.size(); i++)
        for(int j=0;j<bullets[i].size();j++)
        {
            bullets[i][j].drawProjectile(window);
        }
}

bool Player::isDead()
{
    if(lost)
    {
        lives=0;
        return true;
    }
    
    if (lives == 0)
        return true;
    else
        return false;
}

bool Player::isCollide(sf::RectangleShape& object, int i, int j)
{
    return (bullets[i][j].getProjectileGlobalBounds().intersects(object.getGlobalBounds()));
}

void Player::eraseProjectile(sf::RectangleShape& object)
{
    for (int i = 0; i < bullets.size(); i++){
        for(int j=0;j<bullets[i].size();j++)
            if (isCollide(object, i, j))
            {
                bullets[i].erase(bullets[i].begin() + j);
                j--;
            }
        if(bullets[i].size()==0)
            bullets.erase(bullets.begin()+i--);
    }
}
void Player::eraseProjectile(int i, int j)
{
    if(i < bullets.size() && i >= 0 && j>=0 && bullets[i].size()>j)
    {  bullets[i].erase(bullets[i].begin() + j);
        if(bullets[i].size()==0)
            bullets.erase(bullets.begin()+i);
    }
}

sf::Vector2f Player::getPlayerScale() const
{
    return player.getScale();
}

sf::Color Player::getPlayerColor() const
{
    return player.getColor();
}

sf::Vector2f Player::getPlayerPosition() const
{
    return player.getPosition();
}

int Player::getNumOfLives() const
{
    return lives;
}
int Player::getNumOfBullets() const
{
    return bullets.size();
}

int Player:: getNumOfBullets(int i) const
{
    if(i<bullets.size() && i>=0)
    {
        return bullets[i].size();
    }
    
}
void Player::fire()
{
    if(!lost && clock.getElapsedTime().asSeconds()>= 0.125){
        vector<Projectile> new_bullets;
        Projectile projectile;
        projectile.setProjectileColor(sf::Color::Red);
        projectile.setProjectileSize(sf::Vector2f(5, 15));
        
        int middle_x = getPlayerPosition().x + getPlayerSize().x/2 ;
        int top_y = getPlayerPosition().y - projectile.getProjectileSize().y;
        int offset_x = 0;
        
        int position_x=middle_x;
        
        for(int i = 0; i < numberOfBullets; i++){
            switch(numberOfBullets)
            {
                case 1:
                    offset_x = 0;

                    position_x = middle_x;
                    break;
                case 2:
                    offset_x = 0;

                    if(i == 0)
                        position_x = middle_x - getPlayerSize().x / 6;
                    else
                        position_x = middle_x + getPlayerSize().x / 6;
                    break;
                case 3:
                    position_x = middle_x;
                    offset_x = 0;
                    if(i == 0){
                        offset_x = -2;

                        position_x = middle_x - getPlayerSize().x / 6;
                    }
                    if(i == 2){
                        offset_x = 2;
                        position_x = middle_x + getPlayerSize().x / 6;
                    }
                    break;
                    
            }
            projectile.setProjectilePosition(sf::Vector2f(position_x , top_y));
            projectile.setProjectileOffset(sf::Vector2f(offset_x, -15));
            new_bullets.push_back(projectile);
        }
        
        for(int i = 0; i < numberOfBullets; i++)
            new_bullets[i].fire();
        bullets.push_back(new_bullets);
        clock.restart();
        
    }
}

sf::Rect<float> Player::getProjectileGlobalBounds(int i, int j)
{
    if (i < bullets.size() && i >= 0 && j>=0 && bullets[i].size()>j)
        return bullets[i][j].getProjectileGlobalBounds();
    else
        return sf::Rect<float>(sf::Vector2f(-10000, -10000), sf::Vector2f(0, 0));
}

sf::Rect<float> Player::getPlayerGlobalBounds()
{
    return player.getGlobalBounds();
}

void Player::killplayer()
{
    lost = true;
}

void Player::setPlayTexture(sf::Texture* pic)
{
    proj_texture = pic;
}

void Player::setPlayOffset(const sf::Vector2f& o)
{
    proj_offset = o;
}

void Player::setPlayColor(const sf::Color& col)
{
    proj_color = col;
}

void Player::setPlaySize(const sf::Vector2f& s)
{
    proj_size = s;
}
void Player::setPlayStartingOffset(sf::Vector2f& s)
{
    proj_startingOffset = s;
}

sf::Vector2f Player::getPlayerSize() const
{
    return sf::Vector2f (player.getGlobalBounds().width, player.getGlobalBounds().height);
}

void Player::setPlayerTextureRect(const sf::IntRect& R)
{
    player.setTextureRect(R);
}

void Player::setPlayerName(const string &n)
{
    name = n;
}
string Player::getPlayerName()
{
    return name;
}

