// Object header
// Base Class for drawable objects

#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "ResourceManager.h"

namespace GLOBAL { extern ResourceManager<sf::Texture> textureList; }
enum orientation { up = 0, right = 90, down = 180, left = 270 };

class Object {
	sf::Sprite *sprite;
	sf::Vector2i srcSize;		// file source size
	sf::Vector2i srcPos;		// file source position

public:

	Object(	std::string filename, 
			sf::Vector2f pos = { 0, 0 }, 
			sf::Vector2f srcPos = { 0, 0 },
			sf::Vector2f srcSize = { 0, 0 } ) { loadObject(filename, pos, srcPos, srcSize); }
	~Object() { unloadObject(); };

	// Inline Functions
	void setScale(sf::Vector2f scale) { sprite->setScale(scale); }
	void setPosition(sf::Vector2f pos) { sprite->setPosition(pos); }
	void setSrcPos(sf::Vector2i source) { this->srcPos = source; updateTextRect(); }
	void setSrcPosX(int num) { this->srcPos.x = num; updateTextRect(); }
	void setSrcPosY(int num) { this->srcPos.y = num; updateTextRect(); }
	sf::Vector2i getSrcPos() const { return srcPos; }
	sf::Vector2f getPosition() const { return sprite->getPosition(); }
	sf::Vector2f getScale() const { return sprite->getScale(); }
	void draw(sf::RenderWindow &window) { window.draw(*sprite); }

	// Prototypes
	virtual void updateTextRect();
	bool isTargeted(sf::RenderWindow &gWindow);
	sf::Vector2f convertCoord(sf::RenderWindow &gWindow);

private:
	void loadObject(std::string filename, sf::Vector2f pos = { 0, 0 }, sf::Vector2f srcPos = { 0, 0 }, sf::Vector2f srcSize = { 0, 0 });
	void unloadObject() { delete sprite; }

};

#endif // OBJECT_H