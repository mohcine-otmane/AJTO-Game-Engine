#include "include/Actor.hpp"
#include <SFML/Graphics.hpp>
#include "include/Physics.hpp"
#include <iostream>
#include <filesystem>
#include "include/Actor.hpp"
#include "include/Game.hpp"

Actor::Actor(sf::Vector2f position, sf::Vector2f speed) : position(position), speed(speed) {
    CollisionShape = new sf::RectangleShape(); // Ensure CollisionShape is initialized
}

// Add animations for the actor
void Actor::AddAnimation(std::string animationName, sf::Vector2i numberFrames, bool loopAnimation) {
    Animations[animationName] = new Animation(animationName, numberFrames, loopAnimation);
}

// Update the actor's state and collision shape
void Actor::Update() {
    if (currentAnimation) {
        currentAnimation->getSprite().setPosition(position);

        // Update the collision shape to match the sprite size and position
        sf::FloatRect spriteBounds = currentAnimation->getSprite().getGlobalBounds();
        this->CollisionShape->setSize(sf::Vector2f(spriteBounds.width-100, spriteBounds.height-50));  // Fit shape to the sprite, I have done it manually (not good)
        this->CollisionShape->setPosition(spriteBounds.left+50, spriteBounds.top+50);  // Position shape with the sprite
    }
}

// Set the collision shape's size and position based on the sprite's dimensions
void Actor::SetCollisionShape() {
    if (currentAnimation) {
        sf::FloatRect spriteBounds = currentAnimation->getSprite().getGlobalBounds();
        // this->CollisionShape->setSize(sf::Vector2f(spriteBounds.width-50, spriteBounds.height-50));  // Match the sprite's size
        this->CollisionShape->setFillColor(sf::Color(255, 255, 255, 50));  // Set transparent color for visualization
        this->CollisionShape->setPosition(this->position);  // Initially position it at the actor's position
    }
}

// Check if this actor's collision shape intersects with another actor's collision shape
void Actor::CheckCollision(Actor* actor) {
    sf::FloatRect thisBounds = CollisionShape->getGlobalBounds();
    sf::FloatRect otherBounds = actor->CollisionShape->getGlobalBounds();

    // If there's an intersection, resolve the collision
    if (thisBounds.intersects(otherBounds)) {
        std::cout << "Collision detected!" << std::endl;
        
        // Resolve collision by adjusting position based on the direction of movement
        if (thisBounds.left < otherBounds.left) {
            // Collision from left, prevent further movement to the right
            this->position.x -= speed.x;
        } else if (thisBounds.left > otherBounds.left) {
            // Collision from right, prevent further movement to the left
            this->position.x += speed.x;
        }

        if (thisBounds.top < otherBounds.top) {
            // Collision from top, prevent further movement downwards
            this->position.y -= speed.y;
        } else if (thisBounds.top > otherBounds.top) {
            // Collision from bottom, prevent further movement upwards
            this->position.y += speed.y;
        }

        // After resolving, update the position of the collision shape
        CollisionShape->setPosition(position);
    }
}


// Render both the sprite and its collision shape (for debugging)
void Actor::Render(sf::RenderWindow* window) {
    window->draw(currentAnimation->getSprite());  // Render the actor's sprite
    window->draw(*CollisionShape);  // Render the collision shape for debugging purposes
}

// Destructor to clean up dynamically allocated memory
Actor::~Actor() {
    delete CollisionShape;
}
