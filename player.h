/**
 * @file player.h
 * @author Sutton Jones
 * @brief Header for Player class
 * @version 0.1
 * @date 2024-03-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "game.h"
class Player : public sf::Sprite
{
public:
    Player();
    ~Player();
};
#endif