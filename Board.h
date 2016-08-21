//Board header
//two dimensional vector of tiles 
//components used to form map


#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "Tile.h"

const std::string BOARD_HEADER = "resources/boards/";

class Board {
	std::vector<std::vector<Tile *>> board;
	std::string name;
	std::string spriteSheet;
	sf::Vector2i dimensions;
	sf::Vector2i pos;
	int orientation;
public:
	Board(sf::Vector2i pos, sf::Vector2i dimensions, int orientation);
	Board(std::string filename, sf::Vector2i pos, sf::Vector2i dimensions, int orientation);
	void loadBoard(std::string filename, sf::Vector2i pos, sf::Vector2i dimensions, int orientation);
	void unloadBoard();
	void drawBoard(sf::RenderWindow &window);
	int getOrientation() { return orientation; }
	sf::Vector2i getDimensions() { 	return dimensions; }
	bool boardTargeted(sf::RenderWindow &window);
	sf::Vector2f convertCoord(sf::RenderWindow &gWindow);
	void debugDraw(sf::RenderWindow &window);
	void moveRobotToBoard(Robot *robot, sf::Vector2i tileNum) {
		board[tileNum.x][tileNum.y]->placeRobot(robot);
	}
	void removeRobotFromBoard(sf::Vector2i tileNum) {
		board[tileNum.x][tileNum.y]->removeRobot();
	}
};

#endif // BOARD_H




