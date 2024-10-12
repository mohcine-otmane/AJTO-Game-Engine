/*--- The Level class handles levels in the game, each level has (Tile map, Collision map, Physics map, Level rules...) ---*/
/*--------------------- Ignore it for now ---------------------*/


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
