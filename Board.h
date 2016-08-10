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
public:
	Board(std::string filename, sf::Vector2f pos) {};

};

#endif // BOARD_H




