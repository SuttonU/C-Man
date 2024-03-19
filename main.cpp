#include "game.h"
#include "player.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 144.f);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    Game game1;
    player player1;
    sf::RenderWindow window(sf::VideoMode(1920 , 1080), "C-Man");
    sf::Event event;
    direction dir = left;   //Starts pacman going left
    while (game1.getLives() > 0 && window.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        game1.closeWindow(window);
        while (timeSinceLastUpdate > TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            player1.move(dir, window);
        }
        window.clear();
        window.draw(player1);
        window.display();
    }

    return 0;
}