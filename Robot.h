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
const sf::Vector2i ROBOT_SOURCE_SIZE = { 150, 150 };  //  ??????? Just a Guess
const sf::Vector2i ROBOT_BOARD_SIZE = { 300, 300 }; //  ??????? Just a Guess

class Robot : public TileFeature {
	std::vector<Card> upgrades;

public:
	Robot(std::string robotName, sf::Vector2f robotPos, sf::Vector2i sPos = { 0,0 }, int orientation = 0)
		: TileFeature(robotName, 1, ROBOT_SPRITESHEET, robotPos, orientation) {}

	void moveForward(int qty = 1) { 
		switch ((int)getRotation()) {
		case up:
			setPosition(getPosition() - sf::Vector2f(0, TILE_SOURCE_SIZE.y));
			break;
		case right:
			setPosition(getPosition() + sf::Vector2f(TILE_SOURCE_SIZE.x, 0));
			break;
		case down:
			setPosition(getPosition() + sf::Vector2f(0, TILE_SOURCE_SIZE.y));
			break;
		case left:
			setPosition(getPosition() - sf::Vector2f(TILE_SOURCE_SIZE.x, 0));
			break;
		}
	}
	void moveBackward(int qty = 1) {
		switch ((int)this->getRotation()) {
		case up:
			setPosition(getPosition() + sf::Vector2f(0, TILE_SOURCE_SIZE.y));
			break;
		case right:
			setPosition(getPosition() - sf::Vector2f(TILE_SOURCE_SIZE.x, 0));
			break;
		case down:
			setPosition(getPosition() - sf::Vector2f(0, TILE_SOURCE_SIZE.y));
			break;
		case left:
			setPosition(getPosition() + sf::Vector2f(TILE_SOURCE_SIZE.x, 0));
			break;
		}
	}
	void uTurn() { setRotation((int)this->getRotation() + 180); }
	void turnLeft() { setRotation((int)this->getRotation() - 90); }
	void turnRight() { setRotation((int)this->getRotation() + 90); }

};
#endif // ROBOT_H