#include "game.h"
Game::Game()
{
    lives = 3;
    
}
void Game::setLives(int num)
{
    lives += num;
}
int Game::getLives()const
{
    return lives;
}
void Game::closeWindow(sf::RenderWindow &window)
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            // Close window button clicked.
            window.close();
        }
    }
}