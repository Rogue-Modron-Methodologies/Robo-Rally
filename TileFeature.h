// TileFeature header
// features of single tile
//

#ifndef TILEFEATURE_H
#define TILEFEATURE_H

#include <string>
#include "Object.h"

const sf::Vector2f TILE_SOURCE_SIZE = { 150, 150 };

class TileFeature : public Object  {
	std::string featureName;
	int qty;
	bool blockLOS;
	bool occupies;
	bool damages;
	bool moveRobot;

public:
	TileFeature(std::string filename, sf::Vector2f pos, sf::Vector2f sPos, sf::Vector2f sSize = TILE_SOURCE_SIZE) 
		: Object(filename, pos, sPos, sSize) {};

};


#endif // TILEFEATURE_H
