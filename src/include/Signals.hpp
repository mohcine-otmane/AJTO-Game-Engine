/*Note*/
/*Signals can be emitted by any object and they will all be run in one separate thread*/

#ifndef SIGNALS_H
#define SIGNALS_H

#include<vector>
#include "Signal.h"
#include <SFML/Graphics.hpp>

struct Signal{
    float duration;
};



class Signals
{

public:
    Signals(/* args */);
    bool Emit(float duration);
    bool SignalLoop(Signal signal);
    ~Signals();



private:
    std::vector<Signal>* VecSignals;
};

Signals::Signals(/* args */)
{
}


bool Signals::Emit(float duration) {
    Signal signal;
    // Init the signal to be added to the VecSignals vector
    signal.duration = duration;


    VecSignals->push_back(signal);
}

bool Signals::SignalLoop(Signal signal){
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds()<signal.duration)
    {
        /* code */
    }
    
}



Signals::~Signals()
{
}








#endif