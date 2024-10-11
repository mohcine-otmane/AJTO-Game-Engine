#include "include\Level.hpp"

Level::Level(int width, int height, int tileSize)
    : width(width), height(height), tileSize(tileSize) {}

void Level::Grid(sf::RenderWindow& window, const sf::Texture& tileTexture) {
    tiles.clear();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            sf::Sprite tile;
            tile.setTexture(tileTexture);
            tile.setPosition(x * tileSize, y * tileSize);
            tiles.push_back(tile);
        }
    }

    for (const auto& tile : tiles) {
        window.draw(tile);
    }
}

Level::~Level() {}