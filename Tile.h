// Tile Header
// Represents a single square on the board
//


#ifndef TILE_H
#define TILE_H

#include <vector>
#include "TileFeature.h"

class Tile : public Object {
	
	std::vector<TileFeature> features;

public:
	Tile(std::string filename, sf::Vector2f pos, sf::Vector2f sPos, sf::Vector2f sSize = TILE_SOURCE_SIZE)
		: Object(filename, pos, sPos, sSize) {};
};

#endif // TILE_H