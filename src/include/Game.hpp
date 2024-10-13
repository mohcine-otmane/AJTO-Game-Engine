/*--- This is the central class where everything takes shape ---*/
/*--- The Game class stores Actors, Levels, Game data, handles Level transitions and so much more ---*/
/*--- When we save the game we save the Game class variables ---*/


#ifndef GAME_HPP
#define GAME_HPP

#include "Actor.hpp"
#include "Level.hpp"


class Game
{

public:
    Game(/* args */);

    void SetUp();

    void Loop(float deltaTime);

    ~Game();

private:

    // Actors will interact with each other, so any player must access any other player to check for collisions (We will find a more optimized solution later on)
    std::vector<Actor*> VecActor; // All the actors of the game are stored here
};

Game::Game(/* args */)
{
}


void Game::SetUp() {

}

void Game::Loop(float deltaTime) {

}

Game::~Game()
{
}












#endif
