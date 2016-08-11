// Board Implementation File

#include "Board.h"

#define DEFAULTSHEET "resources/images/steel.png"

//*************************************************************
// Opens the file (checks for validity)
// Loops through file and creates 2D Vector of Tile Objects
void Board::loadBoard(std::string filename, sf::Vector2i pos, sf::Vector2i dimensions, int orientation) {

	std::string fullFilename = BOARD_HEADER + filename;
	std::fstream inFile(fullFilename.c_str());
	if (!inFile)
		std::cout << "Error Opening " << filename << "\n\t\tTerminating Program\n", exit(EXIT_FAILURE);

	std::string lineBuffer, cellBuffer;
	std::stringstream ss;
	sf::Vector2i boardPos = { 0, 0 };
	std::vector<Tile> row;

	std::getline(inFile, lineBuffer);
	spriteSheet = SPRITESHEET_HEADER + lineBuffer;
	while (std::getline(inFile, lineBuffer)) {
		ss << lineBuffer;
		while (std::getline(ss, cellBuffer, ',')) {
			row.push_back(Tile(cellBuffer, DEFAULTSHEET, sf::Vector2f((float)pos.x + boardPos.x * TILE_SOURCE_SIZE.x, (float)pos.y + boardPos.y * TILE_SOURCE_SIZE.y), orientation));    //  Will eventualy send spritesheet variable through instead 
			boardPos.y++;
		}
		board.push_back(row);
		row.clear();
		ss.str("");
		ss.clear();
		boardPos.x++;
			boardPos.y = 0;
	}
	inFile.close();
}

//*************************************************************
// Loops through 2D vector and calls drawMap on each element
// 
void Board::drawBoard(sf::RenderWindow &window) {
	int i = 0, j = 0;

	std::cout << "Board: " << name << " Dimensions: " << getDimensions().x << "x" << getDimensions().y
		<< /*" Position: " << pos.x << "," << pos.y <<*/ " Orientation: " << orientation << std::endl;
	for (auto row = board.begin(); row != board.end(); ++row)
	{
		for (auto col = row->begin(); col != row->end(); ++col) {
			std::cout << "Tile: " << i << "," << j << " \n";
			col->draw(window);
			j++;
		}
		j = 0;
		i++;
	}
}