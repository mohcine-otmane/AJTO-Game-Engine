#include "include\Actor.hpp"
#include <SFML/Graphics.hpp>
#include "include\Physics.hpp"
#include <iostream>
#include <filesystem>

Actor::Actor(sf::Vector2f position, sf::Vector2f speed, std::string TexturePath, int numberOfFrames)
    : position(position), speed(speed), numberOfFrames(numberOfFrames), currentFrame(0), animationSpeed(0.1f), elapsedTime(0.f)
{
    this->DefaultShape.setSize(sf::Vector2f(100.f, 100.f));
    this->DefaultShape.setPosition(position);
    this->DefaultShape.setFillColor(sf::Color(255, 0, 0));

    if (!std::filesystem::exists(TexturePath)) {
        std::cout << "File not found at: " << TexturePath << std::endl;
    } else if (!this->texture.loadFromFile(TexturePath)) {
        std::cout << "Texture Not Loaded, falling back to default shape" << std::endl;
    } else {
        this->Sprite.setTexture(this->texture);
        this->Sprite.setPosition(this->position);
    }
}

void Actor::MoveTo(float x, float y) {
    this->position = sf::Vector2f(x, y);
    this->Sprite.setPosition(this->position);
    this->DefaultShape.setPosition(this->position);
}

void Actor::Physics() {
    if (gravity) {
        this->speed.y += 9.8f;
    }

    // this->position += this->speed;
    this->Sprite.setPosition(this->position);
    this->DefaultShape.setPosition(this->position);
}

void Actor::Move(sf::Event* event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->position.y -= this->speed.y;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
       this->position.y += this->speed.y;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->position.x -= this->speed.x;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->position.x += this->speed.x;
    }
}

void Actor::Update(float deltaTime) {
    elapsedTime += deltaTime;


    if (elapsedTime >= animationSpeed) {
        currentFrame = (currentFrame + 1) % numberOfFrames;
        elapsedTime = 0.f;


        int frameWidth = texture.getSize().x / numberOfFrames;
        Sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, texture.getSize().y));
    }
}

void Actor::Render(sf::RenderWindow* window) {
    if (this->texture.getSize().x > 0 && this->texture.getSize().y > 0) {
        window->draw(this->Sprite);
    } else {
        window->draw(this->DefaultShape);
    }
}

Actor::~Actor() {
}
