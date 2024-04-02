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
    sf::FloatRect plyrHitbox;
    int playerFrame = 2;
    int lives;
    //Ghost data
    
public: 
    //Game functions
    Game();
    ~Game();
    void closeWindow();
    void update();
    void render();
    bool isDone() const;
    //Player functions
    struct Player
    {
        sf::Sprite mSprite;
        sf::Vector2f mPos;
        sf::Texture mTextureFile;
        sf::Texture mDeath[10];
        sf::FloatRect mHB;
        float mvSpeed = 2;
        int frames[5] = {32, 16, 0, 16, 32};
        int framecount = 0;
        direction mDir = left;
        Player();
        ~Player();
        void animate();
        void move();
    };
    Player * mPlyr = nullptr;
    struct Ghosts
    {
        sf::Sprite mSprite;
        sf::Vector2f mPos;
        sf::Texture mTextureFile;
        sf::FloatRect mHB;
        float mvSpeed = 2;
        direction mDir = left;
        Ghosts(sf::Color color);
        void move();
    };
    Ghosts * inky = nullptr;
    Ghosts * blinky = nullptr;
    Ghosts * pinky = nullptr;
    Ghosts * clyde = nullptr;
    void destroyPlyr(Player plyr);
    void reset(Player plyr);
    void setLives(int num);
    int getLives()const;
    void plyrAnim();
};
#endif