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
            return true;
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
    lives = 3;
    if(!plyrStillTexture.loadFromFile("player.png"))
        {
            std::cout << "Error opening file\n";
            exit(1);
        } 
    if(!plyrMvTexture.loadFromFile("playermv.png"))
        {
            std::cout << "Error opening file\n";
            exit(1);
        }  
    sf::Vector2u imageSize = plyrStillTexture.getSize();
    plyrSprite.setTexture(plyrStillTexture);  //Sets player texture to pacman
    plyrSprite.setPosition(110,120);      
    plyrSprite.scale(1,1);          
    plyrSprite.setOrigin(imageSize.x/2, imageSize.y/2);  
}
bool Game::isDone() const
{
    if (lives <= 0 || !mWindow.isOpen())
    {
        return true;
    }
    return false;
}
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
void Game::update()
{
    movePlyr();
    //move ghosts
}
void Game::render()
{
    mWindow.clear(sf::Color::Black);
    //Draw player
    mWindow.draw(plyrSprite);
    //draw ghosts
    mWindow.display();
}
void Game::setLives(int num)
{
    lives += num;
}
int Game::getLives()const
{
    return lives;
}
void Game::movePlyr()
{
//Gets direction
    plyrSprite.setTexture(plyrMvTexture);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        plyrDir = up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        plyrDir = down;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        plyrDir = right;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        plyrDir = left;
    }

//Moves character
    if (plyrDir == up)
    {
        plyrSprite.setRotation(270);
        plyrSprite.setPosition(plyrSprite.getPosition().x, plyrSprite.getPosition().y - plyrMvSpeed);
    }
    else if (plyrDir == down)
    {
        plyrSprite.setRotation(90);
        plyrSprite.setPosition(plyrSprite.getPosition().x, plyrSprite.getPosition().y + plyrMvSpeed);
    }
    else if (plyrDir == right)
    {
        plyrSprite.setRotation(0);
        plyrSprite.setPosition(plyrSprite.getPosition().x + plyrMvSpeed, plyrSprite.getPosition().y);
    }
    else if (plyrDir == left)
    {
        plyrSprite.setRotation(180);
        plyrSprite.setPosition(plyrSprite.getPosition().x - plyrMvSpeed, plyrSprite.getPosition().y);
    }
}