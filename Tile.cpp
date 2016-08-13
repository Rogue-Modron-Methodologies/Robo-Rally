//
//

#include "Tile.h";



//i am not understanding something about the load file go below it to see work around


//*********************This function needs to exist
//*********************It is a constructor.  It needs to set all initial values. The sprite, texture, position, etc
//void Tile::loadTile(std::string tileInformation, sf::Vector2f pos, int boardOrientation) {
//
//	std::string tileName;
//
//	std::stringstream sstile;
//
//	sstile << tileInformation;
//
//	std::getline(sstile, tileName, ' ');
//
//	if (tileName == "floor") {			
//
//
//	}
//	else if (tileName == "pit") {
//
//
//	}
//	else if (tileName == "repair") {		//continue parsing to find repair 1 and 2
//
//
//
//	}
//	else if (tileName == "gear") {			//continue parsing to find gear 1 and 2
//
//
//
//	}
//	else if (tileName == "conv") {			//continue parsing to find speed 1 and 2 and orientation
//
//
//
//	}
//	else if (tileName == "convbr") {			//continue parsing to find speed 1 and 2 and orientation
//
//
//
//	}
//	else if (tileName == "convbl") {			//continue parsing to find speed 1 and 2 and orientation
//
//
//
//	}
//	else if (tileName == "convhr") {			//continue parsing to find speed 1 and 2 and orientation
//
//
//
//	}
//	else if (tileName == "convhl") {			//continue parsing to find speed 1 and 2 and orientation
//
//
//
//	}
//	else if (tileName == "convt") {			//continue parsing to find speed 1 and 2 and orientation
//
//
//
//
//	}
//
//
//
//};



//****************What does this function do?
//****************Why are you returning a Color?  
//simpler function (for a simpler coder? ;) ) to test logic, includes testing code
//adding color hues to the existing tiles to check logic (now also used to check orientation code in board.cpp)

sf::Color Tile::tileType(std::string tileInformation) {
	std::string tileName;
	int orientation, qty;

	std::stringstream sstile;

	sstile << tileInformation;

	sstile >> tileName;

	if (tileName == "floor") {
		return sf::Color(255, 255, 255);

	}
	else if (tileName == "pit") {
		setSrcPosX(1);			//******************************************* Won't be a literal for long.  Will create an enum.
		return sf::Color(128, 128, 128);		//dark grey

	}
	else if (tileName == "repair") {		//continue parsing to find repair 1 and 2
		
		sstile >> orientation;
		sstile >> qty;

		if (qty == 1) {
			return sf::Color(128, 255, 128);		//light green
		}
		else if (qty == 2) {
			return sf::Color(0, 255, 0);			//green
		}



	}
	else if (tileName == "gear") {			//continue parsing to find gear 1 and 2

		sstile >> orientation;
		sstile >> qty;

		if (qty == 0) {
			return sf::Color(255, 255, 0);			//yellow
		}
		else if (qty == 1) {
			return sf::Color(255, 0, 0);			//red
		}

	}
	else if (tileName == "conv") {			//continue parsing to find speed 1 and 2 and orientation

		sstile >> orientation;
		sstile >> qty;

		if (qty == 1) {
			return sf::Color(255, 165, 0);			//orange
		}
		else if (qty == 2) {
			return sf::Color(0, 0, 255);			//blue
		}

	}
	else if (tileName == "convbr") {			//continue parsing to find speed 1 and 2 and orientation

		sstile >> orientation;
		sstile >> qty;

		if (qty == 1) {
			return sf::Color(255, 165, 0);			//orange
		}
		else if (qty == 2) {
			return sf::Color(0, 0, 255);			//blue
		}

	}
	else if (tileName == "convbl") {			//continue parsing to find speed 1 and 2 and orientation

		sstile >> orientation;
		sstile >> qty;

		if (qty == 1) {
			return sf::Color(255, 165, 0);			//orange
		}
		else if (qty == 2) {
			return sf::Color(0, 0, 255);			//blue
		}

	}
	else if (tileName == "convhr") {			//continue parsing to find speed 1 and 2 and orientation


		sstile >> orientation;
		sstile >> qty;

		if (qty == 1) {
			return sf::Color(255, 165, 0);			//orange
		}
		else if (qty == 2) {
			return sf::Color(0, 0, 255);			//blue
		}
	}
	else if (tileName == "convhl") {			//continue parsing to find speed 1 and 2 and orientation

		sstile >> orientation;
		sstile >> qty;

		if (qty == 1) {
			return sf::Color(255, 165, 0);			//orange
		}
		else if (qty == 2) {
			return sf::Color(0, 0, 255);			//blue
		}

	}
	else {			//continue parsing to find speed 1 and 2 and orientation	if (tileName == "convt")


		sstile >> orientation;
		sstile >> qty;

		if (qty == 1) {
			return sf::Color(255, 165, 0);			//orange
		}
		else if (qty == 2) {
			return sf::Color(0, 0, 255);			//blue
		}

	}


	return sf::Color(0, 0, 0);

};