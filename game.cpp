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
    blinky = new Ghosts();
    inky = new Ghosts();
    pinky = new Ghosts();
    clyde = new Ghosts();
    mPlyr = new Player;
    pellets[0] = new Pellets;
    //Set textures
    blinky->mBody.setTexture(mTextureFile);
    blinky->mEyes.setTexture(mTextureFile);
    inky->mBody.setTexture(mTextureFile);
    inky->mEyes.setTexture(mTextureFile);
    pinky->mBody.setTexture(mTextureFile);
    pinky->mEyes.setTexture(mTextureFile);
    clyde->mBody.setTexture(mTextureFile);
    clyde->mEyes.setTexture(mTextureFile);
    pellets[0]->mSprite.setTexture(mTextureFile);
    mPlyr->mSprite.setTexture(mTextureFile);
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
    mPlyr->mSprite.setPosition(mWindow.getSize().x/2, mWindow.getSize().y/2 + mPlyr->mSprite.getScale().x * 16);
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

            mPlyr->mvSpeed = 2.0 * scale;
            blinky->mvSpeed = 2.0 * scale;
            map.setScale(scale, scale);
            mPlyr->mSprite.setScale(scale, scale);
            blinky->mBody.setScale(scale, scale);
            blinky->mEyes.setScale(scale, scale);
            map.setPosition(mWindow.getSize().x / 2, mWindow.getSize().y / 2);

        }
        else if (updatebutton(event, playbutton))
        {
            play = true;
            mWindow.clear();
            mWindow.display();
            
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
    delete pellets[0]; 
    mPlyr = nullptr; 
    inky = nullptr;
    blinky = nullptr;
    pinky = nullptr; 
    clyde = nullptr;
    pellets[0] = nullptr;
}
void Game :: displaymenu(){

    mWindow.draw(titleimage);
    mWindow.draw(playbutton);
    mWindow.draw(infobutton);
    mWindow.display();
    windowEvents();
    //while(1){
    //if (updatemenu()){
    //    break;
    //}
    //}
}

bool Game :: updatemenu(){
    sf::Event event;
    while(mWindow.pollEvent(event)){
        if (event.type == sf::Event::Closed)
        mWindow.close();

        if (updatebutton(event, playbutton))
        {
            play = true;
            return true;
        }
        if (updatebutton(event, infobutton)){
            displayinstructions();
        }
        mWindow.clear();
        mWindow.draw(titleimage);
        mWindow.draw(playbutton);
        mWindow.draw(infobutton);
        mWindow.display();
    }
    return false;
}

bool Game :: updatebutton(sf::Event &event, sf::Text &button){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
    bool mouseinbutton = mousePosition.x >= button.getPosition().x - button.getGlobalBounds().width/2
                        && mousePosition.x <= button.getPosition().x + button.getGlobalBounds().width/2
                        && mousePosition.y >= button.getPosition().y - button.getGlobalBounds().height/2
                        && mousePosition.y <= button.getPosition().y + button.getGlobalBounds().height/2;

    if (event.type == sf::Event::MouseMoved){
        if (mouseinbutton){
            button.setFillColor(sf::Color::Red);
            mWindow.draw(button);
        } else {
            button.setFillColor(sf::Color::White);
            mWindow.draw(button);
        }
    }
    if (event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left && mouseinbutton){
            button.setFillColor(sf::Color(150,0,0));
            mWindow.draw(button);
        } else {
            button.setFillColor(sf::Color::White);
            mWindow.draw(button);
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
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Instructions: \n\nUse WASD keys or the arrow keys to move.\n\nDon't get killed by the ghosts.\n\nCollect the dots.");
    instructions.setCharacterSize(40);
    instructions.setOrigin(instructions.getGlobalBounds().width/2, instructions.getGlobalBounds().height/2 + 15);
    instructions.setPosition(mWindow.getSize().x/2, 700);

    sf::Text backbutton;
    backbutton.setFont(font);
    backbutton.setString("back");
    backbutton.setCharacterSize(50);
    backbutton.setOrigin(backbutton.getGlobalBounds().width/2, backbutton.getGlobalBounds().height/2 + 15);
    backbutton.setPosition(mWindow.getSize().x/20, mWindow.getSize().y/20);

    mWindow.draw(instructions);
    mWindow.draw(backbutton);
    mWindow.draw(titleimage);
    mWindow.display();
    while (!backtomenu){
        while(mWindow.pollEvent(event)){
            if (event.type == sf::Event::Closed)
            mWindow.close();

            if (updatebutton(event, backbutton)){
                backtomenu = true;
            }
            mWindow.clear();
            mWindow.draw(instructions);
            mWindow.draw(backbutton);
            mWindow.draw(titleimage);
            mWindow.display();
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
 * @brief Updates the sprites on the screen
 * 
 */
void Game::update()
{
    //Moving
    mPlyr->move();
    mPlyr->animate();
    blinky->move();
    if (blinky->mBody.getPosition().x < 0)
    {
        blinky->mDir = right;
    }
    else if (blinky->mBody.getPosition().x > 1920)
    {
        blinky->mDir = left;
    }
    else if (blinky->mBody.getPosition().y > 1080)
    {
        blinky->mDir = up;
    }
    else if (blinky->mBody.getPosition().y < 0)
    {
        blinky->mDir = down;
    }
}
/**
 * @brief Clears, Draws, and displays the screen
 * 
 */
void Game::render()
{
    mWindow.clear(sf::Color::Black);
    //Draw player
    drawGhost(blinky);
    drawGhost(inky);
    drawGhost(pinky);
    drawGhost(clyde);
    mWindow.draw(mPlyr->mSprite);
    mWindow.draw(pellets[0]->mSprite);
    //draw map
    mWindow.draw(map);
    //draw ghosts
    mWindow.display();
}
/**
 * @brief Draws all the parts of the ghost
 * 
 * @param ghost ghost to draw
 */
void Game::drawGhost(Ghosts * ghost)
{
    mWindow.draw(ghost->mBody);
    mWindow.draw(ghost->mEyes);
}
/**
 * @brief Resets the sprites to their starting positions.
 */
void Game::reset()
{
    //Creates newPlyr on reset
}
/**
 * @brief Adds to the amount of lives
 * 
 * @param num number of lives to add
 */
void Game::setLives(int num)
{
    lives += num;
}
/**
 * @brief Returns the amount of lives the player has
 * 
 * @return int amount of lives
 */
int Game::getLives()const
{
    return lives;
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
void Game::Player::move()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (!movement.empty() && movement.top() != up)
        {
            movement.pop();
            movement.push(up);
        }
        else if (movement.empty())
        {
            movement.push(up);
        }
        
        
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (!movement.empty() && movement.top() != down)
        {
            movement.pop();
            movement.push(down);
        }
        else if (movement.empty())
        {
            movement.push(down);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (!movement.empty() && movement.top() != right)
        {
            movement.pop();
            movement.push(right);
        }
        else if (movement.empty())
        {
            movement.push(right);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (!movement.empty() && movement.top() != left)
        {
            movement.pop();
            movement.push(left);
        }
        else if (movement.empty())
        {
            movement.push(left);
        }
    }
    
//Moves character

    //If statement to check if way is not blocked by wall
    if (!movement.empty())
    {
        mDir = movement.top();
        movement.pop();
    }
    if (mDir == up)
    {
        //Formula for graphic tile to tile on array
        mSprite.setRotation(270);
        mSprite.setPosition(mSprite.getPosition().x, mSprite.getPosition().y - mvSpeed);
    }
    else if (mDir == down)
    {
        mSprite.setRotation(90);
        mSprite.setPosition(mSprite.getPosition().x, mSprite.getPosition().y + mvSpeed);
    }
    else if (mDir == right)
    {
        mSprite.setRotation(0);
        mSprite.setPosition(mSprite.getPosition().x + mvSpeed, mSprite.getPosition().y);
    }
    else if (mDir == left)
    {
        mSprite.setRotation(180);
        mSprite.setPosition(mSprite.getPosition().x - mvSpeed, mSprite.getPosition().y);
    }
}
void Game::Player::animate()
{
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
    mPlyr->mSprite.setTextureRect(sf::IntRect(16, 32, 16, 16));
    render();
}
/**
 * @brief Constructs a new ghost object
 * 
 * @param color color of ghost
 */
Game::Ghosts::Ghosts()
{
    //setHb({ 8.f, 8.f, 16.f, 16.f });
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
void Game::Ghosts::move()
{
    if (mDir == up)
        {
            mBody.setPosition(mBody.getPosition().x, mBody.getPosition().y - mvSpeed);
            mEyes.setTextureRect(sf::IntRect(14*16, 16, 16, 16));
        }
        else if (mDir == down)
        {
            mBody.setPosition(mBody.getPosition().x, mBody.getPosition().y + mvSpeed);
            mEyes.setTextureRect(sf::IntRect(15*16, 16, 16, 16));
        }
        else if (mDir == right)
        {
            mBody.setPosition(mBody.getPosition().x + mvSpeed, mBody.getPosition().y);
            mEyes.setTextureRect(sf::IntRect(13*16, 16, 16, 16));
        }
        else if (mDir == left)
        {
            mBody.setPosition(mBody.getPosition().x - mvSpeed, mBody.getPosition().y);
            mEyes.setTextureRect(sf::IntRect(12*16, 16, 16, 16));
        }
    mEyes.setPosition(mBody.getPosition().x, mBody.getPosition().y);
}
Game::Pellets::Pellets()
{
    //setHb({ 7.f, 7.f, 16.f, 16.f });
    mSprite.setTextureRect({16*14, 0, 16, 16});
    mSprite.setOrigin(8, 8);
}
void Game::displaymap(){
    maptexture.loadFromFile("mapR.png");
    map.setTexture(maptexture);
    map.setOrigin(maptexture.getSize().x/2, maptexture.getSize().y/2);
    map.setPosition(mWindow.getSize().x/2, mWindow.getSize().y/2);
    mWindow.draw(map);
    mWindow.display();
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
 * 
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
    grid[19][15] = 'c';
    grid[14][10] = 'r';
    grid[14][13] = 'b';
    grid[14][17] = 'p';
    grid[14][20] = 'o';
    mPlyr->mToken = grid[19][15];
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