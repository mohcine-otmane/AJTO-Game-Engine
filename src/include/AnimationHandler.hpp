#ifndef ANIMATIONHANDLER_H
#define ANIMATIONHANDLER_H

#include<vector>
#include <SFML/Graphics.hpp>


struct Frame
{
    int FPS = 60;
    sf::Sprite* sprite;
};


class AnimationHandler
{

public:
    AnimationHandler(/* args */);
    bool SelectAnimation(std::string AnimationName);
    ~AnimationHandler();



private:
    std::vector<Frame*> VecFrames;
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