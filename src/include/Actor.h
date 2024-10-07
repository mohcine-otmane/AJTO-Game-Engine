#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>


// Actors may include players, enemies, objects like a arrows
class Actor
{

public:
    Actor(sf::Vector2f position, sf::Vector2f speed);

    void MoveTo(float x, float y);
    void Physics();
    void Move(sf::Event event);
    void Render(sf::RenderWindow *window);
    ~Actor();

private:
    sf::Vector2f position;
    sf::Vector2f speed;
    sf::Vector2f acceleration;
    bool gravity = true;
    
    sf::Sprite Sprite;
    sf::ConvexShape CollisionShape;
    sf::RectangleShape DefaultShape;
};





#endif