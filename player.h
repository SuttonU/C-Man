#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "game.h"
class Player : public Game, public sf::Sprite
{
public:
    Player();
    ~Player();
};
#endif