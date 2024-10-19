#ifndef AJTO_HPP
#define AJTO_HPP



#include <SFML/Window.hpp>
#include <windows.h>

#include "Signals.hpp"
#include "Actor.hpp"



namespace aj {
    void DisplayText(std::string text,sf::Vector2f TextPosition, sf::Font* font, sf::RenderWindow* window) {
        sf::Text txt;
        txt.setFont(*font);
        txt.setPosition(TextPosition);
        txt.setColor(sf::Color(255,255,255));
        window->draw(txt);
    }

    bool StoreTextures(std::vector<std::string>* VecTexturePaths, std::vector<sf::Texture>* VecTextures) {
        for (const auto& texturePath : *VecTexturePaths) {
            sf::Texture texture;
            try {
                if (!texture.loadFromFile(texturePath)) {
                    throw std::runtime_error("Failed to load texture from file: " + texturePath);
                }
                VecTextures->push_back(texture);
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                return false; // Return false only if a texture fails to load
            }
        }
        return true; // Return true after all textures are loaded
    }


}










#endif