#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/Graphics.hpp>

struct Frame {
    float duration;
    sf::IntRect rect;  // It selects the frame we want to separate
    sf::Sprite* sprite;
};

class Animation {
public:
    Animation(std::string AnimationName, sf::Sprite* AnimationSprite, sf::Vector2i NumberFrames, bool LoopAnimation = true);
    bool getSprite();
    void getFrames();
    bool PlayAnimation(float deltaTime);
    ~Animation();

private:
    std::string AnimationName;
    sf::Sprite* AnimationSprite;
    sf::Vector2i NumberFrames;
    std::vector<Frame> VecFrames;
    bool LoopAnimation;
    int currentFrame;
    float elapsedTime;
};

#endif
