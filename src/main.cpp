#include <SFML/Graphics.hpp>
#include <vector>
#include "include/Animation.hpp"
#include "include/Signals.hpp"

int main() {




    Signals signalSystem;
    signalSystem.Start();

    signalSystem.Emit(2.0f, false, 0, "attack");
    signalSystem.Emit(5.0f, true, 3, "warning");



    sf::RenderWindow window(sf::VideoMode(800, 600), "AJTO Game Engine");

    sf::Texture runTexture;
    if (!runTexture.loadFromFile("assets/Run.png")) {
        return -1;
    }

    sf::Texture walkTexture;
    if (!walkTexture.loadFromFile("assets/Walk.png")) {
        return -1;
    }

    sf::Sprite playerSprite;
    playerSprite.setTexture(runTexture);

    Animation runAnimation("Run", &playerSprite, sf::Vector2i(8, 1), true);
    Animation walkAnimation("Walk", &playerSprite, sf::Vector2i(8, 1), true);

    runAnimation.getFrames();
    walkAnimation.getFrames();

    Animation* currentAnimation = &runAnimation;

    sf::Clock clock;
    float deltaTime;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            currentAnimation = &runAnimation;
            playerSprite.setTexture(runTexture);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            currentAnimation = &walkAnimation;
            playerSprite.setTexture(walkTexture);
        }

        deltaTime = clock.restart().asSeconds();
        currentAnimation->PlayAnimation(deltaTime);

        window.clear(sf::Color::Black);
        window.draw(playerSprite);
        window.display();
    }


    signalSystem.Stop();
    return 0;
}
