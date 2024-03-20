#include "game.h"
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
    sf::Vector2u imageSize = plyrStillTexture.getSize();
    plyrSprite.setTexture(plyrStillTexture);  //Sets player texture to pacman
    plyrSprite.setPosition(110,120);      
    plyrSprite.scale(1,1);          
    plyrSprite.setOrigin(imageSize.x/2, imageSize.y/2);  
}
bool Game::isDone() const
{
    if (lives <= 0 || !mWindow.isOpen())
    {
        return true;
    }
    return false;
}
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
void Game::update()
{
    movePlyr();
    //move ghosts
}
void Game::render()
{
    mWindow.clear(sf::Color::Black);
    //Draw player
    mWindow.draw(plyrSprite);
    //draw ghosts
    mWindow.display();
}
void Game::setLives(int num)
{
    lives += num;
}
int Game::getLives()const
{
    return lives;
}
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