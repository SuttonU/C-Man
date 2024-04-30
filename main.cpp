/**
 * @file main.cpp
 * @author Sutton Jones, Ryan Matteson, and Ryan Costin
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
#include <SFML/Audio.hpp>
int main()
{
    int lives = 3;          //Used to keep track of when lives change
    Game game;
    srand(time(NULL));
    //game.displaygrid(); //Uncomment to test and display grid
    //Displays menu and pauses game
    game.loadaudio();
    game.displaymenu();
    while (!game.start() && !game.isDone())
    {
        game.windowEvents();
    }
    //Starts game
    game.displaymap();
    game.render();

    //Gameplay loop for player having enough lives
    while (!game.isDone())
    {        
        usleep(5000000);
        const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
        sf::Clock clock;  
        sf::Time timeSinceLastUpdate = sf::Time::Zero;
        //Gameplay loop while lives have not changed
        while (game.getDots() > 0 && !game.isDone() && lives == game.getLives())
        {
            timeSinceLastUpdate += clock.restart();
            game.windowEvents();
            while (timeSinceLastUpdate > TIME_PER_FRAME && lives == game.getLives())
            {
                timeSinceLastUpdate -= TIME_PER_FRAME;
                game.update();
                //When players live is 4 it will update the lives counter
                if (game.getLives() > lives)
                {
                    lives = game.getLives();
                }
                
            }
            game.render();
        }
        //Resets when level is done or player loses a life
        game.reset((lives != game.getLives()));
        //If the player lost a life it will set lives down one
        if (lives > game.getLives())
        {
            lives--;
        }
    }
    std::cout<<"Game Over.\n";
    return 0;
}