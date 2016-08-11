// Map Implementation File

#include "Map.h"


//*************************************************************
// Opens the file (checks for validity)
// Loops through file and creates 2D Vector of Board Objects
void Map::loadMap(std::string filename, sf::Vector2f pos) {
	std::fstream inFile(filename.c_str());
	std::string boardName, tempLine, buffer;
	std::stringstream ssline, ssCell;
	sf::Vector2i boardPos = { 0, 0 };
	int orientation = 0;
	std::vector<Board> row;

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
				row.push_back(Board(boardName, sf::Vector2i(boardPos.x * 150, boardPos.y * 150), orientation));  //  Need to parse board size to know what multipliers to use.
				boardPos.y++;
				ssCell.str("");
				ssCell.clear();
			}
			map.push_back(row);
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
void Map::drawMap(/*sf::RenderWindow &window*/) {
	int i = 0, j = 0;
	for (auto row = map.begin(); row != map.end(); ++row)
	{
		for (auto col = row->begin(); col != row->end(); ++col) {
			std::cout << "Drawing Map: " << i << "," << j << " \n";
			col->drawBoard(/*window*/);
			j++;
		}
		j = 0;
		i++;
	}

	
}