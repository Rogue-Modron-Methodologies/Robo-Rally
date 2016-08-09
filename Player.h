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
	Robot robot;
public:
	Player(std::string filename) : robot(filename) {};
	void programRobot() {};
};

#endif // PLAYER_H