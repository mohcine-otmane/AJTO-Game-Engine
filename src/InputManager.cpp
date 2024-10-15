#include "include/InputManager.hpp"





InputManager::InputManager(/* args */)
{
}

void InputManager::OnKeyPressed(sf::Event* event, Signals* signalSystem) {
    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::W) {
            signalSystem->Emit("W", false);
        } else if (event->key.code == sf::Keyboard::S) {
            signalSystem->Emit("S", false);
        } else if (event->key.code == sf::Keyboard::A) {
            signalSystem->Emit("A", false);
        } else if (event->key.code == sf::Keyboard::D) {
            signalSystem->Emit("D", false);
        }
    }
}





InputManager::~InputManager()
{
}
