#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
//#include "ghosts.h"
//#include "map.h"
enum direction
{up, down, left, right};
class Game
{
protected:
    int lives;
    sf::Texture plyrStillTexture;
    sf::Texture plyrMvTexture;
    sf::Vector2f plyrPosition;
    float plyrMvSpeed = 1;
    direction plyrDir = left;
    sf::RenderWindow mWindow;
    sf::Sprite plyrSprite;
public: 
    Game();
    void setLives(int num);
    int getLives()const;
    void closeWindow();
    void update();
    void render();
    bool isDone() const;
    void movePlyr();
};
#endif