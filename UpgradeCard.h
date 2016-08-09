// Upgrade Header
// Derived from Card Object
// Used for upgrading robot's abilities

#ifndef UPGRADECARD_H
#define UPGRADECARD_H

#include <string>
#include "Card.h"

class UpgradeCard : public Card {

public:
	UpgradeCard(std::string filename) : Card(filename) {};
};

#endif // UPGRADECARD_H