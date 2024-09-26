#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include "game.h"
#include <vector>
class Entity
{
private:
    int pos[2];
    double mvSpeed;
    double coords[2];

    std::string mName;
    direction mDir;
    sf::Sprite mSprite;
    
public:
    Entity(std::string name, sf::Texture mTextureFile, sf::IntRect rect);
    void move();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates status = sf::RenderStates::Default) const;
};
#endif