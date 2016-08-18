// Card Header
// Virtual Base Class 

#ifndef CARD_H
#define CARD_H

#include <string>
#include "Object.h"

const sf::Vector2i CARD_SOURCE_SIZE = { 300, 300 };  //  ??????? Just a Guess

class Card : public Object {

	std::string text;

public:
	Card(std::string filename, sf::Vector2f pos, sf::Vector2i srcPos, std::string text) 
		: Object(filename, pos, srcPos, CARD_SOURCE_SIZE), text(text) {};
	~Card() {}
	// Getters and Setters
	void setString(std::string str) { this->text = str; }
	std::string getText() const { return text; }

};

#endif // CARD_H