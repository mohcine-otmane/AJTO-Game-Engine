#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <vector>

class Ball {
public:
    Ball(float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity);

    void move();
    void checkCollision(const sf::RenderWindow& window);
    bool checkCollisionWithBall(Ball& other);
    void resolveCollision(Ball& other);
    void draw(sf::RenderWindow& window) const;

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    std::vector<sf::Vector2f> positions; // Stores the history of positions
};

#endif
