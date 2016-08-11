// Card Header
// Virtual Base Class 

#ifndef CARD_H
#define CARD_H

#include <string>
#include "Object.h"

const sf::Vector2i CARD_SOURCE_SIZE = { 150, 150 };  //  ??????? Just a Guess

class Card : public Object {

public:
	Card(std::string filename) : Object(filename) {};
};

#endif // CARD_H