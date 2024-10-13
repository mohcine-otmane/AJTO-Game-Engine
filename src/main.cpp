#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Actor.hpp"
#include "include/InputManager.hpp"
#include "include/Signals.hpp"

int main() {
    sf::Clock clock; // Make a clock to be able to compute deltaTime

    // The render window is stage on which everything is displayed
    sf::RenderWindow window(sf::VideoMode(800, 600), "AJTO Game Engine");

    Actor actor(sf::Vector2f(100.f, 100.f), sf::Vector2f(10.f, 10.f));

    // We add a "Run" animation, this animation is still empty => we need to set the animation sprite...
    actor.AddAnimation("Run", sf::Vector2i(8, 1), true);
    
    // Setting sprite for the "Run" animation
    if (!actor.Animations["Run"]->setSprite("assets/Run.png")) {
        std::cout << "Sprite Not Set" << std::endl;
    } else {
        actor.currentAnimation = actor.Animations["Run"];
        actor.Animations["Run"]->setFrames();
    }

    InputManager inputManager;  // Input manager handles key presses
    Signals signalSystem;       // Signal system to emit key press signals
    sf::Vector2f velocity(0.f, 0.f);

    // This is the main game loop
    while (window.isOpen()) {
        sf::Event event;

        // Any event that happens in the game is handled in this loop
        while (window.pollEvent(event)) {
            // When the X button is pressed, close the window
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Emit signals based on key presses
            inputManager.OnKeyPressed(&event, &signalSystem);
        }

        float deltaTime = clock.restart().asSeconds();

        // Reset the actor's velocity for this frame
        

        // Check if signals for movement are emitted and update velocity accordingly
        if (signalSystem.HasEmitted("MoveUp")) {
            actor.position.y -= actor.speed.y;  // Move up
        }
        if (signalSystem.HasEmitted("MoveDown")) {
            actor.position.y += actor.speed.y;  // Move down
        }
        if (signalSystem.HasEmitted("MoveLeft")) {
            actor.position.x -= actor.speed.x;  // Move left
        }
        if (signalSystem.HasEmitted("MoveRight")) {
            actor.position.x += actor.speed.x;  // Move right
        }

        // Debugging output for velocity
        std::cout << "Velocity: (" << velocity.x << ", " << velocity.y << ")" << std::endl;

        // Update actor's position based on velocity and deltaTime
        actor.position += velocity * deltaTime;

        // Debugging output for position
        std::cout << "Actor Position: (" << actor.position.x << ", " << actor.position.y << ")" << std::endl;

        actor.Update(deltaTime);  // Update actor state such as position, health, animations
        actor.Animations["Run"]->playAnimation(deltaTime);  // Play the "Run" animation

        window.clear();  // Remove everything previously drawn unto the window
        actor.Render(&window);  // Render the actor (the window is passed by reference)
        window.display();  // Display the finished frame from the buffer (frame buffer might change later)
    }

    return 0;
}
