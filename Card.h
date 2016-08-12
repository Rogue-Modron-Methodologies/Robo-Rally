// Card Header
// Virtual Base Class 

#ifndef CARD_H
#define CARD_H

#include <string>
#include "Object.h"

const sf::Vector2i CARD_SOURCE_SIZE = { 150, 250 };  //  ??????? Just a Guess

class Card : public Object {

	std::string text;
	int qty;

public:
	Card(std::string filename, sf::Vector2f pos, sf::Vector2i srcPos, std::string text, int qty) 
		: Object(filename, pos, srcPos, CARD_SOURCE_SIZE), text(text), qty(qty) {};
	~Card() {}
	// Getters and Setters
	void setQty(int num) { 	this->qty = num; }
	void setString(std::string str) { this->text = str; }
	int getQty() const { return qty; }
	std::string getText() const { return text; }

};

#endif // CARD_H