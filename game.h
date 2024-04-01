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
private:
    //Game data
    sf::RenderWindow mWindow;
    //Player data
    sf::Texture plyrFrames[3];
    sf::Texture plyrStillTexture;
    sf::Texture plyrMvTexture;
    sf::Sprite plyrSprite;
    sf::Vector2f plyrPosition;
    sf::FloatRect plyrHitbox;
    direction plyrDir = left;
    int playerFrame = 2;
    int lives;
    float plyrMvSpeed = 2;
    float plyrScale = 1;
    //Ghost data
    
public: 
    //Game functions
    Game();
    void closeWindow();
    void update();
    void render();
    bool isDone() const;
    //Player functions
    struct Player
    {
        sf::Sprite mSprite;
        sf::Vector2f mPos;
        sf::Texture mTexture[3];
        sf::Texture mDeath[10];
        sf::FloatRect mHB;
        direction mDir = left;
        Player();
    };
    void destroyPlyr(Player plyr);
    void reset(Player plyr);
    void setLives(int num);
    int getLives()const;
    void movePlyr();
    void plyrAnim();
};
#endif