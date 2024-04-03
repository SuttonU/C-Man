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
    if(!mTextureFile.loadFromFile("spritesheet.png"))
    {
        std::cout << "Error loading game sprite sheet\n";
        exit(101);
    }
    lives = 3;
    blinky = new Ghosts(sf::Color::Red);
    blinky->mBody.setTexture(mTextureFile);
    //inky = new Ghosts(sf::Color::Blue);
    //inky->mSprite.setTexture(mTextureFile);
    //pinky = new Ghosts(sf::Color::Magenta);
    //pinky->mSprite.setTexture(mTextureFile);
    //clyde = new Ghosts(sf::Color::Red);
    //clyde->mSprite.setTexture(mTextureFile);
    mPlyr = new Player;
    mPlyr->mSprite.setTexture(mTextureFile);
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
    blinky->move();
    if (blinky->mBody.getPosition().x < 0)
    {
        blinky->mDir = right;
    }
    else if (blinky->mBody.getPosition().x > 1920)
    {
        blinky->mDir = left;
    }
    else if (blinky->mBody.getPosition().y > 1080)
    {
        blinky->mDir = up;
    }
    else if (blinky->mBody.getPosition().y < 0)
    {
        blinky->mDir = down;
    }
    
    
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
    mWindow.draw(blinky->mBody);
    mWindow.draw(mPlyr->mSprite);
    //draw ghosts
    mWindow.display();
}
/**
 * @brief Resets the sprites to their starting positions.
 */
void Game::reset()
{
    //Creates newPlyr on reset
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
/**
 * @brief Constructs a new Player object
 * 
 */
Game::Player::Player()
{
    mSprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
    mSprite.setOrigin(8, 8);
    mSprite.setScale(2,2);
    mSprite.setPosition(110,120);        
    //Set position to start of maze
    //plyrSprite.setPosition();
}
/**
 * @brief Moves player through taking in user input
 * 
 */
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
/**
 * @brief Animates player death
 * 
 */
void Game::deathAnimation()
{
    mPlyr->mSprite.setRotation(270);
    for (int i = 0; i < 11; i++)
    {
        mWindow.clear();
        mPlyr->mSprite.setTextureRect(sf::IntRect(48 + 16 * i, 0, 16, 16));
        mWindow.draw(mPlyr->mSprite);
        mWindow.display();
        usleep(2000000.0/1100000.0);
    }
}
/**
 * @brief Constructs a new ghost object
 * 
 * @param color color of ghost
 */
Game::Ghosts::Ghosts(sf::Color color)
{
    mBody.setColor(color);
    mBody.setTextureRect(sf::IntRect(16, 0, 16, 16));
    mBody.setOrigin(8, 8);
    mBody.setScale(2,2);
    mBody.setPosition(110,120); 
}
/**
 * @brief Moves ghost
 * 
 */
void Game::Ghosts::move()
{
    if (mDir == up)
        {
            mBody.setPosition(mBody.getPosition().x, mBody.getPosition().y - mvSpeed);
        }
        else if (mDir == down)
        {
            mBody.setPosition(mBody.getPosition().x, mBody.getPosition().y + mvSpeed);
        }
        else if (mDir == right)
        {
            mBody.setPosition(mBody.getPosition().x + mvSpeed, mBody.getPosition().y);
        }
        else if (mDir == left)
        {
            mBody.setPosition(mBody.getPosition().x - mvSpeed, mBody.getPosition().y);
        }
    mEyes.setPosition(mBody.getPosition().x, mBody.getPosition().y);
    mFeet.setPosition(mBody.getPosition().x, mBody.getPosition().y);
}