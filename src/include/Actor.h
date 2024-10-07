#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>

class Actor
{

public:
    Actor(sf::Vector2f position, sf::Vector2f speed);

    void Move(float x, float y);
    void Render(sf::RenderWindow *window);
    ~Actor();

private:
    sf::Vector2f position;
    sf::Vector2f speed;
    sf::Vector2f acceleration;

    sf::Sprite Sprite;
    sf::ConvexShape CollisionShape;
    sf::RectangleShape DefaultShape;
};











#endif