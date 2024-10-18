#ifndef AJTO_HPP
#define AJTO_HPP



#include <SFML/Window.hpp>
#include <windows.h>

#include "Signals.hpp"
#include "Actor.hpp"



namespace aj {
    void DisplayText(std::string text,sf::Vector2f TextPosition, sf::Font font, sf::RenderWindow* window) {
        sf::Text txt;
        txt.setFont(font);
        txt.setPosition(TextPosition);
        window->draw(txt);
    }

    bool StoreTextures(std::vector<std::string> VecTexturePaths, std::vector<sf::Texture> VecTexures) {
        for(auto texturepath:VecTexturePaths) {
            sf::Texture texture;
            try {
                if (!texture.loadFromFile(texturepath)) {
                    throw std::runtime_error("Failed to load texture from file: " + texturepath);
                }

                VecTexures.push_back(texture);

                return true;
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                return false;
            }
        }
    }

}










#endif