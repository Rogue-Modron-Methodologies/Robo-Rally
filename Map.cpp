// Map Implementation File

#include "Map.h"


//*************************************************************
// Opens the file (checks for validity)
// Loops through file and creates 2D Vector of Board Objects
void Map::loadMap(std::string filename, sf::Vector2f pos) {

	std::string fullFilename = MAP_HEADER + filename;
	std::fstream inFile(fullFilename.c_str());
	if (!inFile)
		std::cout << "Error Opening " << filename << "\n\t\tTerminating Program\n", exit(EXIT_FAILURE);

	std::string boardName, tempLine, buffer;
	std::stringstream ssline, ssCell;
	sf::Vector2i boardPos = { 0, 0 }, boardDims = { 0, 0 };
	int orientation = 0, rowDim = 0;
	std::vector<Board> row;
	mapBounds = { 0,0 };

	origin = pos;
	while (std::getline(inFile, tempLine)) {
		if (tempLine.size()) {
			ssline << tempLine;
			while (std::getline(ssline, buffer, ',')) {
				if (buffer.size()) {
					ssCell << buffer;
					ssCell >> boardName;
					ssCell >> boardDims.x;
					ssCell >> boardDims.y;
					ssCell >> orientation;
					row.push_back(Board(boardName, sf::Vector2i((int)pos.x + mapBounds.x * TILE_SOURCE_SIZE.x, (int)pos.y + rowDim * TILE_SOURCE_SIZE.y), boardDims, orientation));
				}
				else { //  Empty Board
					boardDims.x = map[boardPos.x - 1][boardPos.y].getDimensions().x;
					boardDims.y = map[boardPos.x - 1][boardPos.y].getDimensions().y;
					orientation = 0;
					row.push_back(Board(sf::Vector2i((int)pos.x + mapBounds.x * TILE_SOURCE_SIZE.x, (int)pos.y + rowDim * TILE_SOURCE_SIZE.y), boardDims, orientation));  
				}

				if (orientation == up || orientation == down)
					rowDim += boardDims.y;
				else
					rowDim += boardDims.x;
				boardPos.y++;
				ssCell.str("");
				ssCell.clear();
			}

			map.push_back(row);
			if (orientation == up || orientation == down) 
				mapBounds.x += boardDims.x;
			else 
				mapBounds.x += boardDims.y;
			if (mapBounds.y < rowDim)
				mapBounds.y = rowDim;
			rowDim = 0;
			row.clear();
			ssline.str("");
			ssline.clear();
			boardPos.x++;
			boardPos.y = 0;
		}
	}
	inFile.close();
}

//*************************************************************
// Loops through 2D vector and calls draw on each element
// 
void Map::drawMap(sf::RenderWindow &window) {
	for (auto row = map.begin(); row != map.end(); ++row)
		for (auto col = row->begin(); col != row->end(); ++col) 
			col->drawBoard(window);
}

//*************************************************************
// Loops through 2D vector and calls isTargeted on each element
// 
bool Map::mapTargeted(sf::RenderWindow &window) {
	// check for out of map bounds.  Return false 
	for (auto row = map.begin(); row != map.end(); ++row)
		for (auto col = row->begin(); col != row->end(); ++col)
			if (col->boardTargeted(window))
				return true;
		return  false;
}

//*************************************************************
// Debug checking Tile and TileFeature private member variables
// Game, Map and Board have printXxxx() functions to reach printTile() function
void Map::debugDraw(sf::RenderWindow &window) {
	for (auto row = map.begin(); row != map.end(); ++row)
		for (auto col = row->begin(); col != row->end(); ++col)
			if (col->boardTargeted(window))
				col->debugDraw(window);
}

//*************************************************************
// Takes in a map and board position 
// Returns Screen Position associated with map/board position
sf::Vector2f Map::getTilePos(sf::Vector2i mapPos, sf::Vector2i boardPos) {
	sf::Vector2f tilePos = origin;
	if (mapPos.x > (int)map.size() || mapPos.y > (int)map[0].size())
		std::cout << "BAD DATA assigned in getTileLocation Function\n";

	for (int i = 0; i < mapPos.x; ++i) {
		tilePos.y += map[i][mapPos.y].getDimensions().y * TILE_SOURCE_SIZE.y;
	}
	tilePos.y += boardPos.x * TILE_SOURCE_SIZE.y;

	for (int i = 0; i < mapPos.y; ++i) {
		tilePos.x += map[mapPos.x][i].getDimensions().x * TILE_SOURCE_SIZE.x;
	}
	tilePos.x += boardPos.y * TILE_SOURCE_SIZE.x;
	return tilePos;
}

//*************************************************************
// Takes in a screen position 
// Returns map/board position through output parameters
void Map::getCurrentCoordinates(sf::Vector2f rPos, sf::Vector2i &mapPos, sf::Vector2i &boardPos) {
	sf::Vector2f diff = rPos - origin;
	mapPos = boardPos = { 0,0 };
	int i = 0;
	while (diff.x / (map[0][i].getDimensions().y * TILE_SOURCE_SIZE.y) >= 1) {
		diff.x -= map[0][i].getDimensions().y * TILE_SOURCE_SIZE.y;
		mapPos.y++;
		i++;
	}
	boardPos.y = (int)diff.x / TILE_SOURCE_SIZE.y;

	i = 0;
	while (diff.y / (map[i][0].getDimensions().x * TILE_SOURCE_SIZE.x) >= 1) {
		diff.y -= map[i][0].getDimensions().x * TILE_SOURCE_SIZE.x;
		mapPos.x++;
		i++;
	}
	boardPos.x = (int)diff.y / TILE_SOURCE_SIZE.x;
}

bool Map::getDestinationCoordinates(sf::Vector2i curBoard, sf::Vector2i curTile, int direction, int orientation, 
							   sf::Vector2i &desBoard, sf::Vector2i &desTile) {

	desBoard = curBoard;
	desTile = curTile;
	bool coordinatesAvailable = true;

	switch (direction + orientation)
	{
	case up:
		if (desTile.x > 0)
			desTile.x--;
		else if (desBoard.x > 0) {
			desBoard.x--;
			desTile.x = map[desBoard.x][desBoard.y].getDimensions().x - 1;
		}
		else
			coordinatesAvailable = false;
		break;
	case right:
		if (desTile.y < map[desBoard.x][desBoard.y].getDimensions().y - 1)
			desTile.y++;
		else if (desBoard.y < (int)map[desBoard.y].size() - 1) {   //  Errors on larger boards
			desBoard.y++;
			desTile.y = 0;
		}
		else
			coordinatesAvailable = false;
		break;
	case down:
		if (desTile.x < map[desBoard.x][desBoard.y].getDimensions().x - 1)
			desTile.x++;
		else if (desBoard.x <= (int)map[desBoard.x].size() - 1) {  //  Errors on larger boards
			desBoard.x++;
			desTile.x = 0;
		}
		else
			coordinatesAvailable = false;
		break;
	case left:
		if (desTile.y > 0)
			desTile.y--;
		else if (desBoard.y > 0) {
			desBoard.y--;
			desTile.y = map[desBoard.x][desBoard.y].getDimensions().y - 1;
		}
		else
			coordinatesAvailable = false;
		break;
	}
	std::cout << desBoard.x << " " << desBoard.y << " | " << desTile.x << " " << desTile.y << std::endl;
	return coordinatesAvailable;
}
