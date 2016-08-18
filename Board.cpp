// Board Implementation File

#include "Board.h"

//*************************************************************
// Empty Board Constructor
// Has Dimensions, Position, and Orientation
// Vector of Tiles is empty so no tiles
Board::Board(sf::Vector2i pos, sf::Vector2i dimensions, int orientation) {
	this->orientation = orientation;
	this->dimensions = dimensions;
	this->pos = pos;
};

//*************************************************************
// Full Board Constructor
Board::Board(std::string filename, sf::Vector2i pos, sf::Vector2i dimensions, int orientation) {
	this->name = filename;
	this->orientation = orientation;
	this->dimensions = dimensions;
	this->pos = pos;
	loadBoard(filename, pos, dimensions, orientation);
};

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
	std::replace(spriteSheet.begin(), spriteSheet.end(), ',', ' ');

	switch (orientation){
	case left:
	case right:
		temp = dimensions.y;
		this->dimensions.y = dimensions.x;
		this->dimensions.x = temp;
	case up:
	case down:
		break;
	}
	board.resize(this->dimensions.x);
	for (auto row = board.begin(); row != board.end(); ++row)
		row->resize(this->dimensions.y);

	switch (orientation) {
	case up:
		for (int i = 0; i < this->dimensions.x; ++i) {
			std::getline(inFile, buffer);
			ss << buffer;
			for (int j = 0; j < this->dimensions.y; ++j) {
				std::getline(ss, buffer, ',');
				board[i][j] = new Tile(buffer, spriteSheet, sf::Vector2f((float)pos.y + j * TILE_SOURCE_SIZE.y, (float)pos.x + i * TILE_SOURCE_SIZE.x), orientation);
			}
			ss << "";
			ss.clear();
		}
		break;
	case down:
		for (int i = this->dimensions.x - 1; i >= 0; --i) {
			std::getline(inFile, buffer);
			ss << buffer;
			for (int j = this->dimensions.y - 1; j >= 0; --j) {
				std::getline(ss, buffer, ',');
				board[i][j] = new Tile(buffer, spriteSheet, sf::Vector2f((float)pos.y + j * TILE_SOURCE_SIZE.y, (float)pos.x + i * TILE_SOURCE_SIZE.x), orientation);
			}
			ss << "";
			ss.clear();
		}
		break;
	case left:
		for (int j = 0; j < this->dimensions.y; ++j) {
			std::getline(inFile, buffer);
			ss << buffer;
			for (int i = this->dimensions.x - 1; i >= 0; --i) {
				std::getline(ss, buffer, ',');
				board[i][j] = new Tile(buffer, spriteSheet, sf::Vector2f((float)pos.y + j * TILE_SOURCE_SIZE.y, (float)pos.x + i * TILE_SOURCE_SIZE.x), orientation);
			}
			ss << "";
			ss.clear();
		}
		break;
	case right:
		for (int j = this->dimensions.y - 1; j >= 0; --j) {
			std::getline(inFile, buffer);
			ss << buffer;
			for (int i = 0; i < this->dimensions.x; ++i) {
				std::getline(ss, buffer, ',');
				board[i][j] = new Tile(buffer, spriteSheet, sf::Vector2f((float)pos.y + j * TILE_SOURCE_SIZE.y, (float)pos.x + i * TILE_SOURCE_SIZE.x), orientation);
			}
			ss << "";
			ss.clear();
		}
		break;
	}
	inFile.close();
}

//*************************************************************
// Releases dynamically allocated vector of Tiles.
void Board::unloadBoard() {
	if (board.size() == 0) return;
	for (int i = 0; i < dimensions.x; ++i)
		for (int j = 0; j < dimensions.y; ++j)
			delete(board[i][j]);

	for (auto it = board.begin(); it != board.end(); ++it)
		it->clear();
	board.clear();
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
			board[i][j]->drawTile(window);			//to draw features onto tiles
		}

}

//*************************************************************
// Loops through 2D vector and calls isTargeted on each element
// 
bool Board::boardTargeted(sf::RenderWindow &window) {

	if (board.size() == 0) return false;
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	// returns false if click is outside of board dimensions.  Won't bother checking each tile individually.
	//if (worldPos.x < pos.x || worldPos.y < pos.y || 
	//	worldPos.x > pos.x + dimensions.x * TILE_SOURCE_SIZE.x || 
	//	worldPos.y > pos.y + dimensions.y * TILE_SOURCE_SIZE.y)
	//	return false;

	for (int i = 0; i < dimensions.x; ++i)
		for (int j = 0; j < dimensions.y; ++j)
			if (board[i][j]->isTargeted(window))
				return true; 
	return false;
}
