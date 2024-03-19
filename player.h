#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "game.h"
enum direction
{up, down, left, right};
class player : public Game, public sf::Sprite
{
private:
    sf::Texture stillTexture;
    sf::Texture mvTexture;
    sf::Sprite plyr;
    sf::Vector2f mPosition;
    float mMvSpeed = 0.5;
public:
    player();
    ~player();
    virtual void draw(sf::RenderTarget& target,sf::RenderStates direction) const;
    void move(direction &dir, sf::RenderWindow& window);

};
#endif