#include "include/Actor.hpp"
#include <SFML/Graphics.hpp>
#include "include/Physics.hpp"
#include <iostream>
#include <filesystem>
#include "include/Actor.hpp"
#include "include/Game.hpp"


Actor::Actor(sf::Vector2f position, sf::Vector2f speed):position(position), speed(speed) {}


void Actor::Update() {
    currentAnimation->getSprite().setPosition(position);
}

void Actor::AddAnimation(std::string animationName, sf::Vector2i numberFrames, bool loopAnimation) {
    Animations[animationName] = new Animation(animationName, numberFrames, loopAnimation);
    // Animations[animationName]
}

void Actor::SetAnimation(std::string animationName) {
    currentAnimation =  Animations[animationName];
}

// void Actor::CheckCollision() {
//     // if(collisionShape.getGlobalBounds().intersects(otherActor.collisionShape.getGlobalBounds())) {

//     // }
// }

void Actor::Render(sf::RenderWindow* window) {
    window->draw(currentAnimation->getSprite());
}

Actor::~Actor() {
}
