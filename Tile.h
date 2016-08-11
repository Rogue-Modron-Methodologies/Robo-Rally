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
	Tile(std::string tileInformation, std::string spriteSheetFilename, sf::Vector2f pos, int orientation /*, sf::Vector2f sPos, sf::Vector2f sSize = TILE_SOURCE_SIZE*/)    //commented out because i will find sPos through parsing etc
		: Object(spriteSheetFilename, pos, sf::Vector2i(0, 0), TILE_SOURCE_SIZE) {};   //sf::Vector2f(0,0) is passing a (0,0) to the object constructor, needs to be replaced with sPos (source position)
	/*void drawTile(sf::RenderWindow &window) { }*/
};

#endif // TILE_H