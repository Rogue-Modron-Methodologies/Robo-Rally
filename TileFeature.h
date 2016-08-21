// TileFeature header
// features of single tile
//

#ifndef TILEFEATURE_H
#define TILEFEATURE_H

#include <string>
#include "Object.h"

enum TILE_FEATURES { wall = 0, laser1 = 1, laser2 = 2, laser3 = 3, gear1 = 4, gear2 = 5 };

const sf::Vector2i TILE_SOURCE_SIZE = { 150, 150 };

class TileFeature : public Object  {
	std::string name;
	int qty;
	bool blockLOS;
	bool occupies;
	bool damages;

public:
	TileFeature(std::string featureName, int qty, std::string spriteSheetFilename, sf::Vector2f pos, int orientation)
		: Object(spriteSheetFilename, pos, sf::Vector2i(0, 0), TILE_SOURCE_SIZE) {
		this->name = featureName;
		this->qty = qty;
		setOrigin();
		loadTileFeature(featureName, qty, orientation);
	};

	~TileFeature() {};
	void loadTileFeature(std::string featureName, int qty, int orientation);
	std::string getName() { return name; };
	void drawDebugTileFeature();
};
#endif // TILEFEATURE_H
