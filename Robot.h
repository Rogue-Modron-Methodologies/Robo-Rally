// Robot header
// what is needed to make robots rally
//

#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "TileFeature.h"
#include "Card.h"


class Robot : public TileFeature {

	std::vector<Card> moves;
	std::vector<Card> upgrades;

	std::string featureName;
	std::string spriteSheetFilename;
	int orientation;
	int qty;
	int boardOrientation;



public:
	Robot(std::string filename, sf::Vector2f pos, sf::Vector2i sPos) : TileFeature( featureName, orientation, qty, spriteSheetFilename, pos, boardOrientation) {};		


};



#endif // ROBOT_H