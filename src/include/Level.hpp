#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>

struct Tile
{
    sf::Vector2f TileSize;
    sf::Texture TileTexture;
};




class Level {
public:
    Level(int width, int height, int tileSize);
    ~Level();

private:
    int id;
    int width; 
    int height;    
    int tileSize; 

    std::vector<Tile> VecTiles;
};

#endif
