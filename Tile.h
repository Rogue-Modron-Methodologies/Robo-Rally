// Tile Header
// Represents a single square on the board
//


#ifndef TILE_H
#define TILE_H

#include <vector>
#include "TileFeature.h"

class Tile {
	
	std::vector<TileFeature> features;

public:
	Tile(std::string filename) {};
};

#endif // TILE_H