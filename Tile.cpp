//
//

#include "Tile.h"




//*********************This function needs to exist
//*********************It is a constructor.  It needs to set all initial values. The sprite, texture, position, etc
void Tile::loadTile(std::string tileInformation, sf::Vector2f pos, int boardOrientation) {

	std::string tileName;
	int orientation = 0;

	std::stringstream sstile;

	sstile << tileInformation;

	sstile >> tileName;

	if (tileName == "floor") {
		setSrcPosX(ground);

	}
	else if (tileName == "pit") {
		setSrcPosX(pit);			

	}

	sstile >> orientation;
	setRotation(orientation + boardOrientation);
	sstile >> this->qty;

	if (tileName == "repair") {		//continue parsing to find repair 1 and 2

		if (qty == 1) {
			setSrcPosX(repair1);
		}
		else if (qty == 2) {
			setSrcPosX(repair2);
		}

	}
	else if (tileName == "gear") {			//continue parsing to find gear 1 and 2

		if (qty == 0) {

		}
		else if (qty == 1) {

		}

	}
	else if (tileName == "conv") {			//continue parsing to find speed 1 and 2 and orientation

		if (qty == 1) {
			setSrcPosX(conv1);
		}
		else if (qty == 2) {
			setSrcPosX(conv2);
		}

	}
	else if (tileName == "convbr") {			//continue parsing to find speed 1 and 2 and orientation

		if (qty == 1) {
			setSrcPosX(convbr1);
		}
		else if (qty == 2) {
			setSrcPosX(convbr2);
		}

	}
	else if (tileName == "convbl") {			//continue parsing to find speed 1 and 2 and orientation

		if (qty == 1) {
			setSrcPosX(convbr1);
		}
		else if (qty == 2) {
			setSrcPosX(convbr2);
		}

		setScale({ -1.f,1.f });					//flip sprite for left bend

	}
	else if (tileName == "convhr") {			//continue parsing to find speed 1 and 2 and orientation

		if (qty == 1) {
			setSrcPosX(convhr1);
		}
		else if (qty == 2) {
			setSrcPosX(convhr2);
		}

	}
	else if (tileName == "convhl") {			//continue parsing to find speed 1 and 2 and orientation

		if (qty == 1) {
			setSrcPosX(convhr1);
		}
		else if (qty == 2) {
			setSrcPosX(convhr2);
		}

		setScale({ -1.f,1.f });					//flip sprite for left H join

	}
	else {			//continue parsing to find speed 1 and 2 and orientation	if (tileName == "convt")

		if (qty == 1) {
			setSrcPosX(convt1);
		}
		else if (qty == 2) {
			setSrcPosX(convt2);
		}

	}

	

};

