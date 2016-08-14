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
	std::cout << spriteSheet << std::endl;

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

	for (int i = 0; i < this->dimensions.x; ++i) {
		std::getline(inFile, buffer);
		ss << buffer;
		for (int j = 0; j < this->dimensions.y; ++j) {
			std::getline(ss, buffer, ',');
			board[i][j] = new Tile(buffer, spriteSheet, sf::Vector2f((float)pos.y + j * TILE_SOURCE_SIZE.y, (float)pos.x + i * TILE_SOURCE_SIZE.x), orientation);
			//std::cout << board[i][j]->getPosition().x << "," << board[i][j]->getPosition().y << std::endl;
		}
		ss << "";
		ss.clear();
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
		}

}

//
////*************************************************************
//// Opens the file (checks for validity)
//// Loops through file and creates 2D Vector of Tile Objects
//void Board::loadBoard(std::string filename, sf::Vector2i pos, sf::Vector2i dimensions, int orientation) {
//
//
//	std::string lineBuffer, tileBuffer;
//	std::string fullFilename = BOARD_HEADER + filename;
//	std::fstream inFile(fullFilename.c_str());
//	if (!inFile)
//		std::cout << "Error Opening " << filename << "\n\t\tTerminating Program\n", exit(EXIT_FAILURE);
//	std::stringstream ss;
//
//	int /*temp, */tempX, tempY, iX, jY;
//	std::getline(inFile, spriteSheet);
//
//	//begin tempBoard experiment
//
//	//std::vector<std::vector<Tile *>> tempBoard;  // no longer using tempBoard in tempBoard experiment . . . 
//
//	switch (orientation)		//setting temp values for sizing 2d vector and iterators for filling 2d vector in correct order
//	{
//	case up:
//		tempX = dimensions.x;
//		tempY = dimensions.y;
//		iX = jY = 0;
//	case right:
//		tempX = dimensions.y;
//		tempY = dimensions.x;
//		iX = 0;
//		jY = tempY - 1;
//		break;
//	case down:
//		tempX = dimensions.x;
//		tempY = dimensions.y;
//		iX = tempX - 1;
//		jY = tempY - 1;
//		break;
//	case left:
//		tempX = dimensions.y;
//		tempY = dimensions.x;
//		iX = tempX - 1;
//		jY = 0;
//		break;
//	}
//
//
//	//tempBoard.resize(this->dimensions.x);
//
//	//for (auto row = tempBoard.begin(); row != tempBoard.end(); ++row)
//	//	row->resize(this->dimensions.y);
//
//	board.resize(tempX);				//sizing 2d vector to correct orientation
//
//	for (auto row = board.begin(); row != board.end(); ++row)				//sizing 2d vector to correct orientation
//		row->resize(tempY);
//
//
//	for (int i = 0; i < this->dimensions.x; ++i) {
//
//		std::getline(inFile, lineBuffer);
//		ss << lineBuffer;
//
//		for (int j = 0; j < this->dimensions.y; ++j) {
//			std::getline(ss, tileBuffer, ',');
//			//tempBoard[i][j] = new Tile(tileBuffer, DEFAULTSHEET, sf::Vector2f((float)pos.y + j * TILE_SOURCE_SIZE.y, (float)pos.x + i * TILE_SOURCE_SIZE.x), orientation);
//
//			/*
//			switch statement below is used to migrate data from .csv file (with a fixed orientation) to a 2d vector (which is oriented as needed)
//
//			nested for-loop uses i and j to traverse .csv and/or track position in .csv
//
//			iX and iY used to traverse and/or track position in 2d vector
//
//			i started working on calculation/tracking where the tiles should be printed to the screen THIS might be the problem at the moment
//
//			i also might be going out of bounds of the 2d vector, but its possible i fixed that
//
//			*/
//
//			switch (orientation)			//there must be a better way
//			{
//			case up:
//				board[i][j] = new Tile(tileBuffer, DEFAULTSHEET, sf::Vector2f((float)pos.y + j * TILE_SOURCE_SIZE.y, (float)pos.x + i * TILE_SOURCE_SIZE.x), orientation);
//				board[i][j]->setColor(board[i][j]->getType());		//test parcing and logic for base tile type
//				break;
//			case right:
//				board[iX][jY] = new Tile(tileBuffer, DEFAULTSHEET, sf::Vector2f((float)pos.y + jY * TILE_SOURCE_SIZE.y, (float)pos.x + iX * TILE_SOURCE_SIZE.x), orientation);
//				board[iX][jY]->setColor(board[iX][jY]->getType());		//test parcing and logic for base tile type
//				if (iX < tempX - 1)
//					++iX;
//				else
//					iX = 0;
//				if (jY > 0)
//					--jY;
//				else
//					jY = tempY - 1;
//				break;
//			case down:
//				board[iX][jY] = new Tile(tileBuffer, DEFAULTSHEET, sf::Vector2f((float)pos.y + jY * TILE_SOURCE_SIZE.y, (float)pos.x + iX * TILE_SOURCE_SIZE.x), orientation);
//				board[iX][jY]->setColor(board[iX][jY]->getType());		//test parcing and logic for base tile type
//				if (iX > 0)
//					--iX;
//				else
//					iX = tempX - 1;
//				if (jY > 0)
//					--jY;
//				else
//					jY = tempY - 1;
//				break;
//			case left:
//				board[iX][jY] = new Tile(tileBuffer, DEFAULTSHEET, sf::Vector2f((float)pos.y + jY * TILE_SOURCE_SIZE.y, (float)pos.x + iX * TILE_SOURCE_SIZE.x), orientation);
//				board[iX][jY]->setColor(board[iX][jY]->getType());		//test parcing and logic for base tile type
//				if (iX > 0)
//					--iX;
//				else
//					iX = tempX - 1;
//				if (jY < tempY - 1)
//					++jY;
//				else
//					jY = 0;
//				break;
//			}
//
//		}
//	}
//
//
//
//
//	//end tempBoard experiment
//
//	/*  commented to save
//
//	switch (orientation)		//jordan messed with this
//	{
//	case up:
//	case right:
//	temp = dimensions.y;
//	this->dimensions.y = dimensions.x;
//	this->dimensions.x = temp;
//	case down:
//	case left:
//	temp = dimensions.y;
//	this->dimensions.y = dimensions.x;
//	this->dimensions.x = temp;
//	break;
//	}
//
//	board.resize(this->dimensions.x);
//
//	for (auto row = board.begin(); row != board.end(); ++row)
//	row->resize(this->dimensions.y);
//
//	for (int i = 0; i < this->dimensions.x; ++i) {
//
//	std::getline(inFile, lineBuffer);
//	ss << lineBuffer;
//
//	for (int j = 0; j < this->dimensions.y; ++j) {
//	std::getline(ss, tileBuffer, ',');
//	board[i][j] = new Tile(tileBuffer, DEFAULTSHEET, sf::Vector2f((float)pos.y + j * TILE_SOURCE_SIZE.y, (float)pos.x + i * TILE_SOURCE_SIZE.x), orientation);
//
//	board[i][j]->setColor(board[i][j]->getType());		//test parcing and logic for base tile type
//
//	//std::cout << board[i][j]->getPosition().x << "," << board[i][j]->getPosition().y << std::endl;
//
//	}
//	}
//
//	*/
//
//
//	inFile.close();
//}