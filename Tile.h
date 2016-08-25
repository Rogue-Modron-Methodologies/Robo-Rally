// Tile Header
// Represents a single square on the board
//

#ifndef TILE_H
#define TILE_H

#include <vector>
#include "TileFeature.h"
#include "Robot.h"

enum FLOOR_TILES { ground = 0, pit = 1, repair1 = 2, repair2 = 3, 
					conv1 = 4 , convbr1 = 5, convbl1 = 5, convhr1 = 6, convhl1 = 6, convt1 = 7, 
					conv2 = 8, convbr2 = 9, convbl2 = 9, convhr2 = 10, convhl2 = 10, convt2 = 11,
					gearClock = 12, gearAnti = 13 };

class Tile : public Object {

	std::vector<TileFeature *> features;
	std::string tileType;
	const Robot *robot;
	int qty;
	bool movesBot;
	bool rotatesBot;
	bool causeDeath;

public:
	Tile(std::string tileInformation, std::string spriteSheetFilename, sf::Vector2f pos, int boardOrientation)
		: Object(spriteSheetFilename, pos, sf::Vector2i(0, 0), TILE_SOURCE_SIZE) {	
		setPosition(pos);
		setOrigin();
		loadTile(tileInformation, pos, boardOrientation, spriteSheetFilename);
	};  

	~Tile() { unloadTile(); };
	void loadTile(std::string tileInformation, sf::Vector2f pos, int boardOrientation, std::string spriteSheetFilename);
	void unloadTile();
	void drawTile(sf::RenderWindow &window);	
	void drawDebugTile();
	void addRobot(const Robot &rbt) { robot = &rbt; }
	void removeRobot() { robot = NULL; }
	bool causesDeath() const { return causeDeath; }
	bool movesRobot(int &qty, int &orientation) const { 
		qty = this->qty;
		orientation = (int)getRotation();
		return movesBot; 

	}
	bool rotatesRobot(int &spin) const {
		spin = this->qty;
		return rotatesBot;
	}
	bool movementBlocked(int direction) {
		for (unsigned i = 0; i < features.size(); ++i)
			if (features[i]->blockMovement(direction))
				return true;
		return false;
	}
	bool causesDamage(int &num) const {
		for (unsigned i = 0; i < features.size(); ++i)
			if (features[i]->causesDamage(num))
				return true;
		return false;
	}
};
#endif // TILE_H