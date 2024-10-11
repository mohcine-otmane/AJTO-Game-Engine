#ifndef ANIMATION_H
#define ANIMATION_H

#include<vector>
#include <SFML/Graphics.hpp>

struct Frame
{
    float duration;
    sf::Sprite* sprite;
};

struct Animation
{
    std::string AnimationName;
    sf::Sprite* AnimationSprite;
    int NumberFrames;
    std::vector<Frame*> VecFrames;
    bool LoopAnimation = true;
};



class AnimationHandler
{

public:
    AnimationHandler(/* args */);
    bool SelectAnimation(std::string AnimationName);
    ~AnimationHandler();



private:
    
};

AnimationHandler::AnimationHandler(/* args */)
{
}

bool AnimationHandler::SelectAnimation(std::string AnimationName)
{
    return false;
}

AnimationHandler::~AnimationHandler()
{
}












#endif