// Map header  
// Two Dimensional Vector of Boards
// Encompasses entire "play area" for robots 

#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <iostream>
#include "Board.h"

const std::string MAP_HEADER = "resources/maps/";

class Map {
	std::vector<std::vector<Board>> map;
	sf::Vector2i mapBounds;
	sf::Vector2f origin;

public:
	Map(std::string filename, sf::Vector2f pos) { loadMap(filename, pos); }
	~Map() { unloadMap(); }
	void drawMap(sf::RenderWindow &window);
	void loadMap(std::string filename, sf::Vector2f pos);
	void unloadMap() { map.clear(); }
	bool mapTargeted(sf::RenderWindow &window);
	void debugDraw(sf::RenderWindow &window);
	sf::Vector2f getTilePos(sf::Vector2i mapPos, sf::Vector2i boardPos);
	void getCurrentCoordinates(sf::Vector2f rPos, sf::Vector2i &mapPos, sf::Vector2i &boardPos);
	bool getDestinationCoordinates(sf::Vector2i curBoard, sf::Vector2i curTile, 
			int direction, int orientation, sf::Vector2i &desBoard, sf::Vector2i &desTile);
	void addRobotToPlay(const Robot &robot, sf::Vector2i boardNum, sf::Vector2i tileNum) {
		map[boardNum.x][boardNum.y].addRobotToPlay(robot, tileNum);
	}
	void repositionRobot(const Robot &robot, sf::Vector2i desBoard, sf::Vector2i desTile, sf::Vector2i curBoard, sf::Vector2i curTile) {
		map[desBoard.x][desBoard.y].addRobotToPlay(robot, desTile);
		map[curBoard.x][curBoard.y].removeRobotFromPlay(curTile);
	}
	void removeRobotFromPlay(sf::Vector2i boardNum, sf::Vector2i tileNum) {
		map[boardNum.x][boardNum.y].removeRobotFromPlay(tileNum);
	}
	const Tile *getTile(sf::Vector2i boardPos, sf::Vector2i tilePos) { return map[boardPos.x][boardPos.y].getTile(tilePos); }
	
};

#endif // MAP_H