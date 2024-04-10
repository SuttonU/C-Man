/**
 * @file game.h
 * @author Sutton Jones
 * @brief Header for Game class
git pul * @version 0.1
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
#include <stack>
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
    int playerFrame = 2;
    int lives;
    int points = 0;
    float scale = 1.0;      //Scale of game
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
    //grid data
    char grid[33][31];
    
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

    struct Player
    {
        sf::Sprite mSprite;                     //Player sprite
        sf::Vector2f mPos;                      //Player position
        sf::FloatRect mHB;                      //Player hitbox
        float mvSpeed = 2.5;                    //Player movment speed
        int frames[5] = {32, 16, 0, 16, 32};    //Order of frames for animation
        int framecount = 0;                     //Used to keep count of frames during animation
        direction mDir = left;                  //Direction of player
        std::stack<direction> movement;         //Stack used to buffer moves when player can not turn in chosen direction
        Player();                               //Creates player
        void animate();                         //Player eating animation
        void move();                            //Moves player sprite
        void setHb(const sf::FloatRect &hitbox);//Sets the hitbox of the player
        sf::FloatRect getGlobalHb() const;      //Gets the hitbox of the player
    };

    struct Ghosts
    {
        sf::Sprite mBody;
        sf::Sprite mEyes;
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
        void setHb(const sf::FloatRect &hitbox);
        sf::FloatRect getGlobalHb() const;
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
    void drawGhost(Ghosts * ghost);

    //map functions
    void displaymap();

    //grid functions
    void initializegrid();
    void setwall(int length, int width, int row, int col);
    void displaygrid();
};
#endif