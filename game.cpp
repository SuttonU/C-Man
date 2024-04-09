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
void Game :: displaymenu(){
    texture.loadFromFile("Pacmantitle.png");
    titleimage.setTexture(texture);
    titleimage.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    titleimage.setScale(0.5,0.5);
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

    mWindow.draw(titleimage);
    mWindow.draw(playbutton);
    mWindow.draw(infobutton);
    mWindow.display();
    while(1){
    if (updatemenu()){
        break;
    }
    }
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

Game::Game() : mWindow(sf::VideoMode(1920 , 1080), "C-Man")
{
    if(!mTextureFile.loadFromFile("spritesheet.png"))
    {
        std::cout << "Error loading game sprite sheet\n";
        exit(101);
    }
    lives = 3;
    blinky = new Ghosts();
    blinky->mBody.setTexture(mTextureFile);
    blinky->mEyes.setTexture(mTextureFile);
    //inky = new Ghosts(sf::Color::Blue);
    //inky->mSprite.setTexture();
    //pinky = new Ghosts(sf::Color::Magenta);
    //pinky->mSprite.setTexture();
    //clyde = new Ghosts();
    //clyde->mSprite.setTexture(mTextureFile);
    pellets[0] = new Pellets;
    pellets[0]->mSprite.setTexture(mTextureFile);
    mPlyr = new Player;
    mPlyr->mSprite.setTexture(mTextureFile);
    mPlyr->setHb({ 8.f, 8.f, 16.f, 16.f });
    blinky->setHb({ 8.f, 8.f, 16.f, 16.f });
    mPlyr->mSprite.setPosition(mWindow.getSize().x/2, mWindow.getSize().y/2 + mPlyr->mSprite.getScale().x * 16);
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
 * @brief Closes the window if player presses the close button
 * 
 */
void Game::closeWindow()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            // Close window button clicked.
            mWindow.close();
        }
    }
}
/**
 * @brief Updates the sprites on the screen
 * 
 */
void Game::update()
{
    while (!play)
    {
        usleep(5000000);
    }
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
    if (mPlyr->getGlobalHb().intersects(pellets[0]->getGlobalHb()))
    {
        pellets[0]->mSprite.setPosition({0,0});
    }
    else if (mPlyr->getGlobalHb().intersects(blinky->getGlobalHb())/* || mPlyr->getGlobalHb().intersects(inky->getGlobalHb()) || mPlyr->getGlobalHb().intersects(pinky->getGlobalHb()) || mPlyr->getGlobalHb().intersects(clyde->getGlobalHb())*/)
    {
        deathAnimation();
        usleep(5000000);
        mPlyr->mSprite.setPosition(110,120);
        render();
        lives--;
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
    mSprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
    mSprite.setOrigin(8, 8);
    mSprite.setScale(2,2);        
    //Set position to start of maze
    //plyrSprite.setPosition();
}
/**
 * @brief Moves player through taking in user input
 * 
 */
void Game::Player::move()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        mDir = up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        mDir = down;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        mDir = right;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        mDir = left;
    }

//Moves character
    if (mDir == up)
    {
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
 * @brief Sets the player hitbox
 * 
 * @param hitbox hitbox coordinates
 */
void Game::Player::setHb(const sf::FloatRect &hitbox)
{
    mHB = hitbox;
}
/**
 * @brief Gets the hitbox of the player
 * 
 * @return sf::FloatRect bounds of hitbox
 */
sf::FloatRect Game::Player::getGlobalHb() const
{
    return mSprite.getTransform().transformRect(mHB);
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
    setHb({ 8.f, 8.f, 16.f, 16.f });
    mBody.setTextureRect(sf::IntRect(0,16,16,16));
    mBody.setOrigin(8, 8);
    mBody.setScale(2,2);
    mBody.setPosition(800,800); 
    mEyes.setTextureRect(sf::IntRect(16*12,16,16,16));
    mEyes.setScale(2,2);
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
/**
 * @brief Sets the ghost hitbox
 * 
 * @param hitbox hitbox coordinates
 */
void Game::Ghosts::setHb(const sf::FloatRect &hitbox)
{
    mHB = hitbox;
}
/**
 * @brief Gets the hitbox of the ghost
 * 
 * @return sf::FloatRect bounds of hitbox
 */
sf::FloatRect Game::Ghosts::getGlobalHb() const
{
    return mBody.getTransform().transformRect(mHB);
}
/**
 * @brief Constructs a new pellet
 * 
 */
Game::Pellets::Pellets()
{
    setHb({ 7.f, 7.f, 16.f, 16.f });
    mSprite.setTextureRect({16*14, 0, 16, 16});
    mSprite.setOrigin(8, 8);
    mSprite.setScale(2,2);
}
sf::FloatRect Game::Pellets::getGlobalHb() const
{
    return mSprite.getTransform().transformRect(mHB);
}
void Game::Pellets::setHb(const sf::FloatRect &hitbox)
{
    mHB = hitbox;
}

void Game::displaymap(){
    maptexture.loadFromFile("mapR.png");
    map.setTexture(maptexture);
    map.setOrigin(maptexture.getSize().x/2, maptexture.getSize().y/2);
    map.setScale(2,2);
    map.setPosition(mWindow.getSize().x/2, mWindow.getSize().y/2);
    mWindow.draw(map);
    mWindow.display();
}