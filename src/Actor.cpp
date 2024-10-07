#include "include\Actor.h"
#include <SFML/Graphics.hpp>


Actor::Actor(sf::Vector2f position, sf::Vector2f speed)
{
    this->position = position;
    this->speed = speed;

    this->DefaultShape.setSize(sf::Vector2f(100.f,100.f));
    this->DefaultShape.setPosition(position);
}

void Actor::Move(float x, float y) {
    if(x>0) {
        this->position.x += this->speed.x;
    } else if (x<0)
    {
        this->position.x -= this->speed.x;
    }
    if(y>0) {
        this->position.y -= this->speed.y;
    } else if (y<0)
    {
        this->position.y += this->speed.y;
    }
}


void Actor::Render(sf::RenderWindow* window) {
    window->draw(this->DefaultShape);
}





Actor::~Actor()
{
}