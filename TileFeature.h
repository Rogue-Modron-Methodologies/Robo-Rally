// TileFeature header
// features of single tile
//

#ifndef TILEFEATURE_H
#define TILEFEATURE_H

#include <string>
#include "Object.h"

const sf::Vector2i TILE_SOURCE_SIZE = { 50, 50 };

class TileFeature : public Object  {
	std::string featureName;
	int qty;
	bool blockLOS;
	bool occupies;
	bool damages;
	bool moveRobot;

public:
	TileFeature(std::string filename, sf::Vector2f pos, sf::Vector2i sPos, sf::Vector2i sSize = TILE_SOURCE_SIZE) 
		: Object(filename, pos, sPos, sSize) {};

};


#endif // TILEFEATURE_H
