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
	int orientation;
	sf::Vector2i pos;
public:
	Board(std::string filename, sf::Vector2i pos, int orientation) {
		this->name = filename;
		this->orientation = orientation;
		this->pos = pos;
	};
	void drawBoard() {
		std::cout << "Board: ";
		std::cout << name << " " << pos.x << "," << pos.y << " " << orientation << std::endl;
	}

};

#endif // BOARD_H




