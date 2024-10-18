#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Actor.hpp"
#include "include/InputManager.hpp"
#include "include/Signals.hpp"
#include "include/Game.hpp"
#include "include/AJTO.hpp"



std::vector<std::string> VecTexturePaths = {"assets/WalkLeft.png", "assets/WalkRight.png", "assets/Idle.png"};
std::vector<sf::Texture> VecTexures;
sf::Font font;


class AJTO : public Game {
public:
    sf::Vector2f velocity = sf::Vector2f(0, 0); // Velocity for movement
    Actor* player; // Player actor
    Actor* obstacle; // Obstacle actor
    sf::Clock  forceClock;

    // Set up the game window and initialize actors
    void SetUp() override {

        aj::StoreTextures(VecTexturePaths, VecTexures);


        this->window.create(sf::VideoMode(800, 600), "AJTO Game Engine");

        // Create player actor dynamically
        player = new Actor(sf::Vector2f(100.f, 100.f), sf::Vector2f(10.f, 10.f));
        InitializePlayer(player); // Initialize player settings

        // Create obstacle actor dynamically
        obstacle = new Actor(sf::Vector2f(200.f, 200.f), sf::Vector2f(0.f, 0.f)); // Position obstacle appropriately
        InitializeObstacle(obstacle); // Initialize obstacle settings

        // Store actors in the Actors map
        this->Actors["player"] = player;
        this->Actors["obstacle"] = obstacle;
    }

    // Initialize player settings
    void InitializePlayer(Actor* player) {
        player->AddAnimation("WalkLeft", "assets/WalkLeft.png", sf::Vector2i(10, 1), true);
        player->AddAnimation("WalkRight", "assets/WalkRight.png", sf::Vector2i(10, 1), true);
        player->AddAnimation("Idle", "assets/Idle.png", sf::Vector2i(7, 1), true);
        player->AddAnimation("AtackRight", "assets/Idle.png", sf::Vector2i(7, 1), true);
        obstacle->currentAnimation = obstacle->Animations["WalkLeft"];
        
        player->SetCollisionShape(); // Ensure collision shape is set
    }

    // Initialize obstacle settings
    void InitializeObstacle(Actor* obstacle) {
        obstacle->AddAnimation("WalkLeft", "assets/Idle.png", sf::Vector2i(7, 1), true);
        obstacle->currentAnimation = obstacle->Animations["WalkLeft"];
        obstacle->SetCollisionShape(); // Ensure collision shape is set
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
        Actors["player"]->CheckCollision(Actors["obstacle"]); // Check for collision with obstacle

        Actors["obstacle"]->Update();
        Actors["obstacle"]->currentAnimation->playAnimation(deltaTime);

        // Clear, render, and display the updated game window
        window.clear();
        Actors["player"]->Render(&window);
        Actors["obstacle"]->Render(&window);
        window.display();
    }

    // Handle player movement based on signals
    void HandleMovement(float deltaTime) {
    // Reset velocity to 0 at the start of each frame
    velocity.x = 0;
    velocity.y = 0;

    // Move player actor based on signals
    if (signalSystem.HasEmitted("W")) {
        velocity.y -= Actors["player"]->speed.y;
    } else if (signalSystem.HasEmitted("S")) {
        velocity.y += Actors["player"]->speed.y;
    } else if (signalSystem.HasEmitted("A")) {
        velocity.x -= Actors["player"]->speed.x;
        // Flip the player sprite to the left
        Actors["player"]->currentAnimation->getSprite().setScale(-1.f, 1.f);
        Actors["player"]->currentAnimation = Actors["player"]->Animations["Walk"];
    } else if (signalSystem.HasEmitted("D")) {
        velocity.x += Actors["player"]->speed.x;
        // Reset the player sprite to face right (default)
        Actors["player"]->currentAnimation->getSprite().setScale(1.f, 1.f);
        Actors["player"]->currentAnimation = Actors["player"]->Animations["Walk"];
    }

    // If no movement is detected, switch to the Idle animation
    if (velocity.x == 0 && velocity.y == 0) {
        Actors["player"]->currentAnimation = Actors["player"]->Animations["Idle"];
    }

    // Update player position by adding the velocity, scaled by deltaTime
    Actors["player"]->position += velocity * deltaTime;
}


    // Destructor to clean up dynamically allocated memory
    ~AJTO() {
        delete player; // Delete player actor
        delete obstacle; // Delete obstacle actor
    }
};




int main() {

    AJTO ajto;

    ajto.SetUp();
    ajto.GameLoop();

    return 0;
}