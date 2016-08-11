// Map header  
// Two Dimensional Vector of Boards
// Encompasses entire "play area" for robots 

#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <iostream>
#include "Board.h"


class Map {
	std::vector<std::vector<Board>> map;

public:
	Map(std::string filename, sf::Vector2f pos) { loadMap(filename, pos); }
	~Map() { unloadMap(); }
	void drawMap(/*sf::RenderWindow &window*/);
private:
	void loadMap(std::string filename, sf::Vector2f pos);
	void unloadMap() { map.clear(); }
};

#endif // MAP_H