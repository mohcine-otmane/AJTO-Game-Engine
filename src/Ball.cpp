#include "Ball.h"
#include <cmath>

Ball::Ball(float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity)
    : velocity(velocity)
{
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setPosition(position);
    positions.push_back(position); // Initialize with the starting position
}

void Ball::move() {
    shape.move(velocity);
    positions.push_back(shape.getPosition());

    // Optionally limit the size of the positions history to avoid performance issues
    if (positions.size() > 00) {
        positions.erase(positions.begin()); // Keep the last 100 positions
    }
}

void Ball::checkCollision(const sf::RenderWindow& window) {
    sf::Vector2f position = shape.getPosition();
    float radius = shape.getRadius();

    // Check for collision with the window boundaries
    if (position.x <= 0 || position.x + radius * 2 >= window.getSize().x) {
        velocity.x = -velocity.x;  // Reverse the horizontal direction
    }
    if (position.y <= 0 || position.y + radius * 2 >= window.getSize().y) {
        velocity.y = -velocity.y;  // Reverse the vertical direction
    }
}

bool Ball::checkCollisionWithBall(Ball& other) {
    sf::Vector2f delta = other.shape.getPosition() - shape.getPosition();
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float radiusSum = shape.getRadius() + other.shape.getRadius();

    return distance < radiusSum;
}

void Ball::resolveCollision(Ball& other) {
    sf::Vector2f delta = other.shape.getPosition() - shape.getPosition();
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (distance == 0.0f) {
        return; // Prevent division by zero
    }

    // Normalized collision vector
    sf::Vector2f normal = delta / distance;

    // Relative velocity
    sf::Vector2f relativeVelocity = other.velocity - velocity;

    // Velocity along the normal
    float velocityAlongNormal = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

    if (velocityAlongNormal > 0) {
        return; // Balls are moving apart
    }

    // Elastic collision response
    float restitution = 1.0f; // Perfectly elastic collision
    float impulse = -(1 + restitution) * velocityAlongNormal;
    impulse /= (1 / shape.getRadius()) + (1 / other.shape.getRadius());

    sf::Vector2f impulseVector = impulse * normal;

    velocity -= impulseVector / shape.getRadius();
    other.velocity += impulseVector / other.shape.getRadius();
}

void Ball::draw(sf::RenderWindow& window) const {
    // Draw the trace
    for (size_t i = 1; i < positions.size(); ++i) {
        sf::Vertex line[] = {
            sf::Vertex(positions[i - 1], shape.getFillColor()),
            sf::Vertex(positions[i], shape.getFillColor())
        };
        window.draw(line, 2, sf::Lines);
    }

    // Draw the ball
    window.draw(shape);
}
