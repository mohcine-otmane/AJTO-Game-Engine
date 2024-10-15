#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Actor.hpp"
#include "include/InputManager.hpp"
#include "include/Signals.hpp"
#include "include/Game.hpp"



class AJTO : public Game {
public:
    sf::Vector2f velocity = sf::Vector2f(0, 0); // Velocity for movement
    Actor* player; // Player actor
    Actor* obstacle; // Obstacle actor

    // Set up the game window and initialize actors
    void SetUp() override {
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
        player->AddAnimation("WalkLeft", sf::Vector2i(10, 1), true);
        if (!player->Animations["WalkLeft"]->setSprite("assets/WalkLeft.png")) {
            std::cout << "Player WalkLeft Sprite Not Set" << std::endl;
        } else {
            player->Animations["WalkLeft"]->setFrames(true);
        }

        player->AddAnimation("WalkRight", sf::Vector2i(10, 1), true);
        if (!player->Animations["WalkRight"]->setSprite("assets/WalkRight.png")) {
            std::cout << "Player WalkRight Sprite Not Set" << std::endl;
        } else {
            player->Animations["WalkRight"]->setFrames(false);
        }

        player->AddAnimation("Idle", sf::Vector2i(7, 1), true);
        if (!player->Animations["Idle"]->setSprite("assets/Idle.png")) {
            std::cout << "Player Idle Sprite Not Set" << std::endl;
        } else {
            player->currentAnimation = player->Animations["Idle"];
            player->Animations["Idle"]->setFrames(false);
        }
        
        player->SetCollisionShape(); // Ensure collision shape is set
    }

    // Initialize obstacle settings
    void InitializeObstacle(Actor* obstacle) {
        obstacle->AddAnimation("WalkLeft", sf::Vector2i(7, 1), true);
        if (!obstacle->Animations["WalkLeft"]->setSprite("assets/Idle.png")) {
            std::cout << "Obstacle Sprite Not Set" << std::endl;
        } else {
            obstacle->currentAnimation = obstacle->Animations["WalkLeft"];
            obstacle->Animations["WalkLeft"]->setFrames(true);
            // obstacle->Animations["WalkLeft"]->getSprite().setScale(0.5f, 0.5f);
        }
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
            HandleMovement(); // Move player based on signals
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
    void HandleMovement() {
        // Move player actor based on signals
        if (signalSystem.HasEmitted("W")) {
            Actors["player"]->position.y -= Actors["player"]->speed.y;
        }else
        if (signalSystem.HasEmitted("S")) {
            Actors["player"]->position.y += Actors["player"]->speed.y;
        }else
        if (signalSystem.HasEmitted("A")) {
            Actors["player"]->position.x -= Actors["player"]->speed.x;
            Actors["player"]->currentAnimation = Actors["player"]->Animations["WalkLeft"];
        }else
        if (signalSystem.HasEmitted("D")) {
            Actors["player"]->position.x += Actors["player"]->speed.x;
            Actors["player"]->currentAnimation = Actors["player"]->Animations["WalkRight"];
        }
        else {
            // Actors["player"]->currentAnimation = Actors["player"]->Animations["Idle"];
        }
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