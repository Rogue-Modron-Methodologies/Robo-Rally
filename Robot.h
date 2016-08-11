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

public:
	Robot(std::string filename, sf::Vector2f pos, sf::Vector2i sPos) : TileFeature(filename, pos, sPos) {};


};



#endif // ROBOT_H