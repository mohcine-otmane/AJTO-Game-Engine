#include "include/Animation.hpp"

Animation::Animation(std::string AnimationName, sf::Sprite* AnimationSprite, sf::Vector2i NumberFrames, bool LoopAnimation)
    : AnimationName(AnimationName), AnimationSprite(AnimationSprite), NumberFrames(NumberFrames), LoopAnimation(LoopAnimation), currentFrame(0), elapsedTime(0.0f) {

    }


bool Animation::getSprite() {
    
}




void Animation::getFrames() {
    sf::Vector2u textureSize = AnimationSprite->getTexture()->getSize();
    sf::Vector2i frameSize(textureSize.x / NumberFrames.x, textureSize.y / NumberFrames.y);

    for (int i = 0; i < NumberFrames.x; ++i) {
        for (int j = 0; j < NumberFrames.y; ++j) {
            Frame frame;
            frame.rect = sf::IntRect(i * frameSize.x, j * frameSize.y, frameSize.x, frameSize.y);
            frame.duration = 0.1f;  // set default frame duration (can be changed later)
            frame.sprite = AnimationSprite;
            VecFrames.push_back(frame);
        }
    }
}

bool Animation::PlayAnimation(float deltaTime) {
    elapsedTime += deltaTime;

    if (elapsedTime >= VecFrames[currentFrame].duration) {
        elapsedTime = 0.0f;
        currentFrame++;

        if (currentFrame >= VecFrames.size()) {
            if (LoopAnimation)
                currentFrame = 0;
            else
                return false;
        }
        AnimationSprite->setTextureRect(VecFrames[currentFrame].rect);
    }
    return true;
}

Animation::~Animation() {}
