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
    Game game;
    game.displaygrid(); //Uncomment to test and display grid
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
        while (game.getDots() > 0 && !game.isDone())
        {
            timeSinceLastUpdate += clock.restart();
            game.windowEvents();
            while (timeSinceLastUpdate > TIME_PER_FRAME)
            {
                timeSinceLastUpdate -= TIME_PER_FRAME;
                game.update();
            }
            game.render();
        }
        game.reset(false);
    }

    return 0;
}