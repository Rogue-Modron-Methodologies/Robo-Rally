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


