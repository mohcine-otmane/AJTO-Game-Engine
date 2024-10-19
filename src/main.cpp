#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Actor.hpp"
#include "include/InputManager.hpp"
#include "include/Signals.hpp"
#include "include/Game.hpp"
#include "include/AJTO.hpp"



std::vector<std::string> VecTexturePaths = {"assets/Walk.png", "assets/WalkRight.png", "assets/Idle.png"};
std::vector<sf::Texture> VecTexures;
sf::Font font;


sf::RectangleShape rect;

class AJTO : public Game {
public:
    sf::Vector2f velocity = sf::Vector2f(0, 0); // Velocity for movement
    Actor* player; // Player actor

    // Set up the game window and initialize actors
    void SetUp() override {
        // aj::StoreTextures(&VecTexturePaths, &VecTexures);

        // font->loadFromFile("assets/CURLZ___.TTF");

        this->window.create(sf::VideoMode(800, 600), "AJTO Game Engine");

        // Create player actor dynamically
        player = new Actor(sf::Vector2f(0, 0), sf::Vector2f(10.f, 10.f));
        player->AddAnimation("WalkLeft", VecTexturePaths[0], sf::Vector2i(10, 1), true);
        // player->AddAnimation("WalkRight", VecTexturePaths[1], sf::Vector2i(10, 1), true);
        // player->AddAnimation("Idle", VecTexturePaths[2], sf::Vector2i(7, 1), true);
        // player->AddAnimation("AtackRight", VecTexturePaths[2], sf::Vector2i(7, 1), true);
        player->currentAnimation = player->Animations["WalkLeft"];
        player->SetCollisionShape(); // Ensure collision shape is set
        Actors["player"] = player;

        rect.setSize(sf::Vector2f(2,2));
        rect.setFillColor(sf::Color::Red);
    }


    // Main update loop where events and game logic are handled
    void UpDate(float deltaTime, sf::Event event) override {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Close window on close event
            }

            // Handle input
            inputManager.OnKeyPressed(&event, &signalSystem);
            HandleMovement(deltaTime); // Move player based on signals
        }
        // Update actors and check for collisions
        Actors["player"]->Update();
        Actors["player"]->currentAnimation->playAnimation(deltaTime);

        

        rect.setPosition(Actors["player"]->currentAnimation->getSprite().getOrigin());

        // Clear, render, and display the updated game window
        window.clear();
        Actors["player"]->Render(&window);
        window.draw(rect);
        // aj::DisplayText("Text", sf::Vector2f(100,100),font, &window);
        window.display();
    }

    // Handle player movement based on signals
    void HandleMovement(float deltaTime) {
    // Reset velocity to 0 at the start of each frame
    velocity.x = 0;
    velocity.y = 0;

    // Move player actor based on signals
    if (signalSystem.HasEmitted("W")) {
        velocity.y -= player->speed.y;
    } else if (signalSystem.HasEmitted("S")) {
        velocity.y += player->speed.y;
    } else if (signalSystem.HasEmitted("A")) {
        velocity.x -= player->speed.x;
        // Flip the player sprite to the left
        player->currentAnimation->getSprite().setScale(-1.f, 1.f);
        // player->currentAnimation = player->Animations["Walk"];
    } else if (signalSystem.HasEmitted("D")) {
        velocity.x += player->speed.x;
        // Reset the player sprite to face right (default)
        player->currentAnimation->getSprite().setScale(1.f, 1.f);
        // player->currentAnimation = player->Animations["Walk"];
    }

    // If no movement is detected, switch to the Idle animation
    if (velocity.x == 0 && velocity.y == 0) {
        // player->currentAnimation = player->Animations["Idle"];
    }

    // Update player position by adding the velocity, scaled by deltaTime
    player->position += velocity;
}


    // Destructor to clean up dynamically allocated memory
    ~AJTO() {
        delete player; // Delete player actor
    }
};




int main() {

    AJTO ajto;

    ajto.SetUp();
    ajto.GameLoop();

    return 0;
}