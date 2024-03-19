#include "player.h"
#include <iostream>
/**
 * @brief Constructs a new player which will have its position set to the beginning of the maze.
 * 
 */
player::player()
{
    if(!stillTexture.loadFromFile("player.png"))
        {
            std::cout << "Error opening file\n";
            exit(1);
        } 
    if(!mvTexture.loadFromFile("playermv.png"))
        {
            std::cout << "Error opening file\n";
            exit(1);
        }  
    sf::Vector2u imageSize = stillTexture.getSize();
    plyr.setTexture(stillTexture);  //Sets player texture to pacman
    plyr.setPosition(110,120);      
    plyr.scale(1,1);          
    plyr.setOrigin(imageSize.x/2, imageSize.y/2);  

}
/**
 * @brief Destroys the player sprite which will reduce the lives by 1;
 * 
 */
player::~player()
{
    lives--;
}
void player::draw(sf::RenderTarget& target,sf::RenderStates direction) const
{
    target.draw(plyr, direction);
}
/**
 * @brief Moves the player in a certain direction within the bounds of the window
 * 
 * @param dir direction player is to move in
 * @param window game window
 */
void player::move(direction &dir, sf::RenderWindow& window)
{
//Gets direction
    plyr.setTexture(mvTexture);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        dir = up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        dir = down;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        dir = right;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        dir = left;
    }

//Moves character
    if (dir == up)
    {
        plyr.setRotation(270);
        plyr.setPosition(plyr.getPosition().x, plyr.getPosition().y - mMvSpeed);
    }
    else if (dir == down)
    {
        plyr.setRotation(90);
        plyr.setPosition(plyr.getPosition().x, plyr.getPosition().y + mMvSpeed);
    }
    else if (dir == right)
    {
        plyr.setRotation(0);
        plyr.setPosition(plyr.getPosition().x + mMvSpeed, plyr.getPosition().y);
    }
    else if (dir == left)
    {
        plyr.setRotation(180);
        plyr.setPosition(plyr.getPosition().x - mMvSpeed, plyr.getPosition().y);
    }
}