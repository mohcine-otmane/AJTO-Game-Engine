#include "include/Game.hpp"




Game::Game(/* args */)
{
}


void Game::SetUp() {
    
}

void Game::UpDate(float deltaTime,sf::Event event) {

}

void Game::GameLoop() {
    while (this->window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        UpDate(deltaTime, event);
    }
}

Game::~Game()
{
}