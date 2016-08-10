#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"


class Deck : public Object  {
	std::vector<Card> deck;
	
public:
	Deck(std::string filename) : Object(filename) {};
	void deal() {};
	void shuffle() {};

};




#endif // DECK_H
