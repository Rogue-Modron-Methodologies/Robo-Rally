// ProgramCard Header
// Derived from Card Object
// Used for programing robot's movements

#ifndef PROGRAMCARD_H
#define PROGRAMCARD_H

#include <string>
#include "Card.h"

class ProgramCard : public Card {

public:
	ProgramCard(std::string filename, sf::Vector2f pos, std::string text = "", int qty = 1, sf::Vector2i srcPos = { 0,0 }) // srcPos defaults to 0 0  "Back of Card
		: Card(filename, pos, srcPos, text, qty) {};


};

#endif // PROGRAMCARD_H