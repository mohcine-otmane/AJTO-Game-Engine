#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/Graphics.hpp>

class Physics
{

public:
    Physics(/* args */);
    ~Physics();

    void gravity();
    

private:
    sf::Vector2f Gravity = sf::Vector2f(0,9.81f);
    bool GravityOn = false;
    sf::Vector2f Wind = sf::Vector2f(0,0);
};




#endif