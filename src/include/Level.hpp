#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>

class Level {
public:
    Level(int width, int height, int tileSize);
    void Grid(sf::RenderWindow& window, const sf::Texture& tileTexture);
    ~Level();

private:
    int id;
    int width; 
    int height;    
    int tileSize; 

    std::vector<sf::Sprite> tiles;
};

#endif
