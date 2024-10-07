#include <SFML/Graphics.hpp>
#include <vector>
#include "include\Ball.h"

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Multiple Balls with Collision Detection");

    // Create multiple balls
    std::vector<Ball> balls;

    // Add balls to the vector
    balls.emplace_back(20.f, sf::Color::Green, sf::Vector2f(100.f, 100.f), sf::Vector2f(0.2f, 0.2f));
    balls.emplace_back(30.f, sf::Color::Blue, sf::Vector2f(300.f, 200.f), sf::Vector2f(0.15f, 0.25f));
    balls.emplace_back(25.f, sf::Color::Red, sf::Vector2f(500.f, 400.f), sf::Vector2f(0.25f, 0.15f));
    balls.emplace_back(20.f, sf::Color::Yellow, sf::Vector2f(150.f, 150.f), sf::Vector2f(0.2f, -0.2f));

    // Game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update each ball
        for (auto& ball : balls) {
            ball.move();
            ball.checkCollision(window);
        }

        // Check for collisions between balls
        for (size_t i = 0; i < balls.size(); ++i) {
            for (size_t j = i + 1; j < balls.size(); ++j) {
                if (balls[i].checkCollisionWithBall(balls[j])) {
                    balls[i].resolveCollision(balls[j]);
                }
            }
        }

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Draw each ball
        for (const auto& ball : balls) {
            ball.draw(window);
        }

        // Display the contents of the window
        window.display();
    }

    return 0;
}
