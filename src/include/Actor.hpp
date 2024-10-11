#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include <string>

class Actor {
public:
    Actor(sf::Vector2f position, sf::Vector2f speed, std::string TexturePath, int numberOfFrames);
    
    void MoveTo(float x, float y);
    void Move(sf::Event* event);
    void Physics();
    void Render(sf::RenderWindow* window);
    void Update(float deltaTime);

    ~Actor();

private:
    sf::Vector2f position;
    sf::Vector2f speed;
    sf::RectangleShape DefaultShape;
    sf::Texture texture;
    sf::Sprite Sprite;

    int numberOfFrames;       
    int currentFrame;         
    float animationSpeed;     
    float elapsedTime;        
    bool gravity = false;    
};

#endif
