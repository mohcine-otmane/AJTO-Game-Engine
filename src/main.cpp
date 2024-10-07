#include <SFML/Graphics.hpp>
#include <vector>
#include "include\Physics.h"
#include "include\Actor.h"

int main() {

    // Instances

    Actor player(sf::Vector2f(100.f,100.f),sf::Vector2f(1.f,1.f));

    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Multiple Balls with Collision Detection");

    // Game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        

        // Clear the window with black color
        window.clear(sf::Color::Black);

        player.Render(&window);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
