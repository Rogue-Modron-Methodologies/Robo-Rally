// Tile Header
// Represents a single square on the board
//


#ifndef TILE_H
#define TILE_H

#include <vector>
#include "TileFeature.h"

enum FLOOR_TILES { ground = 0, pit = 1, repair1 = 2, repair2 = 3, 
					conv1 = 4 , convbr1 = 5, convbl1 = 5, convhr1 = 6, convhl1 = 6, convt1 = 7, 
					conv2 = 8, convbr2 = 9, convbl2 = 9, convhr2 = 10, convhl2 = 10, convt2 = 11,
					gearClock = 12, gearAnti = 13 };



class Tile : public Object {

	std::vector<TileFeature *> features;
	std::string tileType;
	int qty;


public:
	Tile(std::string tileInformation, std::string spriteSheetFilename, sf::Vector2f pos, int boardOrientation /*, sf::Vector2f sPos, sf::Vector2f sSize = TILE_SOURCE_SIZE*/)    //commented out because i will find sPos through parsing etc
		: Object(spriteSheetFilename, pos, sf::Vector2i(0, 0), TILE_SOURCE_SIZE) {
		
		setPosition(pos);
		setOrigin();

		loadTile(tileInformation, pos, boardOrientation, spriteSheetFilename);
	};   //sf::Vector2f(0,0) is passing a (0,0) to the object constructor, needs to be replaced with sPos (source position)

	~Tile() { unloadTile(); };

	void loadTile(std::string tileInformation, sf::Vector2f pos, int boardOrientation, std::string spriteSheetFilename);
	void unloadTile();

	void drawTile(sf::RenderWindow &window);			//remember tile is an Object and Object already has a draw

	void drawDebugTile();

	void printTile();					//print private member variables

};

#endif // TILE_H