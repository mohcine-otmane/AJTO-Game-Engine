#include <SFML/Graphics.hpp>
#include <vector>
#include "include\Physics.h"
#include "include\Actor.h"
#include <filesystem>
#include <iostream>
#include "include/Level.h"

int main() {

    // Instances

    Actor player(sf::Vector2f(100.f,100.f),sf::Vector2f(0.1f,0.1f),"assets/Run.png",8);
    Level level(10, 10, 32);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Multiple Balls with Collision Detection");


     sf::Clock clock;

    sf::Texture tileTexture;
    if (!tileTexture.loadFromFile("assets/Tileset.png")) {
        return -1;
    }


    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        window.clear(sf::Color::Black);

        player.Move(&event);
        player.Physics();

        float deltaTime = clock.restart().asSeconds();
        player.Update(deltaTime);

        
        level.Grid(window, tileTexture);
        player.Render(&window);


        window.display();
    }

    return 0;
}
