/*--- This is the central class where everything takes shape ---*/
/*--- The Game class stores Actors, Levels, Game data, handles Level transitions and so much more ---*/
/*--- When we save the game we save the Game class variables ---*/


#ifndef GAME_HPP
#define GAME_HPP

#include "Actor.hpp"
#include "Level.hpp"
#include "InputManager.hpp"


class Game
{

public:
    Game(/* args */);

    virtual void SetUp();

    virtual void UpDate(float deltaTime,sf::Event event);

    void GameLoop();

    ~Game();

    
protected:
    sf::RenderWindow window;
    // Actors will interact with each other, so any player must access any other player to check for collisions (We will find a more optimized solution later on)
    sf::Clock clock;
    float deltaTime;
    sf::Event event;
    std::map<std::string, Actor*> Actors; // All the actors of the game are stored here
    InputManager inputManager;  // Input manager handles key presses
    Signals signalSystem;      // Signal system to emit key press signals
    
    
};













#endif
