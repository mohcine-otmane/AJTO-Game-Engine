#include "include/Animation.hpp"
#include <iostream>

Animation::Animation(std::string animationName, sf::Vector2i numberFrames, bool loopAnimation)
    : AnimationName(animationName), NumberFrames(numberFrames), LoopAnimation(loopAnimation), currentFrame(0), elapsedTime(0.0f) {}

bool Animation::setSprite(const std::string& spritePath) {
    // To avoid memory problems we use try-catch
    try {
        if (!AnimationTexture.loadFromFile(spritePath)) {
            throw std::runtime_error("Failed to load texture from file: " + spritePath);
        }

        AnimationSprite.setTexture(AnimationTexture); // once the texture is loaded bide it to the sprite.
        return true;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

}

void Animation::setFrames(bool reversed) {
    sf::Vector2u textureSize = AnimationTexture.getSize();
    sf::Vector2i frameSize(textureSize.x / NumberFrames.x, textureSize.y / NumberFrames.y);

    std::vector<Frame> tempFrames; // Temporary vector to hold frames before reversing

    for (int i = 0; i < NumberFrames.x; ++i) {
        for (int j = 0; j < NumberFrames.y; ++j) {
            Frame frame;
            frame.rect = sf::IntRect(i * frameSize.x, j * frameSize.y, frameSize.x, frameSize.y);
            frame.duration = 0.08f;
            tempFrames.push_back(frame);
        }
    }

    if (reversed) {
        std::reverse(tempFrames.begin(), tempFrames.end());
    }

    VecFrames = tempFrames; // Copy the frames into VecFrames
}


// To keep the frame rate consistant from time to time and from machine to machine we use deltaTime.
// deltaTime is the time deference between two refreshes
bool Animation::playAnimation(float deltaTime) {
    elapsedTime += deltaTime; // deltaTime will be the engine's time unit

    // When the frame duration is elapsed switch to the next frame.
    if (elapsedTime >= VecFrames[currentFrame].duration) {
        elapsedTime = 0.0f; // Reset the time
        currentFrame++; // Switch to the next frame

        // When the last frame is reached, if the animation should be looped return to frame 0, else stop the animation.
        if (currentFrame >= VecFrames.size()) {
            if (LoopAnimation)
                currentFrame = 0;
            else
                return false;
        }

        // Set the current frame shape to the main sprite
        AnimationSprite.setTextureRect(VecFrames[currentFrame].rect);
    }

    return true;
}

Animation::~Animation() {}
