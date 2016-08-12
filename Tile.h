// Tile Header
// Represents a single square on the board
//


#ifndef TILE_H
#define TILE_H

#include <vector>
#include "TileFeature.h"



class Tile : public Object {

	std::vector<TileFeature> features;
	std::string tileInformation, spriteSheetFilename;
	sf::Vector2f pos;
	sf::Vector2f sPos;
	int boardOrientation;

	int colorCodeR, colorCodeG, colorCodeB;

public:
	Tile(std::string tileInformation, std::string spriteSheetFilename, sf::Vector2f pos, int boardOrientation /*, sf::Vector2f sPos, sf::Vector2f sSize = TILE_SOURCE_SIZE*/)    //commented out because i will find sPos through parsing etc
		: Object(spriteSheetFilename, pos, sf::Vector2i(0, 0), TILE_SOURCE_SIZE) {
		this->tileInformation = tileInformation;
		this->spriteSheetFilename = spriteSheetFilename;
		this->pos = pos;
		this->boardOrientation = boardOrientation;

		//loadTile(tileInformation, pos, boardOrientation, colorCodeR, colorCodeG, colorCodeB);
	};   //sf::Vector2f(0,0) is passing a (0,0) to the object constructor, needs to be replaced with sPos (source position)
	/*void drawTile(sf::RenderWindow &window) { }*/  //remember tile is an Object and Object already has a draw

	void loadTile(std::string tileInformation, sf::Vector2f pos, int boardOrientation , int colorCodeR, int colorCodeG, int colorCodeB);
	void unloadTile() {};

};

#endif // TILE_H