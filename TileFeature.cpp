// Tile Feature Implementation File
//

#include "TileFeature.h"

//*************************************************************
//  Loads a single Tile Feature
// 
void TileFeature::loadTileFeature(std::string featureName, int qty, int orientation) {
	setSrcPosY(1);  // 2nd row of spritesheet
	setRotation(orientation);

	if (featureName == "laser") {
		if (qty == 1) 
			setSrcPosX(laser1);
		else if (qty == 2) 
			setSrcPosX(laser2);
		else if (qty == 3) 
			setSrcPosX(laser3);
	}
	else if (featureName == "wall") 
			setSrcPosX(wall);
}

//*************************************************************
//for bug checking Tile and TileFeature private member variables
//Game, Map and Board habe printXxxx() functions to reach printTile() function
void TileFeature::drawDebugTileFeature() {
	std::cout << "\t" << name << " " << qty << " " << this->getRotation();
		
	if (blockLOS)
		std::cout << "blocks LOS ";
	if (occupies)
		std::cout << "occupies the tile ";
	if (damages)
		std::cout << "causes damage ";
	std::cout << std::endl;
}
