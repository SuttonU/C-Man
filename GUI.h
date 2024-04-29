#include "game.h"
#ifndef GUI_H
#define GUI_H
class GUI : public Game
{
    private:
    int highscore;
    sf::Text scoreGui;
    sf::Text highscoreGui;
    sf::Text plyrLives;
    sf::Text gameLevel;
    public:
    GUI();
    void updateGui();
};
#endif