#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Actor.hpp"
#include "include/InputManager.hpp"
#include "include/Signals.hpp"
#include "include/Game.hpp"



class AJTO : public Game {

public:
    sf::Vector2f velocity = sf::Vector2f(0, 0);  // Velocity for movement

    // Actor needs to persist, so define it as a member of the class
    Actor* player;
    Actor* obstacle;

    // Set up the game window and initialize actors
    void SetUp() override {
        this->window.create(sf::VideoMode(800, 600), "AJTO Game Engine");

        // Create player actor dynamically so it persists beyond SetUp() method
        player = new Actor(sf::Vector2f(100.f, 100.f), sf::Vector2f(10.f, 10.f));

        // Add "WalkLeft" animation and set its sprite
        player->AddAnimation("WalkLeft", sf::Vector2i(8, 1), true);
        if (!player->Animations["WalkLeft"]->setSprite("assets/WalkLeft.png")) {
            std::cout << "Sprite Not Set" << std::endl;
        } else {
            player->currentAnimation = player->Animations["WalkLeft"];
            player->Animations["WalkLeft"]->setFrames(true);  // Enable animation frames
        }

        // Add "WalkRight" animation and set its sprite
        player->AddAnimation("WalkRight", sf::Vector2i(8, 1), true);
        if (!player->Animations["WalkRight"]->setSprite("assets/WalkRight.png")) {
            std::cout << "Sprite Not Set" << std::endl;
        } else {
            player->currentAnimation = player->Animations["WalkRight"];
            player->Animations["WalkRight"]->setFrames(false);  // Disable frame mirroring
        }


        // Store actor in the Actors map, using the key "player"
        this->Actors["player"] = player;



        obstacle = new Actor(sf::Vector2f(100.f, 100.f), sf::Vector2f(10.f, 10.f));
        obstacle->AddAnimation("WalkLeft", sf::Vector2i(1, 1), true);
        if (!obstacle->Animations["WalkLeft"]->setSprite("assets/wall.png")) {
            std::cout << "Sprite Not Set" << std::endl;
        } else {
            obstacle->currentAnimation = obstacle->Animations["WalkLeft"];
            obstacle->Animations["WalkLeft"]->setFrames(true);  // Enable animation frames
            obstacle->Animations["WalkLeft"]->getSprite().setScale(0.5f,0.5f);
        }
        this->Actors["obstacle"] = obstacle;

    }

    // Main update loop where events and game logic are handled
    void UpDate(float deltaTime, sf::Event event) override {
        // Handle window events like closing
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Emit signals for key presses using InputManager
            inputManager.OnKeyPressed(&event, &signalSystem);

            // Move player actor based on signals
            if (signalSystem.HasEmitted("MoveUp")) {
                Actors["player"]->position.y -= Actors["player"]->speed.y;
            }
            if (signalSystem.HasEmitted("MoveDown")) {
                Actors["player"]->position.y += Actors["player"]->speed.y;
            }
            if (signalSystem.HasEmitted("MoveLeft")) {
                Actors["player"]->position.x -= Actors["player"]->speed.x;
                Actors["player"]->currentAnimation = Actors["player"]->Animations["WalkLeft"];
            }
            if (signalSystem.HasEmitted("MoveRight")) {
                Actors["player"]->position.x += Actors["player"]->speed.x;
                Actors["player"]->currentAnimation = Actors["player"]->Animations["WalkRight"];
            }
        }

        // Update player actor and play the appropriate animation
        Actors["player"]->Update();
        Actors["player"]->Animations["WalkRight"]->playAnimation(deltaTime);
        Actors["player"]->Animations["WalkLeft"]->playAnimation(deltaTime);

        Actors["player"]->CheckCollision(obstacle);

        // Clear, render and display the updated game window
        window.clear();
        Actors["player"]->Render(&window);
        Actors["obstacle"]->Render(&window);
        window.display();
    }

    // Destructor to clean up dynamically allocated memory
    ~AJTO() {
        delete player;
    }
};




int main() {

    AJTO ajto;

    ajto.SetUp();
    ajto.GameLoop();


    return 0;
}