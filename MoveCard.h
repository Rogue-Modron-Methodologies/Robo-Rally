// MoveCard Header
// Derived from Card Object
// Used for programing robot's movements

#ifndef MOVECARD_H
#define MOVECARD_H

#include <string>
#include "Card.h"

class MoveCard : public Card {

public:
	MoveCard(std::string filename) : Card(filename) {};
};

#endif // MOVECARD_H