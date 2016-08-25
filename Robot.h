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
const int DEATH_HP = 10;

class Robot : public Object {
	std::vector<Card> upgrades;
	std::string name;
	sf::Vector2f resPoint;
	int damage;


public:
	Robot(std::string robotName, sf::Vector2f robotPos, sf::Vector2i sPos = { 0,0 }, int orientation = 0)
		: Object(ROBOT_SPRITESHEET, robotPos) { loadRobot(robotName, robotPos, sPos, orientation); }

	void loadRobot(std::string robotName, sf::Vector2f robotPos, sf::Vector2i sPos = { 0,0 }, int orientation = 0) {
		damage = 0;
		setOrigin();
		name = robotName;
		//if else statment for sourcePos by name
		setRotation(orientation);
	}
	std::string getName() const { return name; }
	int getDamage() const { return damage; }
	void damageRobot(int num) { damage += num; }
	void setResPoint(sf::Vector2f pos) { resPoint = pos; }
	sf::Vector2f getResPoint() { return resPoint; }
	void returntoResPoint(int startingDamage = 2) {
		damage = startingDamage;
		setPosition(resPoint); 
		setOutOfPlay(false);
	}
	void removeRobot() { setOutOfPlay(true); }

};
#endif // ROBOT_H