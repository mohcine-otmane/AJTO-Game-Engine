#include "include/Actor.h"
#include <SFML/Graphics.hpp>
#include "include/Physics.h"

Actor::Actor(sf::Vector2f position, sf::Vector2f speed)
{
    this->position = position;
    this->speed = speed;

    this->DefaultShape.setSize(sf::Vector2f(100.f,100.f));
    this->DefaultShape.setPosition(position);
    this->DefaultShape.setFillColor(sf::Color(255,0,0));
}

void Actor::MoveTo(float x, float y) {
    this->position = sf::Vector2f(x,y);
}


void Actor::Physics() {
    if(gravity) {
        // this->position.y += 
    }
}


void Actor::Move(sf::Event event) {
    // Controls go here
}

void Actor::Render(sf::RenderWindow* window) {
    window->draw(this->DefaultShape);
}


Actor::~Actor()
{
}