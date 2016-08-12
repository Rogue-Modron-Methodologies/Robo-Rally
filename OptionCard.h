// Upgrade Header
// Derived from Card Object
// Used for upgrading robot's abilities

#ifndef OPTIONCARD_H
#define OPTIONCARD_H

#include <string>
#include "Card.h"

class OptionCard : public Card {

public:
	OptionCard(std::string filename, sf::Vector2f pos, std::string text = "", int qty = 1, sf::Vector2i srcPos = { 0,0 }) // srcPos defaults to 0 0  "Back of Card
		: Card(filename, pos, srcPos, text, qty) {};
};

#endif // OPTIONCARD_H