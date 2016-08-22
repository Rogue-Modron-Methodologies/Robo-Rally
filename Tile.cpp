//
//

#include "Tile.h"

//*********************
//  Sets all initial values. The sprite, texture, position, etc
void Tile::loadTile(std::string tileInformation, sf::Vector2f pos, int boardOrientation, std::string spriteSheetFilename) {
	int orientation = 0;
	std::stringstream sstile;

	sstile << tileInformation;
	sstile >> this->tileType;

	if (tileType == "floor") 
		setSrcPosX(ground);
	else if (tileType == "pit") {
		setSrcPosX(pit);
		causesDeath = true;
	}
		
	if(tileType != "floor" && tileType != "pit") {
		sstile >> orientation;
		setRotation(orientation + boardOrientation);
		sstile >> this->qty;
	}

	if (tileType == "repair") {				//continue parsing to find repair 1 and 2
		if (qty == 1) 
			setSrcPosX(repair1);
		else //if (qty == 2) 
			setSrcPosX(repair2);
	}
	else if (tileType == "conv") {			//continue parsing to find speed 1 and 2 and orientation
		if (qty == 1) 
			setSrcPosX(conv1);
		else //if (qty == 2) 
			setSrcPosX(conv2);
	}
	else if (tileType == "convbr") {			//continue parsing to find speed 1 and 2 and orientation
		if (qty == 1) 
			setSrcPosX(convbr1);
		else //if (qty == 2) 
			setSrcPosX(convbr2);
	}
	else if (tileType == "convbl") {			//continue parsing to find speed 1 and 2 and orientation
		if (qty == 1) 
			setSrcPosX(convbr1);
		else //if (qty == 2) 
			setSrcPosX(convbr2);
		setScale({ -1.f,1.f });					//flip sprite for left bend
	}
	else if (tileType == "convhr") {			//continue parsing to find speed 1 and 2 and orientation
		if (qty == 1) 
			setSrcPosX(convhr1);
		else //if (qty == 2) 
			setSrcPosX(convhr2);
	}
	else if (tileType == "convhl") {			//continue parsing to find speed 1 and 2 and orientation
		if (qty == 1) 
			setSrcPosX(convhr1);
		else //if (qty == 2) 
			setSrcPosX(convhr2);
		setScale({ -1.f,1.f });					//flip sprite for left H join
	}
	else if (tileType == "convt") {			//continue parsing to find speed 1 and 2 and orientation	if (tileName == "convt")
		if (qty == 1) 
			setSrcPosX(convt1);
		else //if (qty == 2) 
			setSrcPosX(convt2);
	}
	else if (tileType == "gear") {			//continue parsing to find speed 1 and 2 and orientation	if (tileName == "convt")
		if (qty == 0) 
			setSrcPosX(gearClock);
		else //if (qty == 1) 
			setSrcPosX(gearAnti);
	}
	else {
		if(tileType != "floor" && tileType != "pit")
			std::cout << "THIS SHOULD NEVER HAPPEN! in Tile.h" << std::endl;
	}

	std::string featureName;
	int featureOrientation, featureQty;

	while (sstile >> featureName) {
		sstile >> featureOrientation;
		sstile >> featureQty;
		features.push_back(new TileFeature(featureName, featureQty, spriteSheetFilename, pos, featureOrientation + boardOrientation));
	}
};

//*********************
//release dynamcally allocated vector of tile features
void Tile::unloadTile() {
	for (unsigned i = 0; i < features.size(); ++i) 
		delete features[i];
	features.clear();
}

//*********************
//renders tile floor and tileFeature sprites for one tile
void Tile::drawTile(sf::RenderWindow &window) {
	this->draw(window);
	for (unsigned i = 0; i < features.size(); ++i)
		features[i]->draw(window);
};

//*********************
//prints to screen the ground tile and, if any, the tile's features
void Tile::drawDebugTile() {
	std::cout << tileType << " " << qty << " " << this->getRotation() << " ";
	if (robot)
		std::cout << robot->getName() << " ";
	if (features.size() == 0) 
		std::cout << ": no tile features.\n\n";
	else {
		std::cout << ": features:\n";
		for (unsigned i = 0; i < features.size(); ++i)
			features[i]->drawDebugTileFeature();
		std::cout << std::endl;
	}
};

