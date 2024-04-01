/**
 * @file game.cpp
 * @author Sutton Jones
 * @brief Functions for game class.
 * @version 0.1
 * @date 2024-03-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "game.h"
/**
 * @brief Construct a new Game object
 * 
 */
Game::Game() : mWindow(sf::VideoMode(1920 , 1080), "C-Man")
{
    lives = 3;
    if(!plyrStillTexture.loadFromFile("player.png"))
        {
            std::cout << "Error opening file\n";
            exit(1);
        } 
    if(!plyrMvTexture.loadFromFile("playermv.png"))
        {
            std::cout << "Error opening file\n";
            exit(1);
        }  
    if (    
        !plyrFrames[0].loadFromFile("pcmnOpn.png") ||
        !plyrFrames[1].loadFromFile("playermv.png") ||
        !plyrFrames[2].loadFromFile("player.png")
        )
    {
       std::cout << "Error opening a player frame.\n";
    }
    sf::Vector2u imageSize = plyrStillTexture.getSize();
    plyrSprite.setTexture(plyrStillTexture);  //Sets player texture to pacman
    plyrSprite.setPosition(110,120);      
    plyrSprite.scale(2,2);          
    plyrSprite.setOrigin(imageSize.x/2, imageSize.y/2);  
}
/**
 * @brief Checks to see if the game is over
 * 
 * @return true game is over
 * @return false game is not over
 */
bool Game::isDone() const
{
    if (lives <= 0 || !mWindow.isOpen())
    {
        return true;
    }
    return false;
}
/**
 * @brief Closes the window if player presses the close button
 * 
 */
void Game::closeWindow()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            // Close window button clicked.
            mWindow.close();
        }
    }
}
/**
 * @brief Updates the sprites on the screen
 * 
 */
void Game::update()
{
    movePlyr();
    plyrAnim();
    //move ghosts
}
/**
 * @brief Clears, Draws, and displays the screen
 * 
 */
void Game::render()
{
    mWindow.clear(sf::Color::Black);
    //Draw player
    mWindow.draw(plyrSprite);
    //draw ghosts
    mWindow.display();
}
/**
 * @brief Adds to the amount of lives
 * 
 * @param num number of lives to add
 */
void Game::setLives(int num)
{
    lives += num;
}
/**
 * @brief Returns the amount of lives the player has
 * 
 * @return int amount of lives
 */
int Game::getLives()const
{
    return lives;
}
/**
 * @brief Recieves control from player and moves the character in that direction
 * 
 */
void Game::movePlyr()
{
//Gets direction
    plyrSprite.setTexture(plyrMvTexture);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        plyrDir = up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        plyrDir = down;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        plyrDir = right;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        plyrDir = left;
    }

//Moves character
    if (plyrDir == up)
    {
        plyrSprite.setRotation(270);
        plyrSprite.setPosition(plyrSprite.getPosition().x, plyrSprite.getPosition().y - plyrMvSpeed);
    }
    else if (plyrDir == down)
    {
        plyrSprite.setRotation(90);
        plyrSprite.setPosition(plyrSprite.getPosition().x, plyrSprite.getPosition().y + plyrMvSpeed);
    }
    else if (plyrDir == right)
    {
        plyrSprite.setRotation(0);
        plyrSprite.setPosition(plyrSprite.getPosition().x + plyrMvSpeed, plyrSprite.getPosition().y);
    }
    else if (plyrDir == left)
    {
        plyrSprite.setRotation(180);
        plyrSprite.setPosition(plyrSprite.getPosition().x - plyrMvSpeed, plyrSprite.getPosition().y);
    }
}
/**
 * @brief Destroys player and takes away 1 life
 * 
 * @param plyr player obj
 */
void Game::destroyPlyr(Player plyr)
{
    lives--;
    plyr.~Player();
}
Game::Player::Player()
{
    //Set position to start of maze
    //plyrSprite.setPosition();
}
void Game::reset(Player plyr)
{
    //Creates newPlyr on reset
    Player * newPlyr;
    newPlyr = new Player;
    destroyPlyr(plyr);
    lives++;
}
void Game::plyrAnim()
{
    plyrSprite.setTexture(plyrFrames[playerFrame]);
    if (playerFrame == 2)
    {
        playerFrame = 0;
    }
    else
    {
        playerFrame++;
    }
    
}