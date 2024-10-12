#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Actor.hpp"

int main() {
    sf::Clock clock; // Make a clock to be able to compute deltaTime

    // The render window is stage on which everything is displayed
    sf::RenderWindow window(sf::VideoMode(800, 600), "AJTO Game Engine");

    Actor actor(sf::Vector2f(100.f, 100.f), sf::Vector2f(1.f, 1.f));

    // We add a "Run" animation, this animation is still empty => we need to set the animation sprite...
    actor.AddAnimation("Run", sf::Vector2i(8, 1), true);
    
    

    // Setting sprite for the "Run" animation
    
    if (!actor.Animations["Run"]->setSprite("assets/Run.png")) {
        std::cout << "Sprite Not Set" << std::endl;
    } else {
        actor.currentAnimation = actor.Animations["Run"];
        actor.Animations["Run"]->setFrames();
    }

    

    // This is the main game loop
    while (window.isOpen()) {
        sf::Event event;

        // Any event that happens in the game is handled in this loop
        while (window.pollEvent(event)) {
            // When the X button is pressed close the window
            if (event.type == sf::Event::Closed)
                window.close();
            
            /*Add other events handlers here*/
        }

        float deltaTime = clock.restart().asSeconds();
        
        actor.Update(deltaTime); // Update the actor data (such as position, health, animations...)
        actor.Animations["Run"]->playAnimation(deltaTime); // Play the "Run animation"
        window.clear(); // Remove everything previously drawn unto the window
        actor.Render(&window); // Render the actor, we pass the window by address because we need to access a specific window.
        window.display(); // Display the finished frame from the buffer (We may change the buffer size later)
    }

    return 0;
}

