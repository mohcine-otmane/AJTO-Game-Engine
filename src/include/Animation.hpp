/*--- Only actors are animated thus the Animation class is accessed only by the Actor class---*/
/*--- An actor may have multiple animations but only one animation (currentAnimation) runs at a time ---*/

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// The Frame struct is used to store all the frames of the animation sprite in a vector
struct Frame {
    sf::IntRect rect; // This is a square to select each frame from the animation sprite
    float duration; // Each frame has a duration, we could make all frames have the same duration but we need to have more control.
};

class Animation {
public:

    // I guess all of the arguments are self evident

    ~Animation(); // Will be used at the end to free allocated memory.

    Animation(std::string animationName, const std::string &AnimationTexturePath, sf::Vector2i numberFrames, bool loopAnimation);

    // Each animation has an animation sprite, this function loads the sprite image from its path.
    bool setSprite(const std::string& spritePath);

    // Each animation sprite has frames, this function separates the frames and puts them in a vector.
    void setFrames(bool reversed);

    
    
    bool playAnimation(float deltaTime);

    sf::Vector2i getFrameSize() {
        return FrameSize;
    }

    sf::Sprite& getSprite() { return AnimationSprite; } // This is a getter function that we use for debugging

private:
    std::string AnimationName; // Each animation has a unique name, Examples = {AtackAnimation, DeathAnimation, JumpAnimation}
    sf::Texture AnimationTexture; // This is the image that we load.
    sf::Sprite AnimationSprite; // This is the animation sprite. (we use AnimationSprite.setTexture(texture))
    std::vector<Frame> VecFrames; // This is the vector in which we store all the frames of the animation sprite.
    sf::Vector2i NumberFrames; // This is a vector2i (int, int) because the animation sprite might have raw and columns of frames.
    int currentFrame;
    sf::Vector2i FrameSize;
    float elapsedTime;
    bool LoopAnimation = true;
};

#endif
