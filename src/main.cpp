#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Actor.hpp"
#include "include/InputManager.hpp"
#include "include/Signals.hpp"
#include "include/Game.hpp"



class AJTO : public Game {

public:
    // sf::RenderWindow window;
    
    sf::Vector2f velocity = sf::Vector2f(0,0);

    void SetUp() override {
        this->window.create(sf::VideoMode(800, 600), "AJTO Game Engine"); // The render window is stage on which everything is displayed

        Actor actor(sf::Vector2f(100.f, 100.f), sf::Vector2f(10.f, 10.f));
        actor.AddAnimation("WalkLeft", sf::Vector2i(8, 1), true); // We add a "Run" animation, this animation is still empty => we need to set the animation sprite...
        
        // Setting sprite for the "Run" animation
        if (!actor.Animations["WalkLeft"]->setSprite("assets/WalkLeft.png")) {
            std::cout << "Sprite Not Set" << std::endl;
        } else {
            actor.currentAnimation = actor.Animations["WalkLeft"];
            actor.Animations["WalkLeft"]->setFrames(true);
        }

        actor.AddAnimation("WalkRight", sf::Vector2i(8, 1), true);


        // Setting sprite for the "Walk" animation
        if (!actor.Animations["WalkRight"]->setSprite("assets/WalkRight.png")) {
            std::cout << "Sprite Not Set" << std::endl;
        } else {
            actor.currentAnimation = actor.Animations["WalkRight"];
            actor.Animations["WalkRight"]->setFrames(false);
        }
        this->Actors["player"] = &actor;
    }

    void UpDate(float deltaTime, sf::Event event) override {
            
            // Any event that happens in the game is handled in this loop
            while (window.pollEvent(event)) {
                // When the X button is pressed, close the window
                if (event.type == sf::Event::Closed)
                    window.close();
                
                 // Emit signals based on key presses
                inputManager.OnKeyPressed(&event, &signalSystem);
            }
            // Check if signals for movement are emitted and update the position accordingly
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

            // Update actor's position based on velocity and deltaTime
            // Actors["player"]->position += velocity * deltaTime; // There is a strange bug here (When this line is commented out the window crashes)


            Actors["player"]->Update();  // Update actor state such as position, health, animations
            Actors["player"]->Animations["WalkRight"]->playAnimation(deltaTime);  // Play the "Run" animation
            Actors["player"]->Animations["WalkLeft"]->playAnimation(deltaTime);  // Play the "Walk" animation

            window.clear();  // Remove everything previously drawn unto the window
            Actors["player"]->Render(&window);  // Render the actor (the window is passed by reference)
            window.display();  // Display the finished frame from the buffer (frame buffer might change later)

        
    }

};


int main() {

    AJTO ajto;

    ajto.SetUp();
    ajto.GameLoop();


    return 0;
}