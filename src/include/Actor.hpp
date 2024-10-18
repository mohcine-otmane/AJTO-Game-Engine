#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "Animation.hpp"

// Actors can be players, none player characters, animated objects...
class Actor {
public:

    Actor(sf::Vector2f position, sf::Vector2f speed);
    

    //Because sometimes actors need not be rendered because they are off screen, we need to be able to render the actor when we like to.
    void Render(sf::RenderWindow* window);
    void Update();

    // Each actor needs animations to come alive in the levels of the game.
    // Each animation has a name, number of frames and a flag to determine whether the animation should loop or not.
    void AddAnimation(const std::string animationName,const std::string& AnimationTexturePath, sf::Vector2i numberFrames, bool loopAnimation);



    void SetCollisionShape();

    void CheckCollision(Actor *actor);

    ~Actor();

/*Public variables*/ //(We should make them accessible by friend functions instead of making them public)
    // We use a map instead of a vector because we need to store Animations by name
    std::map<std::string, Animation*> Animations; // All the animations of the actor are stored in this map  
    Animation* currentAnimation; // The actor has only one animation running at a given time
    sf::Vector2f position; //Position with respect to the window (or with respect of the world origin)
    sf::Vector2f speed;
    sf::Vector2f acceleration;
    sf::RectangleShape* CollisionShape;
    
private:
    
    

    
};

#endif
