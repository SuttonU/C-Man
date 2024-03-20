/**
 * @file game.h
 * @author Sutton Jones
 * @brief Header for Game class
 * @version 0.1
 * @date 2024-03-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
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
    float plyrMvSpeed = 1;
    sf::RenderWindow mWindow;
    //Player data
    sf::Texture plyrStillTexture;
    sf::Texture plyrMvTexture;
    sf::Sprite plyrSprite;
    direction plyrDir = left;
    sf::Vector2f plyrPosition;
    //Ghost data
    
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