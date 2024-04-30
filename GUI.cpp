#include "GUI.h"
/**
 * @brief creates gui object
 * 
 */
GUI::GUI() : Game(10)
{
    points = 0;
    scoreGui.setScale(scale, scale);
    scoreGui.setString(std::to_string(points) + '0');
    highscoreGui.setScale(scale, scale);
    highscoreGui.setString(std::to_string(points) + '0');
    plyrLives.setScale(scale, scale);
    plyrLives.setString(std::to_string(lives));
    gameLevel.setScale(scale, scale);
    gameLevel.setString('3');
}
/**
 * @brief updates the gui on the screen
 * 
 */
void GUI::updateGui()
{
    scoreGui.setString(std::to_string(points) + '0');
    highscoreGui.setString(std::to_string(points) + '0');
}