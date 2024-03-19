#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
//#include "ghosts.h"
//#include "map.h"
class Game
{
protected:
    int lives;
public:
    Game();
    void setLives(int num);
    int getLives()const;
    void closeWindow(sf::RenderWindow &window);
    void update();
    void render();
};
#endif