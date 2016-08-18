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