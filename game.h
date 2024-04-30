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
#include <time.h>
#include <fstream>
#include <SFML/Audio.hpp>
enum direction
{up, left, down, right};
enum ghostStates
{scatter, chase, panic, dead};
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
    int xtraLive;
    int points = 0;
    int highscore;
    int dotSpaces = 0;
    int dots = 0;
    int sDots = 0;
    int ghostMult = 1;
    int cornersPos[4][2] = {{1,1}, {30,1}, {1,34}, {30,34}};   //Positions of the 4 corners{x,y}
    float scale = 1.0;      //Scale of game
    //Title menu data
    sf::Sprite titleimage;
    sf::Sprite plyrLives;
    sf::Sprite life;
    sf::Texture texture;
    sf::Font font;
    sf::Text playbutton;
    sf::Text infobutton;
    sf::Text scoreGui;
    sf::Text highscoreGui;
    sf::Text gameLevel;
    sf::Text backbutton;
    sf::Text instructions;
    //map data
    sf::Sprite map;
    sf::Texture maptexture;
    //grid data
    char grid[GRID_SIZE_Y][GRID_SIZE_X];    //Main grid used to check for portals
    float gridoriginx;
    float gridoriginy;
    std::fstream highscoreSave;
    //Audio data
    sf::SoundBuffer mintro;
    sf::SoundBuffer mchomp;
    sf::SoundBuffer mdeath;
    sf::SoundBuffer meatfruit;
    sf::SoundBuffer meatghost;
    sf::SoundBuffer mgainlife;
    sf::SoundBuffer mmenu;
    sf::SoundBuffer mpanicmode;
    sf::Sound intro;
    sf::Sound chomp;
    sf::Sound death;
    sf::Sound eatfruit;
    sf::Sound eatghost;
    sf::Sound gainlife;
    sf::Sound menu;
    sf::Sound panicmode;
    
public: 
    //Game functions
    Game();
    ~Game();
    void windowEvents();
    void update();
    void render();
    void reset(bool dead);
    void deathAnimation();
    void setUpDots();
    void displayGUI();
    bool isDone() const;
    bool start();
    int  getDots() const;
    int getLives() const;
    void teleport(sf::Sprite &s);                        //Check if teleporting and set position
    void updateGui();
    void loadaudio();
    sf::Texture mTextureFile;
    

    struct Player : public sf::Window
    {
        sf::Sprite mSprite;                     //Player sprite
        float mvSpeed = 1.5;                    //Player movment speed
        int frames[5] = {32, 16, 0, 16, 32};    //Order of frames for animation
        int framecount = 0;                     //Used to keep count of frames during animation
        int gridPos[2][1];                      //Used to keep sprites position on grid
        direction mDir = left;                  //Direction of player
        direction bufferDir = left;             //Direction in buffer
        Player();                               //Creates player
        void animate();                         //Player eating animation
        void move(float col, float row);        //Moves player sprite
        void controls();                        //Changes sprites direction
        virtual void draw(sf::RenderTarget& target, sf::RenderStates status = sf::RenderStates::Default) const;
    };

    struct Ghosts : public sf::Window
    {
        char map[GRID_SIZE_Y][GRID_SIZE_X];
        char mapToken;
        sf::Sprite mBody;                       //Ghost body
        sf::Sprite mEyes;                       //Ghost eyes
        float mvSpeed = 1.5;                    //Ghost movement speed
        float stateTime = 7.0;                        //Time for ghost to be in panic mode
        float prevTime;                         //Previous timer for ghost state
        int frames[2] = {0, 16};                //Ghost's animation frames
        int panicFrames[4] = {10*16, 11*16, 8*16, 9 * 16};    //Frames for ghost panic
        int framecount = 0;                     //Count of the frame
        int gridPos[2][1];                      //Used to keep sprites position on grid
        int prevFork[2][1];                     //Used to prevent ghost from activating the same fork before moving out of it
        //int prevPos[2][1];                    //Used to prevent ghost from going backwards
        int objPos[2][1];                       //Objective position
        direction mDir;                         //Ghost's direction
        direction nextDir;                      //Ghost's previous direction to prevent it from going the way it came
        ghostStates state = scatter;              //State ghost is in
        ghostStates prevState;                  //Previous state ghost was in
        Ghosts();                               //Ghost constructor
        void move(float x, float y);            //Moves ghost
        void animate();                         //Animates ghost
        void displayMap();                      //Used to keep track of the ghosts path
        void stateCountDown();                  //Changes states after each count down
        virtual void draw(sf::RenderTarget& target, sf::RenderStates status = sf::RenderStates::Default) const;
        bool spawned = false;                   //Test if ghost is already spawned
    };
    
    struct Pellets : public sf::Window
    {
        Pellets(bool isSuper);                  //Pellets constructor
        sf::Sprite mSprite;                     //Pellets sprite
        bool eaten = false;                     //If pellet is eaten it will be true
        bool super = false;                     //Determines which kind of pellet it is
        int frames[2] = {0, 48};                //Frames of pellet to use to be animated
        int frameCount = 0;                     //frame count for super pellets
        int gridPos[2][1];                      //Used to keep sprites position on grid
    };
    struct Fruit : public sf::Window
    {
        Fruit();
        sf::Sprite mSprite;
        void toDespawn();
        float despawnTime;
        int level;
        int gridPos[2][1];
        int values[8] = {10, 30, 50, 70, 100, 200, 300, 500};
        bool spawned = false;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates status = sf::RenderStates::Default) const;

    };

    //Game objects
    Player * mPlyr = nullptr;   //Player
    Ghosts * ghost1 = nullptr;  //red ghost
    Ghosts * ghost2 = nullptr;   //pink ghost
    Ghosts * ghost3 = nullptr;    //blue ghost
    Ghosts * ghost4 = nullptr;   //orange ghost
    Fruit * fruit = nullptr;    //fruit
    Pellets * pellets[MAX_DOTS];//Array of pellets
    Pellets * sPellets[4];      //Array of super pellets
    void eatPellet(Game::Pellets * pellet);       //Function for when a pellet is eaten
    int eatFruit(Game::Fruit * fruit);
    void destroyPlyr(Player plyr);
    void displaymenu();
    bool updatemenu();
    bool updatebutton(sf::Event &event, sf::Text &button);
    void displayinstructions();
    void findPath(Ghosts * ghost);
    void choosePath(Ghosts * ghost);
    void respawnGhost(Ghosts * ghost);                         //Used to respawn the ghost once it reaches the cage
    void movetospawn(Ghosts *ghost);                           //Moves ghost from ghost house to outside ghost house.
    void spawn();                                              //Initially spawns all ghosts.
    bool inghosthouse(sf::Sprite s);
    virtual void draw(sf::RenderTarget& target, Pellets * pellets[MAX_DOTS], int size, sf::RenderStates status = sf::RenderStates::Default) const;

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
    bool fillPath(int col, int row, Ghosts * ghost, int targetX, int targetY);
};
#endif