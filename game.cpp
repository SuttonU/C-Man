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
    mPlyr = new Player;
}
/**
 * @brief Destroy the Game:: Game object and frees memory.
 * 
 */
Game::~Game()
{
    delete mPlyr;
    delete inky;
    delete blinky; 
    delete pinky;
    delete clyde;
    mPlyr = nullptr;
    inky = nullptr;
    blinky = nullptr;
    pinky = nullptr;
    clyde = nullptr;
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
    mPlyr->move();
    mPlyr->animate();
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
    //mWindow.draw(plyrSprite);
    mWindow.draw(mPlyr->mSprite);
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
    if(!mTextureFile.loadFromFile("spritesheet.png"))
    {
        std::cout << "Error loading player sprite sheet\n";
        exit(101);
    }

    mSprite.setTexture(mTextureFile);
    mSprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
    mSprite.setOrigin(8, 8);
    mSprite.setScale(2,2);
    mSprite.setPosition(110,120);        
    //Set position to start of maze
    //plyrSprite.setPosition();
}
void Game::Player::move()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        mDir = up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        mDir = down;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        mDir = right;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        mDir = left;
    }

//Moves character
    if (mDir == up)
    {
        mSprite.setRotation(270);
        mSprite.setPosition(mSprite.getPosition().x, mSprite.getPosition().y - mvSpeed);
    }
    else if (mDir == down)
    {
        mSprite.setRotation(90);
        mSprite.setPosition(mSprite.getPosition().x, mSprite.getPosition().y + mvSpeed);
    }
    else if (mDir == right)
    {
        mSprite.setRotation(0);
        mSprite.setPosition(mSprite.getPosition().x + mvSpeed, mSprite.getPosition().y);
    }
    else if (mDir == left)
    {
        mSprite.setRotation(180);
        mSprite.setPosition(mSprite.getPosition().x - mvSpeed, mSprite.getPosition().y);
    }
}
void Game::Player::animate()
{
    mSprite.setTextureRect(sf::IntRect(frames[framecount/4], 0, 16, 16));
    if (framecount == 16)
    {
        framecount = 0;
    }
    else
    {
        framecount++;
    }
}
void Game::reset(Player plyr)
{
    //Creates newPlyr on reset
}