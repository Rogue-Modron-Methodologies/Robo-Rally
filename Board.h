//Board header
//two dimensional vector of tiles 
//components used to form map


#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "Tile.h"

const std::string BOARD_HEADER = "resources/boards/";
const std::string SPRITESHEET_HEADER = "resources/images/";

class Board {
	std::vector<std::vector<Tile>> board;
	std::string name;
	std::string spriteSheet;
	sf::Vector2i dimensions;
	int orientation;
public:
	Board(sf::Vector2i pos, sf::Vector2i dimensions, int orientation) {
		this->orientation = orientation;
		this->dimensions = dimensions;
	};
	Board(std::string filename, sf::Vector2i pos, sf::Vector2i dimensions, int orientation) {
		this->name = filename;
		this->orientation = orientation;
		this->dimensions = dimensions;
		loadBoard(filename, pos, dimensions, orientation);
	};
	void loadBoard(std::string filename, sf::Vector2i pos, sf::Vector2i dimensions, int orientation);
	void drawBoard(sf::RenderWindow &window);
	int getOrientation() { return orientation; }
	sf::Vector2i getDimensions() { 	return dimensions; }
};

#endif // BOARD_H




