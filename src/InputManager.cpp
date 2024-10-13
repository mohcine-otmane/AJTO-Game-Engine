#include "include/InputManager.hpp"





InputManager::InputManager(/* args */)
{
}

void InputManager::OnKeyPressed(sf::Event* event, Signals* signalSystem) {
    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::W) {
            signalSystem->Emit("MoveUp", false);
        } else if (event->key.code == sf::Keyboard::S) {
            signalSystem->Emit("MoveDown", false);
        } else if (event->key.code == sf::Keyboard::A) {
            signalSystem->Emit("MoveLeft", false);
        } else if (event->key.code == sf::Keyboard::D) {
            signalSystem->Emit("MoveRight", false);
        }
    }
}





InputManager::~InputManager()
{
}
