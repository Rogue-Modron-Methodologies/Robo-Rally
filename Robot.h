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

	void moveForward(int qty = 1) { 
		switch ((int)getRotation()) {
		case up:
			setPosition(getPosition() - sf::Vector2f(0, (float)TILE_SOURCE_SIZE.y));
			break;
		case right:
			setPosition(getPosition() + sf::Vector2f((float)TILE_SOURCE_SIZE.x, 0));
			break;
		case down:
			setPosition(getPosition() + sf::Vector2f(0, (float)TILE_SOURCE_SIZE.y));
			break;
		case left:
			setPosition(getPosition() - sf::Vector2f((float)TILE_SOURCE_SIZE.x, 0));
			break;
		}
	}
	void moveBackward(int qty = 1) {
		switch ((int)this->getRotation()) {
		case up:
			setPosition(getPosition() + sf::Vector2f(0, (float)TILE_SOURCE_SIZE.y));
			break;
		case right:
			setPosition(getPosition() - sf::Vector2f((float)TILE_SOURCE_SIZE.x, 0));
			break;
		case down:
			setPosition(getPosition() - sf::Vector2f(0, (float)TILE_SOURCE_SIZE.y));
			break;
		case left:
			setPosition(getPosition() + sf::Vector2f((float)TILE_SOURCE_SIZE.x, 0));
			break;
		}
	}
	void uTurn() { setRotation((int)this->getRotation() + 180); }
	void turnLeft() { setRotation((int)this->getRotation() - 90); }
	void turnRight() { setRotation((int)this->getRotation() + 90); }

};
#endif // ROBOT_H