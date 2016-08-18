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

public:
	Map(std::string filename, sf::Vector2f pos) { loadMap(filename, pos); }
	~Map() { unloadMap(); }
	void drawMap(sf::RenderWindow &window);
	void loadMap(std::string filename, sf::Vector2f pos);
	void unloadMap() { map.clear(); }
	bool mapTargeted(sf::RenderWindow &window);

	void printMap();
};

#endif // MAP_H