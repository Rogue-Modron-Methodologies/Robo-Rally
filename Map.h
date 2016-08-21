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
	void moveRobotToMap(Robot *robot, sf::Vector2i boardNum, sf::Vector2i tileNum) {
		map[boardNum.x][boardNum.y].moveRobotToBoard(robot, tileNum);
	}

	sf::Vector2f getTilePos(sf::Vector2i mapPos, sf::Vector2i boardPos) {
		sf::Vector2f tilePos = origin;
		if (mapPos.x > (int)map.size() || mapPos.y > (int)map[0].size())
			std::cout << "BAD DATA assigned in getTileLocation Function\n";
		for (int i = 0; i < mapPos.x; ++i) {
			tilePos.x += map[i][mapPos.y].getDimensions().x * TILE_SOURCE_SIZE.x;
		}
		tilePos.x += boardPos.x * TILE_SOURCE_SIZE.x;

		for (int i = 0; i < mapPos.y; ++i) {
			tilePos.y += map[mapPos.x][i].getDimensions().y * TILE_SOURCE_SIZE.y;
		}
		tilePos.y += boardPos.y * TILE_SOURCE_SIZE.y;
		return tilePos;
	}
};

#endif // MAP_H