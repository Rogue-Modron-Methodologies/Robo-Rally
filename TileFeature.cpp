//
//

#include "TileFeature.h"



//*************************************************************
//  
// 
void TileFeature::loadTileFeature(std::string featureName, int orientation, int qty, int boardOrientation) {

	setSrcPosY(1);

	setRotation(orientation + boardOrientation);

	if (featureName == "laser") {

		if (qty == 1) {
			setSrcPosX(laser1);
		}
		else if (qty == 2) {
			setSrcPosX(laser2);
		}
		else if (qty == 3) {
			setSrcPosX(laser3);
		}
	}
	else if (featureName == "wall") {

			setSrcPosX(wall);
	}

}


//for bug checking Tile and TileFeature private member variables
//Game, Map and Board habe printXxxx() functions to reach printTile() function
void TileFeature::printTileFeature() {

	std::cout << "\t" << featureName << " " << qty << " ";
		
	if (blockLOS)
		std::cout << "blocks LOS ";

	if (occupies)
		std::cout << "occupies the tile ";

	if (damages)
		std::cout << "causes damage ";

	if (moveRobot)
		std::cout << "moves robot ";	
		
		std::cout << std::endl;

}
