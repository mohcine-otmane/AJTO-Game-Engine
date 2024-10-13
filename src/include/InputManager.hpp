#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Signals.hpp"


class InputManager
{

public:
    InputManager(/* args */);

    void OnKeyPressed(sf::Event *event, Signals* signalSystem);


    ~InputManager();

private:
    
};













#endif