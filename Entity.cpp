#include "Entity.h"
Entity::Entity(std::string name, sf::Texture mTextureFile, sf::IntRect rect)
{
    mvSpeed = 1.5 * mSprite.getScale().x;
    mSprite.setTexture(mTextureFile);
    mSprite.setTextureRect(rect);
    mSprite.setOrigin(8, 8);
}

void Entity::move()
{
    switch (mDir)
    {
    case up:
        
        coords[1] = mSprite.getPosition().y - mvSpeed;
        mSprite.setRotation(270);
        break;
    case down:

        coords[1] = mSprite.getPosition().y + mvSpeed;
        mSprite.setRotation(270);
        break;
    case left:

        coords[0] = mSprite.getPosition().x - mvSpeed;
        mSprite.setRotation(180);
        break;
    case right:
        
        coords[0] = mSprite.getPosition().x + mvSpeed;
        mSprite.setRotation(0);
        break;
    
    default:
        break;
    }
    mSprite.setPosition(coords[0], coords[1]);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates status) const
{
    target.draw(mSprite);
}