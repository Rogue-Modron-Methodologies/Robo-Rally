//Board header
//two dimensional vector of tiles 
//components used to form map


#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "Tile.h"

class Board {
	std::vector<std::vector<Tile>> board;
	std::string name;
	std::string spriteSheet;
	int orientation;
	sf::Vector2i pos;
	sf::Vector2i dimensions;
public:
	Board(sf::Vector2i pos, sf::Vector2i dimensions, int orientation) {
		this->orientation = orientation;
		this->dimensions = dimensions;
		this->pos = pos;
	};
	Board(std::string filename, sf::Vector2i pos, sf::Vector2i dimensions, int orientation) {
		this->name = filename;
		this->orientation = orientation;
		this->dimensions = dimensions;
		this->pos = pos;
	};
	void Board::loadBoard(std::string filename, sf::Vector2f pos);
	void drawBoard(/*sf::RenderWindow &window*/);
	int getOrientation() { return orientation; }
	sf::Vector2i getDimensions() {
		//return orientation == up || orientation == down ? dimensions : sf::Vector2i(dimensions.y, dimensions.x);
		return dimensions;
	}
};

#endif // BOARD_H




