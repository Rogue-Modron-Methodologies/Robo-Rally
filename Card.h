// Card Header
// Virtual Base Class 

#ifndef CARD_H
#define CARD_H

#include <string>
#include "Object.h"

class Card : public Object {

public:
	Card(std::string filename) {};
};

#endif // CARD_H