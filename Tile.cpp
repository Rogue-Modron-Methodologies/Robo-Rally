//
//

#include "Tile.h"




//*********************This function needs to exist
//*********************It is a constructor.  It needs to set all initial values. The sprite, texture, position, etc
void Tile::loadTile(std::string tileInformation, sf::Vector2f pos, int boardOrientation, std::string spriteSheetFilename) {

	//std::string tileName;
	int orientation = 0;

	std::stringstream sstile;

	sstile << tileInformation;

	sstile >> this->tileType;


	if (tileType == "floor") {
		setSrcPosX(ground);

	}
	else if (tileType == "pit") {
		setSrcPosX(pit);			

	}

	if(tileType != "floor" && tileType != "pit"){
	sstile >> orientation;
	setRotation(orientation + boardOrientation);
	sstile >> this->qty;
	}

	if (tileType == "repair") {				//continue parsing to find repair 1 and 2

		if (qty == 1) {
			setSrcPosX(repair1);
		}
		else if (qty == 2) {
			setSrcPosX(repair2);
		}

	}
	else if (tileType == "conv") {			//continue parsing to find speed 1 and 2 and orientation

		if (qty == 1) {
			setSrcPosX(conv1);
		}
		else if (qty == 2) {
			setSrcPosX(conv2);
		}

	}
	else if (tileType == "convbr") {			//continue parsing to find speed 1 and 2 and orientation

		if (qty == 1) {
			setSrcPosX(convbr1);
		}
		else if (qty == 2) {
			setSrcPosX(convbr2);
		}

	}
	else if (tileType == "convbl") {			//continue parsing to find speed 1 and 2 and orientation

		if (qty == 1) {
			setSrcPosX(convbr1);
		}
		else if (qty == 2) {
			setSrcPosX(convbr2);
		}

		setScale({ -1.f,1.f });					//flip sprite for left bend

	}
	else if (tileType == "convhr") {			//continue parsing to find speed 1 and 2 and orientation

		if (qty == 1) {
			setSrcPosX(convhr1);
		}
		else if (qty == 2) {
			setSrcPosX(convhr2);
		}

	}
	else if (tileType == "convhl") {			//continue parsing to find speed 1 and 2 and orientation

		if (qty == 1) {
			setSrcPosX(convhr1);
		}
		else if (qty == 2) {
			setSrcPosX(convhr2);
		}

		setScale({ -1.f,1.f });					//flip sprite for left H join

	}
	else if (tileType == "convt") {			//continue parsing to find speed 1 and 2 and orientation	if (tileName == "convt")

		if (qty == 1) {
			setSrcPosX(convt1);
		}
		else if (qty == 2) {
			setSrcPosX(convt2);
		}

	}
	else if (tileType == "gear") {			//continue parsing to find speed 1 and 2 and orientation	if (tileName == "convt")

		if (qty == 0) {
			setSrcPosX(gearClock);
		}
		else if (qty == 1) {
			setSrcPosX(gearAnti);
		}

	}
	//else {
	//	//if it gets here there is an error do we want to check that? have option that wont error out?
	//}

	std::string featureName;
	int featureOrientation, featureQty;



	while (sstile >> featureName) {
		sstile >> featureOrientation;
		sstile >> featureQty;

		features.push_back(new TileFeature(featureName, featureOrientation, featureQty, spriteSheetFilename, pos, boardOrientation));
		
	}

};


//*********************
//*********************
void Tile::drawTile(sf::RenderWindow &window) {

	int numFeatures = features.size();

	for (int i = 0; i < numFeatures; ++i) {
		features[i]->draw(window);
	}
};

//*********************
//*********************
void Tile::unloadTile() {

	for (int i = 0; i < features.size(); ++i) {
		delete features[i];
	}

	features.clear();
}