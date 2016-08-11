// Board Implementation File

#include "Board.h"

//*************************************************************
// Opens the file (checks for validity)
// Loops through file and creates 2D Vector of Tile Objects
void Board::loadBoard(std::string filename, sf::Vector2f pos) {
	std::fstream inFile(filename.c_str());
	std::string boardName, tempLine, buffer;
	std::stringstream ssline, ssCell;
	sf::Vector2i boardPos = { 0, 0 };
	int orientation = 0;
	std::vector<Tile> row;

	if (!inFile)
		std::cout << "Error Opening " << filename << "\n\t\tTerminating Program\n", exit(EXIT_FAILURE);
	while (std::getline(inFile, tempLine)) {
		if (tempLine.size())
		{
			ssline << tempLine;
			while (std::getline(ssline, buffer, ','))
			{
				ssCell << buffer;
				ssCell >> boardName;
				ssCell >> orientation;
				//row.push_back(Board(boardName, sf::Vector2i(boardPos.x * 150, boardPos.y * 150), orientation));  //  Need to parse board size to know what multipliers to use.
				boardPos.y++;
				ssCell.str("");
				ssCell.clear();
			}
			board.push_back(row);
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
// Loops through 2D vector and calls drawMap on each element
// 
void Board::drawBoard(/*sf::RenderWindow &window*/) {
	//int i = 0, j = 0;
	//for (auto row = map.begin(); row != map.end(); ++row)
	//{
	//	for (auto col = row->begin(); col != row->end(); ++col) {
	//		std::cout << "Drawing Board: " << i << "," << j << " \n";
	//		col->drawTile(/*window*/);
	//		j++;
	//	}
	//	j = 0;
	//	i++;

		std::cout << "Board: " << name << " Dimensions: " << getDimensions().x << "x" << getDimensions().y 
				  << " Position: " << pos.x << "," << pos.y << " Orientation: " << orientation << std::endl;
	}