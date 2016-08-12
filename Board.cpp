// Board Implementation File

#include "Board.h"

#define DEFAULTSHEET "steel.png"

//*************************************************************
// Opens the file (checks for validity)
// Loops through file and creates 2D Vector of Tile Objects
void Board::loadBoard(std::string filename, sf::Vector2i pos, sf::Vector2i dimensions, int orientation) {

	std::string buffer;
	std::string fullFilename = BOARD_HEADER + filename;
	std::fstream inFile(fullFilename.c_str());
	if (!inFile)
		std::cout << "Error Opening " << filename << "\n\t\tTerminating Program\n", exit(EXIT_FAILURE);
	std::stringstream ss;

	int temp;
	std::getline(inFile, spriteSheet);

	switch (orientation)
	{
	case right:
	case left:
		temp = dimensions.y;
		this->dimensions.y = dimensions.x;
		this->dimensions.x = temp;
	case down:
	case up:
		break;
	}

	board.resize(this->dimensions.x);
	for (auto row = board.begin(); row != board.end(); ++row)
		row->resize(this->dimensions.y);

	for (int i = 0; i < this->dimensions.x; ++i) {
		std::getline(inFile, buffer);
		ss << buffer;
		for (int j = 0; j < this->dimensions.y; ++j) {
			std::getline(ss, buffer, ',');
			board[i][j] = new Tile(buffer, DEFAULTSHEET, sf::Vector2f((float)pos.y + j * TILE_SOURCE_SIZE.y, (float)pos.x + i * TILE_SOURCE_SIZE.x), orientation);
			//std::cout << board[i][j]->getPosition().x << "," << board[i][j]->getPosition().y << std::endl;

		}
	}

	inFile.close();
}

//*************************************************************
// Loops through 2D vector and calls draw on each element
// 
void Board::drawBoard(sf::RenderWindow &window) {
	//std::cout << "Board: " << name << " Dimensions: " << getDimensions().x << "x" << getDimensions().y
	//	<< " Position: " << pos.x << "," << pos.y << " Orientation: " << orientation << std::endl;
	if (board.size() == 0) return;
	for (int i = 0; i < dimensions.x; ++i)
		for (int j = 0; j < dimensions.y; ++j)
		{
			//std::cout << "Drawing " << board[i][j]->getPosition().x << "," << board[i][j]->getPosition().y << std::endl;
			board[i][j]->draw(window);
		}

}
