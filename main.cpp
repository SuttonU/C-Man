#include "game.h"
#include "player.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    Game game;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    Player player;
    while (!game.isDone())
    {
        timeSinceLastUpdate += clock.restart();
        game.closeWindow();
        while (timeSinceLastUpdate > TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            game.update();
        }
        game.render();
    }

    return 0;
}