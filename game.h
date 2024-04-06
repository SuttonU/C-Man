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
#include <unistd.h>
//#include "ghosts.h"
//#include "map.h"
enum direction
{up, down, left, right};
class Game
{
private:
    //Game data
    sf::RenderWindow mWindow;
    bool play = false;
    //Player data
    sf::Texture plyrFrames[3];
    sf::FloatRect plyrHitbox;
    int playerFrame = 2;
    int lives;
    int points;
    //Ghost data
    //Title menu data
    sf::Sprite titleimage;
    sf::Texture texture;
    sf::Font font;
    sf::Text playbutton;
    sf::Text infobutton;
    //map data
    sf::Sprite map;
    sf::Texture maptexture;
    
public: 
    //Game functions
    Game();
    ~Game();
    void closeWindow();
    void update();
    void render();
    bool isDone() const;
    void reset();
    void setLives(int num);
    int getLives()const;
    sf::Texture mTextureFile;
    void deathAnimation();
    //Player functions
    struct Player
    {
        sf::Sprite mSprite;
        sf::Vector2f mPos;
        sf::Texture mDeath[10];
        sf::FloatRect mHB;
        float mvSpeed = 2;
        int frames[5] = {32, 16, 0, 16, 32};
        int framecount = 0;
        direction mDir = left;
        Player();
        void animate();
        void move();
        void setHb(const sf::FloatRect &hitbox);
        sf::FloatRect getGlobalHb() const;
    };
    struct Ghosts
    {
        sf::Sprite mBody;
        sf::Sprite mEyes;
        sf::Sprite mFeet;
        sf::Vector2f mPos;
        sf::FloatRect mHB;
        float mvSpeed = 2;
        direction mDir = left;
        Ghosts();
        void move();
        void setHb(const sf::FloatRect &hitbox);
        sf::FloatRect getGlobalHb() const;
    };
    struct Pellets
    {
        Pellets();
        sf::Sprite mSprite;
        sf::Vector2f mPos;
        sf::FloatRect mHB;
        int amount;
    };

    Player * mPlyr = nullptr;
    Ghosts * inky = nullptr;
    Ghosts * blinky = nullptr;
    Ghosts * pinky = nullptr;
    Ghosts * clyde = nullptr;
    Pellets * pellets[240];
    void destroyPlyr(Player plyr);
    void displaymenu();
    bool updatemenu();
    bool updatebutton(sf::Event &event, sf::Text &button);
    void displayinstructions();

    //map functions
    void displaymap();
};
#endif