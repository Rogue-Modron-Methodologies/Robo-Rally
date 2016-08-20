// Player Header
// Has a collection of cards which are used to register it's robot
// Has a robot that actually moves about the board

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Robot.h"
#include "Card.h"



class Player : public Object  {
	std::string name;
	std::vector<Card> hand;
	std::vector<Card> moves;
	Robot robot;
public:
	Player(std::string robotName, sf::Vector2f robotPos) 
		: Object(ROBOT_BOARD, { 2000, 700 }, { 0, 0 }, { 300, 300 }), robot(robotName, robotPos) {};

	void drawPlayer(sf::RenderWindow &window) {
		this->draw(window);
		robot.draw(window);
	};
	void placeRobotOnBoard(sf::Vector2f pos, int orientation) { 
		robot.setPosition(pos); 
		robot.setRotation(orientation); 
	}

	void moveRobot(int direction) {
		switch (direction)
		{
		case up:
			robot.moveForward();
			break;
		case right:
			robot.turnRight();
			break;
		case down:
			robot.moveBackward();
			break;
		case left:
			robot.turnLeft();
			break;
		}
	}
	void programRobot() {};
};

#endif // PLAYER_H