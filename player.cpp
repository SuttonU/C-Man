#include "player.h"
#include <iostream>
/**
 * @brief Constructs a new player which will have its position set to the beginning of the maze.
 * 
 */
Player::Player()
{
    //Set position to start of maze
    //plyrSprite.setPosition();
}
/**
 * @brief Destroys the player sprite which will reduce the lives by 1;
 * 
 */
Player::~Player()
{
    lives--;
}
