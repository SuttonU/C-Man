/**
 * @file game.cpp
 * @author Sutton Jones
 * @brief Functions for game class.
 * @version 0.1
 * @date 2024-03-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "game.h"
//Creates game and initializes all entities
Game::Game() : mWindow(sf::VideoMode(1920 , 1080), "C-Man")
{
    //Menu initialization
    texture.loadFromFile("Pacmantitle.png");
    titleimage.setTexture(texture);
    titleimage.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    titleimage.setScale(0.5 / scale,0.5 / scale);
    titleimage.setPosition(mWindow.getSize().x/2, mWindow.getSize().y/3);

    font.loadFromFile("PixelFont.ttf");
    playbutton.setFont(font);
    playbutton.setCharacterSize(50);
    playbutton.setString("Start");
    playbutton.setOrigin(playbutton.getGlobalBounds().width/2, playbutton.getGlobalBounds().height/2 + 15);
    playbutton.setPosition(mWindow.getSize().x/2, 600);

    infobutton.setFont(font);
    infobutton.setString("How to play");
    infobutton.setCharacterSize(50);
    infobutton.setOrigin(infobutton.getGlobalBounds().width/2, infobutton.getGlobalBounds().height/2 + 15);
    infobutton.setPosition(mWindow.getSize().x/2, 700);

    maptexture.loadFromFile("mapR.png");
    map.setTexture(maptexture);
    map.setOrigin(maptexture.getSize().x/2, maptexture.getSize().y/2);
    map.setPosition(mWindow.getSize().x/2, mWindow.getSize().y/2);

    if(!mTextureFile.loadFromFile("spritesheet.png"))
    {
        std::cout << "Error loading game sprite sheet\n";
        exit(101);
    }
    lives = 3;
    //Set scale of game
    scale = (mWindow.getSize().y * 1.0 )/248.0;
    scale -= scale / 10.0;
    //Create characters
    blinky = new Ghosts;
    inky = new Ghosts;
    pinky = new Ghosts;
    clyde = new Ghosts;
    mPlyr = new Player;
    fruit = new Fruit;
    //Set textures
    blinky->mBody.setTexture(mTextureFile);
    blinky->mEyes.setTexture(mTextureFile);
    inky->mBody.setTexture(mTextureFile);
    inky->mEyes.setTexture(mTextureFile);
    pinky->mBody.setTexture(mTextureFile);
    pinky->mEyes.setTexture(mTextureFile);
    clyde->mBody.setTexture(mTextureFile);
    clyde->mEyes.setTexture(mTextureFile);
    mPlyr->mSprite.setTexture(mTextureFile);
    fruit->mSprite.setTexture(mTextureFile);
    //Scale textures
    map.setScale(scale, scale);

    mPlyr->mSprite.setScale(scale, scale);
    blinky->mBody.setScale(scale, scale);
    blinky->mEyes.setScale(scale, scale);
    inky->mBody.setScale(scale, scale);
    inky->mEyes.setScale(scale, scale);
    pinky->mBody.setScale(scale, scale);
    pinky->mEyes.setScale(scale, scale);
    clyde->mBody.setScale(scale, scale);
    clyde->mEyes.setScale(scale, scale);
    fruit->mSprite.setScale(scale, scale);
    setgridorigin();
    //Set positions
    mPlyr->mSprite.setPosition(getgridx(15), getgridy(19));
    blinky->mBody.setPosition(getgridx(10), getgridy(14));
    inky->mBody.setPosition(getgridx(17), getgridy(14));
    pinky->mBody.setPosition(getgridx(13), getgridy(14));
    clyde->mBody.setPosition(getgridx(20), getgridy(14));
    fruit->mSprite.setPosition(getgridx(15), getgridy(19));
    mPlyr->gridPos[0][0] = 15;
    mPlyr->gridPos[0][1] = 19;
    blinky->gridPos[0][0] = 10;
    blinky->gridPos[0][1] = 14;
    inky->gridPos[0][0] = 17;
    inky->gridPos[0][1] = 14;
    pinky->gridPos[0][0] = 13;
    pinky->gridPos[0][1] = 14;
    clyde->gridPos[0][0] = 20;
    clyde->gridPos[0][1] = 14;
    fruit->gridPos[0][0] = 15;
    fruit->gridPos[0][1] = 19;
    //Set frames
    blinky->frames[0] = 0;
    blinky->frames[1] = 16;
    inky->frames[0] = 32;
    inky->frames[1] = 48;
    pinky->frames[0] = 64;
    pinky->frames[1] = 80;
    clyde->frames[0] = 96;
    clyde->frames[1] = 112;
    //Set starting frames
    pinky->mBody.setTextureRect(sf::IntRect(64, 16, 16, 16));
    inky->mBody.setTextureRect(sf::IntRect(32, 16, 16, 16));
    clyde->mBody.setTextureRect(sf::IntRect(96, 16, 16, 16));
    mPlyr->mSprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
    //Set up grid and dots
    //Set up map tokens
    blinky->mapToken = 'b';
    inky->mapToken = 'i';
    pinky->mapToken = 'p';
    clyde-> mapToken = 'c';
    initializegrid();
    setUpDots();
    //GUI Set up
    if (!font.loadFromFile("PixelFont.ttf"))
    {
        std::cout << "Error loading font\n";
        exit(1);
    }
    //Score set up
    score.setFont(font);
    score.setString(std::to_string(points) + "0");
    score.setScale(scale, scale);
    score.setOrigin(score.getGlobalBounds().width, 0);
    score.setPosition(mWindow.getSize().x, 0);
    //testing comment when done
    // blinky->gridPos[0][0] = 15;
    // blinky->gridPos[0][1] = 9;
    // inky->gridPos[0][0] = 15;
    // inky->gridPos[0][1] = 9;
    // pinky->gridPos[0][0] = 15;
    // pinky->gridPos[0][1] = 9;
    // clyde->gridPos[0][0] =15;
    // clyde->gridPos[0][1] =9;
    //Initialize ghost maps
    for (int i = 0; i < GRID_SIZE_Y; i++)
    {
        for (int j = 0; j < GRID_SIZE_X; j++)
        {
            blinky->map[i][j] = ' ';
            pinky->map[i][j] = ' ';
            inky->map[i][j] = ' ';
            clyde->map[i][j] = ' ';
        }
    }
    instructions.setFont(font);
    instructions.setString("Instructions: \n\nUse WASD keys or the arrow keys to move.\n\nDon't get killed by the ghosts.\n\nCollect the dots.");
    instructions.setCharacterSize(40);
    instructions.setOrigin(instructions.getGlobalBounds().width/2, instructions.getGlobalBounds().height/2 + 15);
    instructions.setPosition(mWindow.getSize().x/2, 700);

    backbutton.setFont(font);
    backbutton.setString("back");
    backbutton.setCharacterSize(50);
    backbutton.setOrigin(backbutton.getGlobalBounds().width/2, backbutton.getGlobalBounds().height/2 + 15);
    backbutton.setPosition(mWindow.getSize().x/20, mWindow.getSize().y/20);
}
/**
 * @brief Sets up the dots for pacman to eat
 * 
 */
void Game::setUpDots()
{
    for (int y = 0; y < GRID_SIZE_Y; y++)
    {
        for (int x = 0; x < GRID_SIZE_X; x++)
        {
            if ((grid[y][x] == ' ' 
                || grid[y][x] == 'f') 
                && (y != 23 || x != 9) 
                && (y != 23 || x != 21) 
                && (y != 9 || x != 9) 
                && (y != 9 || x != 21) 
                && ((y < 9 || y > 20) || (x < 6 || x > 24)))
            {
                //Creates new dot at position and increments # of dots
                pellets[dots] = new Pellets(false);
                pellets[dots]->mSprite.setTexture(mTextureFile);
                pellets[dots]->mSprite.setScale(scale, scale);
                pellets[dots]->mSprite.setPosition(getgridx(x) , getgridy(y));
                pellets[dots]->gridPos[0][0] = x;
                pellets[dots]->gridPos[1][0] = y;
                dots++;
            }    
            else if (((y == 23 && x == 9) 
                || (y == 23 && x == 21) 
                || (y == 9  && x == 9) 
                || (y == 9  && x == 21)) 
                && sDots < 4)
            {
                sPellets[sDots] = new Pellets(true);
                sPellets[sDots]->mSprite.setTexture(mTextureFile);
                sPellets[sDots]->mSprite.setScale(scale, scale);
                sPellets[sDots]->mSprite.setPosition(getgridx(x) , getgridy(y));
                sPellets[sDots]->gridPos[0][0] = x;
                sPellets[sDots]->gridPos[1][0] = y;
                sDots++;
            }
        }
    }
}
/**
 * @brief Runs different routines depending on how the window is updated
 * 
 */
void Game::windowEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            // Close window button clicked.
            mWindow.close();
        }
        else if (event.type == sf::Event::Resized)
        {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(visibleArea));



            scale = (mWindow.getSize().y * 1.0 )/312.0;
            //Scale movement speed
            mPlyr->mvSpeed = 1.25 * scale;
            blinky->mvSpeed = 1.25 * scale;
            pinky->mvSpeed = 1.25 * scale;
            inky->mvSpeed = 1.25 * scale;
            clyde->mvSpeed = 1.25 * scale;
            //Scale sprites
            map.setScale(scale, scale);
            mPlyr->mSprite.setScale(scale, scale);
            blinky->mBody.setScale(scale, scale);
            blinky->mEyes.setScale(scale, scale);
            pinky->mBody.setScale(scale, scale);
            pinky->mEyes.setScale(scale, scale);
            inky->mBody.setScale(scale, scale);
            inky->mEyes.setScale(scale, scale);
            clyde->mBody.setScale(scale, scale);
            clyde->mEyes.setScale(scale, scale);
            fruit->mSprite.setScale(scale, scale);
            //Scale positions
            map.setPosition(mWindow.getSize().x / 2, mWindow.getSize().y / 2);
            setgridorigin();
            mPlyr->mSprite.setPosition(getgridx(mPlyr->gridPos[0][0]), getgridy(mPlyr->gridPos[0][1]));
            blinky->mBody.setPosition(getgridx(blinky->gridPos[0][0]), getgridy(blinky->gridPos[0][1]));
            inky->mBody.setPosition(getgridx(inky->gridPos[0][0]), getgridy(inky->gridPos[0][1]));
            pinky->mBody.setPosition(getgridx(pinky->gridPos[0][0]), getgridy(pinky->gridPos[0][1]));
            clyde->mBody.setPosition(getgridx(clyde->gridPos[0][0]), getgridy(clyde->gridPos[0][1]));
            blinky->mEyes.setPosition(getgridx(blinky->gridPos[0][0]), getgridy(blinky->gridPos[0][1]));
            inky->mEyes.setPosition(getgridx(inky->gridPos[0][0]), getgridy(inky->gridPos[0][1]));
            pinky->mEyes.setPosition(getgridx(pinky->gridPos[0][0]), getgridy(pinky->gridPos[0][1]));
            clyde->mEyes.setPosition(getgridx(clyde->gridPos[0][0]), getgridy(clyde->gridPos[0][1]));
            fruit->mSprite.setPosition(getgridx(fruit->gridPos[0][0]), getgridy(fruit->gridPos[0][1]));
            //Scale dots
            if (dots > 0)
            {
                int i = 0;
                int j = 0;
                for (int y = 0; y < GRID_SIZE_Y; y++)
                {
                    for (int x = 0; x < GRID_SIZE_X; x++)
                    {
                        if ((grid[y][x] == ' ' 
                            || grid[y][x] == 'f') 
                            && (y != 23 || x != 9) 
                            && (y != 23 || x != 21) 
                            && (y != 9 || x != 9) 
                            && (y != 9 || x != 21) 
                            && ((y < 9 || y > 20) || (x < 6 || x > 24)))
                        {
                            pellets[i]->mSprite.setScale(scale, scale);
                            pellets[i]->mSprite.setPosition(getgridx(x) , getgridy(y));
                            i++;
                        }   
                        else if (((y == 23 && x == 9) 
                        || (y == 23 && x == 21) 
                        || (y == 9  && x == 9) 
                        || (y == 9  && x == 21)) 
                        && j < sDots)
                        {
                            sPellets[j]->mSprite.setScale(scale, scale);
                            sPellets[j]->mSprite.setPosition(getgridx(x) , getgridy(y));
                            j++;
                        }                     
                    }
                }
            }
            //Scale Gui
            score.setScale(scale, scale);
        }
        //updates each button
        else if (updatebutton(event, playbutton))
        {
            play = true;
        }
        else if (updatebutton(event, infobutton)){
            displayinstructions();
        }
        if (!play)
        {
            mWindow.clear();
            mWindow.draw(titleimage);
            mWindow.draw(playbutton);
            mWindow.draw(infobutton);
            mWindow.display();
        }
    }
}
/**
 * @brief starts game when play is true
 * 
 */
bool Game::start()
{
    return play;
}
/**
 * @brief Destroy the Game:: Game object and frees memory.
 * 
 */
Game::~Game()
{
    delete mPlyr;  
    delete inky;  
    delete blinky;
    delete pinky; 
    delete clyde;
    mPlyr = nullptr; 
    inky = nullptr;
    blinky = nullptr;
    pinky = nullptr; 
    clyde = nullptr;
    int size = dots;
    for (int i = 0; i < size; i++)
    {
       delete pellets[i];
       pellets[i] = nullptr;
    }
    for (int i = 0; i < 4; i++)
    {
       delete sPellets[i];
       sPellets[i] = nullptr;
    }
}
void Game :: displaymenu(){

    mWindow.draw(titleimage);
    mWindow.draw(playbutton);
    mWindow.draw(infobutton);
    mWindow.display();
    //windowEvents();
}

// bool Game :: updatemenu(){
//     sf::Event event;
//     while(mWindow.pollEvent(event)){
//         if (event.type == sf::Event::Closed)
//         mWindow.close();

//         if (updatebutton(event, playbutton))
//         {
//             play = true;
//             return true;
//         }
//         if (updatebutton(event, infobutton)){
//             displayinstructions();
//         }
//         mWindow.clear();
//         mWindow.draw(titleimage);
//         mWindow.draw(playbutton);
//         mWindow.draw(infobutton);
//         mWindow.display();
//     }
//     return false;
// }

bool Game :: updatebutton(sf::Event &event, sf::Text &button){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
    bool mouseinbutton = mousePosition.x >= button.getPosition().x - button.getGlobalBounds().width/2
                        && mousePosition.x <= button.getPosition().x + button.getGlobalBounds().width/2
                        && mousePosition.y >= button.getPosition().y - button.getGlobalBounds().height/2
                        && mousePosition.y <= button.getPosition().y + button.getGlobalBounds().height/2;

    if (event.type == sf::Event::MouseMoved){
        if (mouseinbutton){
            button.setFillColor(sf::Color::Yellow);
        } else {
            button.setFillColor(sf::Color::White);
        }
    }
    if (event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left && mouseinbutton){
            button.setFillColor(sf::Color(150,0,0));
        } else {
            button.setFillColor(sf::Color::White);
        }
    }
    if (event.type == sf::Event::MouseButtonReleased){
        if(event.mouseButton.button==sf::Mouse::Left){
            if(mouseinbutton)
                {
                    button.setFillColor(sf::Color::White);
                    return true;
                }
                else
                {
                    button.setFillColor(sf::Color::White);
                }
        }
    }
    return false;
}

void Game :: displayinstructions(){
    mWindow.clear();
    sf::Event event;
    bool backtomenu = false;

    mWindow.draw(instructions);
    mWindow.draw(backbutton);
    mWindow.draw(titleimage);
    mWindow.display();
    while (!backtomenu){
        if(mWindow.pollEvent(event)){
            if (event.type == sf::Event::Closed)
            mWindow.close();

            if (updatebutton(event, backbutton)){
                backtomenu = true;
            }
            if (!backtomenu){
            mWindow.clear();
            mWindow.draw(instructions);
            mWindow.draw(backbutton);
            mWindow.draw(titleimage);
            mWindow.display();
            }
        }
    }
}
/**
 * @brief Checks to see if the game is over
 * 
 * @return true game is over
 * @return false game is not over
 */
bool Game::isDone() const
{
    if (lives <= 0 || !mWindow.isOpen())
    {
        return true;
    }
    return false;
}
/**
 * @brief Updates the sprites on the screen as well as anything the game needs
 * 
 */
void Game::update()
{
    //Moving
    mPlyr->controls();
    if (!inghosthouse(blinky->mBody)){
        findPath(blinky);
    }
    if (!inghosthouse(inky->mBody)){
        findPath(inky);
    }
    if (!inghosthouse(pinky->mBody)){
        findPath(pinky);
    }
    if (!inghosthouse(clyde->mBody)){
        findPath(clyde);
    }
    spawn();
    choosePath(blinky);
    choosePath(inky);
    choosePath(pinky);
    choosePath(clyde);
    //If the next move is clear then it will set the next direction to the one store in movement buffer.
    if (isClear(mPlyr->bufferDir, mPlyr->mSprite) && mPlyr->bufferDir!=mPlyr->mDir)
    {
        mPlyr->mDir = mPlyr->bufferDir;
    }
    if (isClear(mPlyr->mDir, mPlyr->mSprite))
    {
        mPlyr->move(getgridx(returncol(mPlyr->mSprite)), getgridy(returnrow(mPlyr->mSprite)));//Moves and sets pacman token
        mPlyr->animate();
    }
    if ((isClear(blinky->mDir, blinky->mBody) || blinky->state == dead) && blinky->spawned)
    {
        blinky->move(getgridx(returncol(blinky->mBody)), getgridy(returnrow(blinky->mBody)));
        blinky->animate();
    }
    if ((isClear(pinky->mDir, pinky->mBody) || pinky->state == dead) && pinky->spawned)
    {
        pinky->move(getgridx(returncol(pinky->mBody)), getgridy(returnrow(pinky->mBody)));
        pinky->animate();
    }
    if ((isClear(inky->mDir, inky->mBody) || inky->state == dead) && inky->spawned)
    {
        inky->move(getgridx(returncol(inky->mBody)), getgridy(returnrow(inky->mBody)));
        inky->animate();
    }
    if ((isClear(clyde->mDir, clyde->mBody) || clyde->state == dead) && clyde->spawned)
    {
        clyde->move(getgridx(returncol(clyde->mBody)), getgridy(returnrow(clyde->mBody)));
        clyde->animate();
    }
    //Eats pellets
    if (dots > 0)
    {
        for (int i = 0; i < MAX_DOTS; i++)
        {
            bool notEaten = (!pellets[i]->eaten);   //Checks if pellet is not eaten
            eatPellet(pellets[i]);  
            bool eaten = (pellets[i]->eaten);       //Checks to see if pellet is eaten after function
            if (eaten && notEaten)                  //If pellet was not eaten and pellet is now eaten it will add 10 points
            {
                points += 1;
            }      
        }
    }    
    //Eats super pellets then sets ghosts to panic
    for (int i = 0; i < 4; i++)
        {
            bool notEaten = (!sPellets[i]->eaten);
            eatPellet(sPellets[i]);
            bool eaten = (sPellets[i]->eaten);
            if (eaten && notEaten)
            {
                ghostMult = 1;
                blinky->prevState = blinky->state;
                inky->prevState = inky->state;
                pinky->prevState = pinky->state;
                clyde->prevState = clyde->state; 
                blinky->state = panic;
                inky->state = panic;
                pinky->state = panic;
                clyde->state = panic;
                blinky->framecount = 0;
                inky->framecount = 0;
                pinky->framecount = 0;
                clyde->framecount = 0;
                blinky->panicTime = 7.0;
                pinky->panicTime = 7.0;
                inky->panicTime = 7.0;
                clyde->panicTime = 7.0;
            }
        }
    //Animates the super dots so they flash
    for (int i = 0; i < 4; i++)
    {
        if (!sPellets[i]->eaten)
        {
            sPellets[i]->mSprite.setTextureRect({16 * 15, sPellets[i]->frames[sPellets[i]->frameCount / 16], 16, 16});
                if (sPellets[i]->frameCount == 31)
                {
                    sPellets[i]->frameCount = 0;
                }
                else
                {
                    sPellets[i]->frameCount++;
                }

        }
        
        }
    //eats the fruit
    if (fruit->spawned && (fruit->gridPos[0][0] == mPlyr->gridPos[0][0] && fruit->gridPos[1][0] == mPlyr->gridPos[1][0]))
    {
        points += eatFruit(fruit);
    }
    //Spawns a fruit when dots are at 70 and 170
    if (dots == MAX_DOTS - 70 || dots == MAX_DOTS - 170)
    {
        fruit->mSprite.setTextureRect({16 * fruit->level, 32, 16, 16});
        fruit->spawned = true;
    }
    //Adds extra life at 10k points
    if (points >= 1000 && xtraLive == 0)
    {
        lives++;
        xtraLive = 1;
    }

    //Check for teleportation
    teleport(mPlyr->mSprite);
    teleport(blinky->mBody);
    teleport(inky->mBody);
    teleport(pinky->mBody);
    teleport(clyde->mBody);
    
    //Update position
    mPlyr->gridPos[0][0] = returncol(mPlyr->mSprite);
    mPlyr->gridPos[0][1] = returnrow(mPlyr->mSprite);
    blinky->gridPos[0][0] = returncol(blinky->mBody);
    blinky->gridPos[0][1] = returnrow(blinky->mBody);
    inky->gridPos[0][0] = returncol(inky->mBody);
    inky->gridPos[0][1] = returnrow(inky->mBody);
    pinky->gridPos[0][0] = returncol(pinky->mBody);
    pinky->gridPos[0][1] = returnrow(pinky->mBody);
    clyde->gridPos[0][0] = returncol(clyde->mBody);
    clyde->gridPos[0][1] = returnrow(clyde->mBody);
    //If pacman shares the same tile with any ghost and their state is not in panic it will kill the player
    if ((mPlyr->gridPos[0][0] == blinky->gridPos[0][0] && mPlyr->gridPos[0][1] == blinky->gridPos[0][1] && (blinky->state != panic && blinky->state != dead))
    ||(mPlyr->gridPos[0][0] == inky->gridPos[0][0] && mPlyr->gridPos[0][1] == inky->gridPos[0][1] && (inky->state != panic && inky->state != dead))
    ||(mPlyr->gridPos[0][0] == pinky->gridPos[0][0] && mPlyr->gridPos[0][1] == pinky->gridPos[0][1] && (pinky->state != panic && pinky->state != dead))
    ||(mPlyr->gridPos[0][0] == clyde->gridPos[0][0] && mPlyr->gridPos[0][1] == clyde->gridPos[0][1] && (clyde->state != panic && clyde->state != dead)))
    {
        deathAnimation();
        lives--;
        return;
    }
    //These will eat the ghost
    else if ((mPlyr->gridPos[0][0] == blinky->gridPos[0][0] && mPlyr->gridPos[0][1] == blinky->gridPos[0][1] && blinky->state == panic))
    {
        blinky->state = dead;
        points += 40 * ghostMult;
        ghostMult++;
        blinky->spawned = false;
    }
    else if (mPlyr->gridPos[0][0] == inky->gridPos[0][0] && mPlyr->gridPos[0][1] == inky->gridPos[0][1] && inky->state == panic)
    {
        inky->state = dead;
        points += 40 * ghostMult;
        ghostMult++;
        inky->spawned = false;
    }
    else if(mPlyr->gridPos[0][0] == pinky->gridPos[0][0] && mPlyr->gridPos[0][1] == pinky->gridPos[0][1] && pinky->state == panic)
    {
        pinky->state = dead;
        points += 40 * ghostMult;
        ghostMult++;
        pinky->spawned = false;
    }
    else if (mPlyr->gridPos[0][0] == clyde->gridPos[0][0] && mPlyr->gridPos[0][1] == clyde->gridPos[0][1] && clyde->state == panic)
    {
        clyde->state = dead;
        points += 40 * ghostMult;
        ghostMult++;
        clyde->spawned = false;
    }
    
    //Revive dead ghosts
    //If a ghost is dead and its position is in the ghost house it will be set to the previous state
    if (blinky->state == dead 
    && blinky->gridPos[0][0] == blinky->objPos[0][0] 
    && blinky->gridPos[0][1] == blinky->objPos[0][1])
    {
        blinky->state = blinky->prevState;
        blinky->objPos[0][1] = 9;
        respawnGhost(blinky);
    }
    else if (pinky->state == dead 
    && pinky->gridPos[0][0] == pinky->objPos[0][0] 
    && pinky->gridPos[0][1] == pinky->objPos[0][1])
    {
        pinky->state = pinky->prevState;
        blinky->objPos[0][1] = 9;
        respawnGhost(pinky);
    }
    else if (inky->state == dead 
    && inky->gridPos[0][0] == inky->objPos[0][0] 
    && inky->gridPos[0][1] == inky->objPos[0][1])
    {
        inky->state = inky->prevState;
        blinky->objPos[0][1] = 9;
        respawnGhost(inky);
    }
    else if (clyde->state == dead 
    && clyde->gridPos[0][0] == clyde->objPos[0][0] 
    && clyde->gridPos[0][1] == clyde->objPos[0][1])
    {
        clyde->state = clyde->prevState;
        blinky->objPos[0][1] = 9;
        respawnGhost(clyde);
    }
    updateGUI();
}
/**
 * @brief returns player lives
 * 
 * @return int # of lives
 */
int Game::getLives() const
{
    return lives;
}
/**
 * @brief Clears, Draws, and displays the screen
 * 
 */
void Game::render()
{
    mWindow.clear(sf::Color::Black);
    //Draw player
    for (int i = 0; i < MAX_DOTS; i++)
    {
        if (!pellets[i]->eaten)
        {
            mWindow.draw(pellets[i]->mSprite);
        }        
    }
    for (int i = 0; i < 4; i++)
    {
        if (!sPellets[i]->eaten)
        {  
            mWindow.draw(sPellets[i]->mSprite);
        }
    }
    
    if (fruit->spawned)
    {
        mWindow.draw(fruit->mSprite);
    }
    
    drawGhost(blinky);
    drawGhost(inky);
    drawGhost(pinky);
    drawGhost(clyde);
    mWindow.draw(mPlyr->mSprite);
    //draw map
    mWindow.draw(map);
    //draw gui
    mWindow.draw(score);
    mWindow.display();
}
/**
 * @brief Checks to see if there is a wall in the way
 * 
 * @param dir direction sprite is traveling in
 * @return true there is no wall in the way
 * @return false there is a wall in the way
 */
bool Game::isClear(direction dir, sf::Sprite sprite)
{
    int x = returncol(sprite);
    int y = returnrow(sprite);
    if (!inghosthouse(sprite)){
        if (
            (dir == up && grid[y - 1][x] == 'w')
        || (dir == down && grid[y + 1][x] == 'w')  
        || (dir == right && grid[y][x + 1] == 'w')  
        || (dir == left && grid[y][x - 1] == 'w')
        )
        {
            return false;
        }
    }
    return true;
    
}
/**
 * @brief Draws all the parts of the ghost
 * 
 * @param ghost ghost to draw
 */
void Game::drawGhost(Ghosts * ghost)
{
    if (ghost->state != dead)
    {
        mWindow.draw(ghost->mBody);
    }
    if (ghost->state != panic)
    {
        mWindow.draw(ghost->mEyes);
    }    
}
/**
 * @brief Resets the sprites to their starting positions.
 */
void Game::reset(bool dead)
{
    setgridorigin();
    mPlyr->mSprite.setPosition(getgridx(15), getgridy(19));
    mPlyr->mDir = left;
    mPlyr->mSprite.setTextureRect(sf::IntRect(32, 0, 16 ,16));
    blinky->mBody.setPosition(getgridx(15), getgridy(9));
    inky->mBody.setPosition(getgridx(17), getgridy(14));
    pinky->mBody.setPosition(getgridx(13), getgridy(14));
    clyde->mBody.setPosition(getgridx(20), getgridy(14));
    blinky->mEyes.setPosition(getgridx(15), getgridy(9));
    inky->mEyes.setPosition(getgridx(17), getgridy(14));
    pinky->mEyes.setPosition(getgridx(13), getgridy(14));
    clyde->mEyes.setPosition(getgridx(20), getgridy(14));
    //Set grid pos
    mPlyr->gridPos[0][0] = 15;
    mPlyr->gridPos[0][1] = 19;
    blinky->gridPos[0][0] = 9;
    pinky->gridPos[0][0] = 17;
    inky->gridPos[0][0] = 13;
    clyde->gridPos[0][0] = 20;
    blinky->gridPos[0][1] = 15;
    pinky->gridPos[0][1] = 14;
    inky->gridPos[0][1] = 14;
    clyde->gridPos[0][1] = 14;

    //Reset states
    blinky->state = scatter;
    pinky->state = scatter;
    inky->state = scatter;
    clyde->state = scatter;
    //reset mdir
    mPlyr->mDir = left;
    mPlyr->bufferDir = left;
    blinky->mDir = left;
    pinky->mDir = left;
    inky->mDir = left;
    clyde->mDir = left;
    //Reinitialize ghost maps
    for (int i = 0; i < GRID_SIZE_Y; i++)
    {
        for (int j = 0; j < GRID_SIZE_X; j++)
        {
            blinky->map[i][j] = ' ';
            pinky->map[i][j] = ' ';
            inky->map[i][j] = ' ';
            clyde->map[i][j] = ' ';
        }
    }
    //If player died the dots will not reset
    if (!dead)
    {
        dots = 0;
        for (int i = 0; i < MAX_DOTS; i++)
        {
            (pellets[i])->eaten = false;
            dots++;
        }
        for (int i = 0; i < 4; i++)
        {
            (sPellets[i])->eaten = false;
            sPellets[i]->mSprite.setTextureRect({16 * 15, sPellets[i]->frames[0], 16, 16 });
            sPellets[i]->frameCount = 0;
            sDots++;
        }
    //increments the fruit level to the next fruit.
    fruit->level++;
    }
    fruit->toDespawn();
    render();    
}
/**
 * @brief returns amount of dots that remain in the game
 * 
 * @return amount of dots left
 */
int Game::getDots()const
{
    return dots + sDots;
}
/**
 * @brief Destroys player and takes away 1 life
 * 
 * @param plyr player obj
 */
void Game::destroyPlyr(Player plyr)
{
    lives--;
    plyr.~Player();
}


/****Player Functions*****/


/**
 * @brief Constructs a new Player object
 * 
 */
Game::Player::Player()
{
    mvSpeed = mvSpeed * mSprite.getScale().x;
    mSprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
    mSprite.setOrigin(8, 8);
}
/**
 * @brief Moves player through taking in user input
 * 
 */
void Game::Player::move(float col, float row)
{    
//Moves character
    if (mDir == up)
    {
        mSprite.setRotation(270);
        mSprite.setPosition(col, mSprite.getPosition().y - mvSpeed);
    }
    else if (mDir == down)
    {
        mSprite.setRotation(90);
        mSprite.setPosition(col, mSprite.getPosition().y + mvSpeed);
    }
    else if (mDir == right)
    {
        mSprite.setRotation(0);
        mSprite.setPosition(mSprite.getPosition().x + mvSpeed, row);
    }
    else if (mDir == left)
    {
        mSprite.setRotation(180);
        mSprite.setPosition(mSprite.getPosition().x - mvSpeed, row);
    }
}
/**
 * @brief Changes players direction based on input
 * 
 */
void Game::Player::controls()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        bufferDir = up;
        
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        bufferDir = down;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        bufferDir = right;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        bufferDir = left;
    }
}
/**
 * @brief animates player
 * 
 */
void Game::Player::animate()
{
    //If the frame is the last frame then it will set the frame count back to zero
    //Displays the frame the player is on.
    mSprite.setTextureRect(sf::IntRect(frames[framecount/4], 0, 16, 16));
    if (framecount == 16)
    {
        framecount = 0;
    }
    else
    {
        framecount++;
    }
}
/**
 * @brief Animates player death
 * 
 */
void Game::deathAnimation()
{
    mPlyr->mSprite.setRotation(270);
    for (int i = 0; i < 11; i++)
    {
        mPlyr->mSprite.setTextureRect(sf::IntRect(48 + 16 * i, 0, 16, 16));
        render();
        usleep((1.0/12.0) * 1000000);
    }
    mPlyr->mSprite.setTextureRect(sf::IntRect(64, 64, 16, 16));
    render();
}
/****Ghost Functions****/


/**
 * @brief Constructs a new ghost object
 * 
 * @param color color of ghost
 */
Game::Ghosts::Ghosts()
{
    mBody.setTextureRect(sf::IntRect(0,16,16,16));
    mBody.setOrigin(8, 8);
    mBody.setPosition(800,800); 
    mEyes.setTextureRect(sf::IntRect(16*12,16,16,16));
    mEyes.setOrigin(8,8);
    mEyes.setPosition(mBody.getPosition().x, mBody.getPosition().y);
}
/**
 * @brief Moves ghost
 * 
 */
void Game::Ghosts::move(float x, float y)
{
    if (mDir == up)
        {
            mBody.setPosition(x, mBody.getPosition().y - mvSpeed);
            mEyes.setTextureRect(sf::IntRect(14*16, 16, 16, 16));
        }
        else if (mDir == down)
        {
            mBody.setPosition(x, mBody.getPosition().y + mvSpeed);
            mEyes.setTextureRect(sf::IntRect(15*16, 16, 16, 16));
        }
        else if (mDir == right)
        {
            mBody.setPosition(mBody.getPosition().x + mvSpeed, y);
            mEyes.setTextureRect(sf::IntRect(13*16, 16, 16, 16));
        }
        else if (mDir == left)
        {
            mBody.setPosition(mBody.getPosition().x - mvSpeed, y);
            mEyes.setTextureRect(sf::IntRect(12*16, 16, 16, 16));
        }
    mEyes.setPosition(mBody.getPosition().x, mBody.getPosition().y);
}
/**
 * @brief displays map of ghosts pathfinding
 * 
 */
void Game::Ghosts::displayMap()
{
    for (int y = 0; y < GRID_SIZE_Y; y++)
    {
        for (int x = 0; x < GRID_SIZE_X; x++)
        {
            std::cout<<map[y][x] << " ";
        }
        std::cout<<"\n";
    }
}
/**
 * @brief respawns the ghost
 * 
 * @param ghost ghost to spawn
 */
void Game::respawnGhost(Ghosts * ghost)
{
    movetospawn(ghost);
    ghost->spawned = true;
}
/**
 * @brief Sets ghost objective based on its state and which ghost it is
 * 
 * @param ghost 
 */
void Game::findPath(Ghosts * ghost)
{
    ghost-> mvSpeed = 1.0 * scale;
    if (ghost->state == chase)
    {
        //These if statements find which ghost it is
        if (ghost->frames[0] == 0)
        {
            ghost->objPos[0][0] = returncol(mPlyr->mSprite);
            ghost->objPos[0][1] = returnrow(mPlyr->mSprite);

        } else if (ghost->frames[0] == 32)
        {
            //These are to find what tile is 2 tiles in front of pac man
            if (mPlyr->mDir == up)
            {
                ghost->objPos[0][1] = returnrow(mPlyr->mSprite) - 2;
            } else if (mPlyr->mDir == down)
            {
                ghost->objPos[0][1] = returnrow(mPlyr->mSprite) + 2;
            } else if (mPlyr->mDir == left)
            {
                ghost->objPos[0][0] = returncol(mPlyr->mSprite) - 2;
            } else
            {
                ghost->objPos[0][0] = returncol(mPlyr->mSprite) + 2;
            }
        } else if (ghost->frames[0] == 64)
        {
            //This is inkys complicated mess of finding his target tile
            int x = mPlyr->gridPos[0][0];
            int y = mPlyr->gridPos[0][1];

            if (mPlyr->mDir == up)
            {
                y -= 2;
            } else if (mPlyr->mDir == down)
            {
                y += 2;
            } else if (mPlyr->mDir == left)
            {
                x -= 2;
            } else
            {
                x += 2;
            }

            x = (x - blinky->gridPos[0][0]) * 2 + blinky->gridPos[0][0];
            y = (y - blinky->gridPos[0][1]) * 2 + blinky->gridPos[0][1];
            ghost->objPos[0][0] = x;
            ghost->objPos[0][1] = y;

        } else if (ghost->frames[0] == 96)
        {
            //Clyde will not attack unless hes more than 8 tile away from pac man
            if (mPlyr->gridPos[0][0] - ghost->gridPos[0][0] > 8
            || mPlyr->gridPos[0][0] - ghost->gridPos[0][0] < -8
            || mPlyr->gridPos[0][1] - ghost->gridPos[0][1] > 8
            || mPlyr->gridPos[0][1] - ghost->gridPos[0][1] < -8)
            {
                ghost->objPos[0][0] = mPlyr->gridPos[0][0];
                ghost->objPos[0][1] = mPlyr->gridPos[0][1];
            } else
            {
                //Clydes corner  
                ghost->objPos[0][0] = cornersPos[(ghost->frames[0] / 32 + 1)][0];
                ghost->objPos[0][1] = cornersPos[(ghost->frames[0] / 32 + 1)][1];
            }
        }
    }
    //If the state is scatter the ghosts will go to their corners
    else if (ghost->state == scatter)
    {
        //Set to each corner   Ghost number
        ghost->objPos[0][0] = cornersPos[(ghost->frames[0] / 32 + 1)][0];
        ghost->objPos[0][1] = cornersPos[(ghost->frames[0] / 32 + 1)][1];
    }
    //If its panic they will move random directions
    else if (ghost->state == panic)
    {
        //Slow down and randomize direction
        ghost->mvSpeed = 0.75 * scale;
    }
    //If their dead they will go to spawn
    else if (ghost->state == dead)
    {
        ghost->mvSpeed = 2.5 * scale;
        ghost->objPos[0][0] = 15;
        ghost->objPos[0][1] = 14;
    }    
}
/**
 * @brief Chooses the path the ghost should take
 * 
 * @param ghost ghost object
 */
void Game::choosePath(Ghosts * ghost)
{
    int x = returncol(ghost->mBody);
    int y = returnrow(ghost->mBody);
    int targetX = ghost->objPos[0][0];
    int targetY = ghost->objPos[0][1];
    direction prevDir = ghost->mDir;
    //Prevents path from updating multiple times on the same tile
    if (grid[y][x] == 'f' && (y != ghost->prevFork[0][1] || x != ghost->prevFork[0][0]))
    {        
        ghost->prevFork[0][1] = y;
        ghost->prevFork[0][0] = x;
        fillPath(y, x, ghost, targetX, targetY);
    }
    ghost->map[y][x] = ' ';
    //If the ghost can not move he will move in which ever direction is the easiest
    if (!isClear(ghost->mDir, ghost->mBody) && ghost->state != dead)
    {
        if (isClear(up, ghost->mBody) && ghost->mDir != down 
        && y >= targetY
        )
        {
            ghost->mDir = up;
        }
        else if (isClear(left, ghost->mBody) && ghost->mDir != right 
        && x >= targetX
        )
        {
            ghost->mDir = left;
        }
        else if (isClear(down, ghost->mBody) && ghost->mDir != up 
        && y <= targetY
        )
        {
            ghost->mDir = down;
        }
        else if (isClear(right, ghost->mBody) && ghost->mDir != left 
        && x <= targetX
        )
        {
            ghost->mDir = right;
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                if (isClear(direction(i), ghost->mBody)
                &&!(direction(i) == down && prevDir == up)
                &&!(direction(i) == up && prevDir == down)
                &&!(direction(i) == right && prevDir == left)
                &&!(direction(i) == left && prevDir == right))
                {
                    ghost->mDir = direction(i);
                    break;
                }
            }
            
        }        
    }
    //If the ghost is dead it will directly go to the ghost spawn
    else if (ghost->state == dead)
    {
        if (y > targetY)
        {
            ghost->mDir = up;
        }
        else if (y < targetY)
        {
            ghost->mDir = down;
        }
        else if (x > targetX)
        {
            ghost->mDir = left;
        }
        else 
        {
            ghost->mDir = right;
        }
    }
    //determines default direction for ghost to turn in
    else if (ghost->map[y - 1][x] == ghost->mapToken 
    && y > targetY
    )
    {
        ghost->mDir = up;
    }
    else if (ghost->map[y][x - 1] == ghost->mapToken 
    && x > targetX
    )
    {
        ghost->mDir = left;
    }
    else if (ghost->map[y + 1][x] == ghost->mapToken 
    && y < targetY
    )
    {
        ghost->mDir = down;
    }
    else if (ghost->map[y][x + 1] == ghost->mapToken 
    && x < targetX
    )
    {
        ghost->mDir = right;
    } else if (inghosthouse(ghost->mBody) && x > targetX){
        ghost->mDir = left;
    } else if (inghosthouse(ghost->mBody) && x < targetX){
        ghost->mDir = right;
    }

    else
    {
        for (size_t i = 0; i < 4; i++)
        {
            if (isClear(direction(i), ghost->mBody)
            &&!(direction(i) == down && prevDir == up)
            &&!(direction(i) == up && prevDir == down)
            &&!(direction(i) == right && prevDir == left)
            &&!(direction(i) == left && prevDir == right))
            {
                ghost->mDir = direction(i);
                break;
            }
            
        }
        
    }
    
}
/**
 * @brief fills the ghost's map with the direction it needs to go to get to pac man
 * 
 * @param row ghost row
 * @param col ghost col
 * @param ghost ghost itself
 * @param targetX ghost target col
 * @param targetY ghost target row
 * @return true ghost can go this way
 * @return false ghost can not go this way
 */
bool Game::fillPath(int row, int col, Ghosts * ghost, int targetX, int targetY)
{
    //Base 1 If the chosen row or collumn is a row or collumn greater than the rowsize or collumn size or lesser than 0
    if (row > GRID_SIZE_Y || row < 0 || col > GRID_SIZE_X || col < 0) 
    {
        return false;
    }
    //Base 2 else if the position in the maze is the goal it will return true
    else if (row == targetY && col == targetX) 
    {
        return true;
    }
    else if (grid[row][col] == 'w' || ghost->map[row][col] == ghost->mapToken) // else if it is a wall or a path already taken it will return false
    {
        return false;
    }
    else
    {
        ghost->map[row][col] = ghost->mapToken;//Marks the current path it is taking
        if (abs(row - targetY) < abs(col - targetX))
        {
            if (
            fillPath(row - 1, col, ghost, targetX, targetY)
            || fillPath(row, col - 1, ghost, targetX, targetY) 
            || fillPath(row + 1, col, ghost, targetX, targetY) 
            || fillPath(row, col + 1, ghost, targetX, targetY))
            {
                return true;
            }
        }
        else if (abs(targetY - row) > abs(targetX - col))
        {
            if (
            fillPath(row, col - 1, ghost, targetX, targetY)
            || fillPath(row, col + 1, ghost, targetX, targetY) 
            || fillPath(row - 1, col, ghost, targetX, targetY) 
            || fillPath(row + 1, col, ghost, targetX, targetY))
            {
                return true;
            }
        }
        else
        {
            ghost->map[row][col] = ' '; //Else it will retrace its steps
        }
        return false;
    }
}
/**
 * @brief animates ghosts
 * 
 */
void Game::Ghosts::animate()
{
    //Depending on the state it will animate differently
    if (state != panic)
    {
        mBody.setTextureRect(sf::IntRect(frames[framecount/8], 16, 16, 16));
        if (framecount == 15)
        {
            framecount = 0;
        }
        else
        {
            framecount++;
        }
    }
    else
    {
        mBody.setTextureRect(sf::IntRect(panicFrames[framecount/8], 16, 16, 16));
        if (framecount == 15)
        {
            framecount = 0;
        }
        else
        {
            framecount++;
        }
    }
    
}
/**
 * @brief Construct a new Game:: Pellets:: Pellets object
 * 
 * @param isSuper 
 */
Game::Pellets::Pellets(bool isSuper)
{
    //if pellet is super pellet it will change sprite
    if (isSuper)
    {
        mSprite.setTextureRect({16*15, 0, 16, 16});
    }
    else
    {
        mSprite.setTextureRect({16*14, 0, 16, 16});
    }
    super = isSuper;
    mSprite.setOrigin(8, 8);
}
/**
 * @brief Eats a pellet
 * 
 * @param pellet pellet to eat
 */
void Game::eatPellet(Game::Pellets * pellet)
{
    if (!pellet->eaten && (returnrow(pellet->mSprite) == returnrow(mPlyr->mSprite) && returncol(pellet->mSprite) == returncol(mPlyr->mSprite)))
    {
        pellet->eaten = true;
        if (pellet->super)
        {
            sDots--;
        }
        else
        {        
            dots--;
        }
    }
    
}
/**
 * @brief Creates a new fruit object
 * 
 */
Game::Fruit::Fruit()
{
    mSprite.setOrigin(8,8);
    mSprite.setTextureRect({16 * level, 32, 16,16});
}
/**
 * @brief Eats fruit
 * 
 * @param fruit 
 */
int Game::eatFruit(Game::Fruit * fruit)
{
    fruit->spawned = false;
    return (fruit)->values[(fruit)->level];
}
void Game::Fruit::toDespawn()
{
    spawned = false;
}

/****Map and grid functions****/



void Game::displaymap(){
    maptexture.loadFromFile("mapR.png");
    map.setTexture(maptexture);
    map.setOrigin(maptexture.getSize().x/2, maptexture.getSize().y/2);
    map.setPosition(mWindow.getSize().x/2, mWindow.getSize().y/2);
}
/**
 * @brief Initializes grid.
 * w = wall
 * t = portal
 * p = pink ghost
 * b = blue ghost
 * o = orange ghost
 * r = red ghost
 * c = pacman
 * f = fork
 * s = Player spawn
 */
void Game::initializegrid(){
    for (int i = 0; i < 31; i++){
        for (int j = 0; j < 33; j++){
            grid[j][i] = ' ';
        }
    }
    //initialize outer walls
    for (int i = 0; i < 33; i++){
        grid[i][0] = 'w';
        grid[i][30] = 'w';
        if (i < 31){
        grid[32][i] = 'w';
        grid[0][i] = 'w';
        }
    }
    grid[16][0] = 't';
    grid[16][30] = 't';
    setwall(7,7,2,2);
    setwall(2,5,2,10);
    setwall(2,5,2,16);
    setwall(7,7,2,22);
    setwall(4,11,5,10);
    setwall(6,4,10,2);
    setwall(9,17,10,7);
    setwall(6,4,10,25);
    setwall(6,4,17,2);
    setwall(6,4,17,25);
    setwall(3,17,20,7);
    setwall(3,3,23,14);
    setwall(7,7,24,2);
    setwall(7,7,24,22);
    setwall(8,3,24,10);
    setwall(8,3,24,18);
    setwall(4,3,27,14);

    //Set forks
    for (int i = 0; i < 33; i++){
        for (int j = 0; j < 31; j++){
            int openpaths = 0;
            if(grid[i+1][j] == ' ')
            openpaths++;
            if(grid[i-1][j] == ' ')
            openpaths++;
            if(grid[i][j+1] == ' ')
            openpaths++;
            if(grid[i][j-1] == ' ')
            openpaths++;
            if (openpaths >= 3){
                grid[i][j] = 'f';
            }
        }
    }
    for (int i = 12; i < 17; i++){
        for (int j = 9; j < 22; j++){
            grid[i][j] = ' ';
        }
    }
    grid[19][15] = 's';
    grid[14][10] = 'r';
    grid[14][13] = 'b';
    grid[14][17] = 'p';
    grid[14][20] = 'o';
}
/**
 * @brief Function to initialize part of grid.
 * 
 * @param length 
 * @param start 
 * @param dir 
 * @param type 
 */
void Game::setwall(int length, int width, int row, int col){
    for (int i = row; i < length + row; i++){
        for (int j = col; j < width + col; j++){
            grid[i][j] = 'w';
        }
    }
}
/**
 * @brief For testing the grid
 * 
 */
void Game::displaygrid(){
    for (int i = 0; i < 33; i++){
        for (int j = 0; j < 31; j++){
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
/**
 * @brief Sets the 0,0 origin for the map/grid.
 * 
 */
void Game::setgridorigin(){
    gridoriginx = (float)map.getPosition().x-((float)map.getGlobalBounds().width/2.0)+(4.0*scale);
    gridoriginy = (float)map.getPosition().y-((float)map.getGlobalBounds().height/2.0)+(4.0*scale);
}
/**
 * @brief Returns the y coordinates of a given row in the grid.
 * 
 * @param row 
 * @return float 
 */
float Game::getgridy(int row){
    return (8*scale)*(row) + gridoriginy;
}
/**
 * @brief Returns the x coordinates of a given collumn in the grid.
 * 
 * @param col 
 * @return float 
 */
float Game::getgridx(int col){
    return (8*scale)*(col) + gridoriginx;
}
/**
 * @brief Returns the row that a sprite is in.
 * 
 * @param s 
 * @return int 
 */
int Game::returnrow(sf::Sprite s){
    return (s.getPosition().y - (mWindow.getSize().y/2 - map.getGlobalBounds().height/2)) / ((int)8*scale);
}
/**
 * @brief Returns the collumn that a sprite is in.
 * 
 * @param s 
 * @return int 
 */
int Game::returncol(sf::Sprite s){
    return (s.getPosition().x - (mWindow.getSize().x/2 - map.getGlobalBounds().width/2)) / ((int)8*scale);
}
/**
 * @brief Displays Gui
 * 
 */
void Game::displayGUI()
{

}
/**
 * @brief Updates Gui
 * 
 */
void Game::updateGUI()
{
    score.setString(std::to_string(points) + "0");
    score.setPosition(mWindow.getSize().x / 4, mWindow.getSize().y / 4);
}
/**
 * @brief Checks if a sprite is able to teleport to other side of map. Sets positions of sprite to destination.
 * 
 * @param s 
 */
void Game::teleport(sf::Sprite &s){
    if (returnrow(s) == 16 && returncol(s) == 0){
        s.setPosition(getgridx(29), getgridy(16));
        mPlyr->mDir = left;
    } else if (returnrow(s) == 16 && returncol(s) == 30){
        s.setPosition(getgridx(1), getgridy(16));
        mPlyr->mDir = right;
    }
}
/**
 * @brief Spawn all ghosts
 * 
 */
void Game::spawn(){
    if (!inky->spawned){
        movetospawn(inky);
        inky->spawned = true;
    }
    if ((dots <= MAX_DOTS * .7) && !blinky->spawned){
        movetospawn(blinky);
        blinky->spawned = true;
    }

    if (blinky->spawned && !pinky->spawned && !(inghosthouse(blinky->mBody))){
        movetospawn(pinky);
        pinky->spawned = true;
    }

    if (!clyde->spawned && dots <= MAX_DOTS * 0.3){
        movetospawn(clyde);
        clyde->spawned = true;
    }
}
/**
 * @brief Move ghost to spawnpoint
 * 
 * @param ghost 
 */
void Game::movetospawn(Ghosts *ghost){
    ghost->objPos[0][0] = 15;
    ghost->objPos[0][1] = 14;
    choosePath(ghost);
}
/**
 * @brief Test if ghost is inside ghost house
 * 
 * @param s 
 * @return true 
 * @return false 
 */
bool Game::inghosthouse(sf::Sprite s){
    if (returnrow(s) < 18 && returnrow(s) > 10 && returncol(s) < 24 && returncol(s) > 7){
        return true;
    } else {
        return false;
    }
}