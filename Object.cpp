//  Object Implementation File
#include "Object.h"

ResourceManager<sf::Texture> GLOBAL::textureList;

//*************************************************************
// Creates the sprite for the object.  
// Sets the inital scale, source position, and screen position.
void Object::loadObject(std::string filename, sf::Vector2f pos, sf::Vector2i sPos, sf::Vector2i sSize) {
	outOfPlay = false;
	std::string textureFilename = IMAGE_HEADER + filename;
	this->srcSize = sSize;
	this->srcPos = sPos;
	sprite = new sf::Sprite;

	sprite->setTexture(GLOBAL::textureList.getResource(textureFilename));

	updateTextRect();
	sprite->setPosition(pos);
}

//*************************************************************
//  Converts Coordinates to current view
sf::Vector2f Object::convertCoord(sf::RenderWindow &gWindow) {
	sf::Vector2i pixelPos = sf::Mouse::getPosition(gWindow);
	sf::Vector2f worldPos = gWindow.mapPixelToCoords(pixelPos);
	return worldPos;
}

//*************************************************************
//  Check if Mouse Position is within bounds of the sprite
bool Object::isTargeted(sf::RenderWindow &gWindow) {
	if (outOfPlay)
		return false;
	return sprite->getGlobalBounds().contains(convertCoord(gWindow));
}

//*************************************************************
//  Updates the TextureRect to new position 
void Object::updateTextRect() {
	sprite->setTextureRect(sf::IntRect(srcPos.x * srcSize.x, srcPos.y * srcSize.y, srcSize.x, srcSize.y));
}

//*************************************************************
//  Calculates the center of the sprite and sets that to the origin for all transformations 
void Object::setOrigin() {
	sprite->setOrigin(sprite->getGlobalBounds().width / 2,sprite->getGlobalBounds().height / 2);
}
