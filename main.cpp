/**
 * @file main.cpp
 * @author Sutton Jones, Ryan, and Ryan
 * @brief Runs the game in a loop
 * @version 0.1
 * @date 2024-03-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
int main()
{
    int lives = 3;          //Used to keep track of when lives change
    Game game;
    //game.displaygrid(); //Uncomment to test and display grid
    game.displaymenu();
    while (!game.start() && !game.isDone())
    {
        game.windowEvents();
    }
    game.displaymap();
    game.render();
    while (!game.isDone())
    {        
        usleep(5000000);
        const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
        sf::Clock clock;  
        sf::Time timeSinceLastUpdate = sf::Time::Zero;
        while (game.getDots() > 0 && !game.isDone() && lives == game.getLives())
        {
            timeSinceLastUpdate += clock.restart();
            game.windowEvents();
            while (timeSinceLastUpdate > TIME_PER_FRAME && lives == game.getLives())
            {
                timeSinceLastUpdate -= TIME_PER_FRAME;
                game.update();
                if (game.getLives() > lives)
                {
                    lives = game.getLives();
                }
                
            }
            game.render();
        }
        game.reset((lives != game.getLives()));
        if (lives > game.getLives())
        {
            lives--;
        }
        else if (lives < game.getLives())
        {
            lives = game.getLives();
        }
        
        
    }

    return 0;
}