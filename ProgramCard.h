// ProgramCard Header
// Derived from Card Object
// Used for programing robot's movements

#ifndef PROGRAMCARD_H
#define PROGRAMCARD_H

#include <string>
#include "Card.h"

class ProgramCard : public Card {
	int initiative;
	int action;
	int qty;
	//  Will have a font associated with it

public:
	ProgramCard(std::string filename, sf::Vector2f pos, std::string text, int initiative, sf::Vector2i srcPos = { 0,0 }) // srcPos defaults to 0 0  "Back of Card
		: Card(filename, pos, srcPos, text) { this->initiative = initiative; }
public:
	int getInitiative() const { return initiative; }
	void setInitiative(int num) { initiative = num; }
};

#endif // PROGRAMCARD_H