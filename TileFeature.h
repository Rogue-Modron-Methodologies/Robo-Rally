// TileFeature header
// features of single tile
//

#ifndef TILEFEATURE_H
#define TILEFEATURE_H



#include <string>
#include "Object.h"



class TileFeature : public Object  {
	std::string featureName;
	int qty;
	bool blockLOS;
	bool occupies;
	bool damages;
	bool moveRobot;

public:

	TileFeature(std::string filename) {};

};


#endif // TILEFEATURE_H
