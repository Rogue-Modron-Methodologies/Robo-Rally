// Robot header
// what is needed to make robots rally
//

#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "TileFeature.h"
#include "Card.h"

const std::string ROBOT_SPRITESHEET = "robotspritesheet.png";
const std::string ROBOT_BOARD = "robotboardsheet.png";
const sf::Vector2i ROBOT_SOURCE_SIZE = { 150, 150 };  
const sf::Vector2i ROBOT_BOARD_SIZE = { 300, 300 }; //  ??????? Just a Guess

class Robot : public Object {
	std::vector<Card> upgrades;
	std::string name;
	sf::Vector2f resPoint;

public:
	Robot(std::string robotName, sf::Vector2f robotPos, sf::Vector2i sPos = { 0,0 }, int orientation = 0)
		: Object(ROBOT_SPRITESHEET, robotPos) { loadRobot(robotName, robotPos, sPos, orientation); }

	void loadRobot(std::string robotName, sf::Vector2f robotPos, sf::Vector2i sPos = { 0,0 }, int orientation = 0) {
		setOrigin();
		name = robotName;
		//if else statment for sourcePos by name
		setRotation(orientation);
	}
	std::string getName() { return name; }
	void setResPoint(sf::Vector2f pos) { resPoint = pos; }
	void returntoResPoint() { setPosition(resPoint); }

};
#endif // ROBOT_H