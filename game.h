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
#include <cstring>
enum direction
{up, down, left, right};
const int GRID_SIZE_X = 31;
const int GRID_SIZE_Y = 33;
const int MAX_DOTS = 210;
class Game
{
private:
    //Game data
    sf::RenderWindow mWindow;
    bool play = false;
    //Player data
    int lives;
    int points = 0;
    int dotSpaces = 0;
    int dots = 0;
    int sDots = 0;
    float scale = 1.0;      //Scale of game
    //Ghost data
    //Title menu data
    sf::Sprite titleimage;
    sf::Texture texture;
    sf::Font font;
    sf::Text playbutton;
    sf::Text infobutton;
    sf::Text score;
    //map data
    sf::Sprite map;
    sf::Texture maptexture;
    //grid data
    char grid[GRID_SIZE_Y][GRID_SIZE_X];    //Main grid used to check for portals
    float gridoriginx;
    float gridoriginy;
    
public: 
    //Game functions
    Game();
    ~Game();
    void windowEvents();
    void update();
    void render();
    void reset();
    void deathAnimation();
    void setUpDots();
    void displayGUI();
    void updateGUI();
    bool isDone() const;
    bool start();
    int  getDots() const;
    sf::Texture mTextureFile;
    

    struct Player
    {
        sf::Sprite mSprite;                     //Player sprite
        float mvSpeed = 1.5;                    //Player movment speed
        int frames[5] = {32, 16, 0, 16, 32};    //Order of frames for animation
        int framecount = 0;                     //Used to keep count of frames during animation
        int gridPos[2][1];                      //Used to keep sprites position on grid
        direction mDir = left;                  //Direction of player
        direction bufferDir;                    //Direction put in buffer
        std::stack<direction> movement;         //Stack used to buffer moves when player can not turn in chosen direction
        Player();                               //Creates player
        void animate();                         //Player eating animation
        void move(float col, float row);        //Moves player sprite
        void controls();                        //Changes sprites direction
    };

    struct Ghosts
    {
        sf::Sprite mBody;                       //Ghost body
        sf::Sprite mEyes;                       //Ghost eyes
        float mvSpeed = 1.5;                    //Ghost movement speed
        int frames[2] = {0, 16};                //Ghost's animation frames
        int framecount = 0;                     //Count of the frame
        int gridPos[2][1];                      //Used to keep sprites position on grid
        direction mDir = left;                  //Ghost's direction
        Ghosts();                               //Ghost constructor
        void move();                            //Moves ghost
        void animate();                         //Animates ghost
    };
    
    struct Pellets
    {
        Pellets(bool isSuper);                  //Pellets constructor
        sf::Sprite mSprite;         //Pellets sprite
        bool eaten = false;         //If pellet is eaten it will be true
        bool super = false;         //Determines which kind of pellet it is
        int frames[2] = {0, 48};    //Frames of pellet to use to be animated
        int frameCount = 0;
        int gridPos[2][1];          //Used to keep sprites position on grid
    };
    struct Fruit
    {
        Fruit();
        sf::Sprite mSprite;
        void toDespawn();
        int level;
        int gridPos[2][1];
        int values[8] = {10, 30, 50, 70, 100, 200, 300, 500};
        bool spawned = false;

    };

    //Game objects
    Player * mPlyr = nullptr;
    Ghosts * inky = nullptr;
    Ghosts * blinky = nullptr;
    Ghosts * pinky = nullptr;
    Ghosts * clyde = nullptr;
    Fruit * fruit = nullptr;
    Pellets * pellets[MAX_DOTS];
    Pellets * sPellets[4];
    void eatPellet(Game::Pellets * pellet);       //Function for when a pellet is eaten
    int eatFruit(Game::Fruit * fruit);
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
    float getgridy(int row);
    float getgridx(int col);
    void setgridorigin();
    int returnrow(sf::Sprite s);
    int returncol(sf::Sprite s);
    bool isClear(direction dir, sf::Sprite sprite);
};
#endif