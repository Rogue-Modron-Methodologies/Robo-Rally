// TileFeature header
// features of single tile
//

#ifndef TILEFEATURE_H
#define TILEFEATURE_H

#include <string>
#include "Object.h"

enum TILE_FEATURES { wall = 0, laser1 = 1, laser2 = 2, laser3 = 3, gear1 = 4, gear2 = 5 };

const sf::Vector2i TILE_SOURCE_SIZE = { 50, 50 };

class TileFeature : public Object  {
	std::string featureName;
	int qty;
	bool blockLOS;
	bool occupies;
	bool damages;
	bool moveRobot;

public:
	TileFeature(std::string featureName, int orientation, int qty, std::string spriteSheetFilename, sf::Vector2f pos, int boardOrientation)
		: Object(spriteSheetFilename, pos, sf::Vector2i(0, 0), TILE_SOURCE_SIZE) {
	
		setPosition(pos);
		setOrigin();

		loadTileFeature(featureName, orientation, qty, boardOrientation);

	};

	~TileFeature() {};

	void loadTileFeature(std::string featureName, int orientation, int qty, int boardOrientation);


	std::string getFeatureName() { return featureName; };

	void printTileFeature();

};


#endif // TILEFEATURE_H
