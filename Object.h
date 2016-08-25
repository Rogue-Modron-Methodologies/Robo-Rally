// Object header
// Base Class for drawable objects

#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ResourceManager.h"

namespace GLOBAL { extern ResourceManager<sf::Texture> textureList; }
enum orientation { up = 0, right = 90, down = 180, left = 270 };

const std::string IMAGE_HEADER = "resources/images/";

class Object {
	sf::Sprite *sprite;
	sf::Vector2i srcSize;		// file source size
	sf::Vector2i srcPos;		// file source position
	bool outOfPlay;

public:
	Object(	std::string filename, 
			sf::Vector2f pos, 
			sf::Vector2i srcPos = { 0, 0 },
			sf::Vector2i srcSize = { 150, 150 }) { loadObject(filename, pos, srcPos, srcSize); }
	~Object() { unloadObject(); };

	void setScale(sf::Vector2f scale) { sprite->setScale(scale); }
	void setPosition(sf::Vector2f pos) { sprite->setPosition(pos); }
	void setSrcPos(sf::Vector2i source) { this->srcPos = source; updateTextRect(); }
	void setSrcPosX(int num) { this->srcPos.x = num; updateTextRect(); }
	void setSrcPosY(int num) { this->srcPos.y = num; updateTextRect(); }
	void setColor(sf::Color color) { sprite->setColor(color); }
	void setRotation(int orientation) { sprite->setRotation((float)orientation); }
	void setOrigin();
	void setOutOfPlay(bool oop) { outOfPlay = oop; }
	bool isOutOfPlay() const { return outOfPlay; }
	sf::Vector2i getSrcPos() const { return srcPos; }
	sf::Vector2f getPosition() const { return sprite->getPosition(); }
	sf::Vector2f getScale() const { return sprite->getScale(); }
	sf::FloatRect getSize() const { return sprite->getGlobalBounds(); }
	float getRotation() const { return sprite->getRotation(); }
	void draw(sf::RenderWindow &window) { if(!outOfPlay) window.draw(*sprite); }
	bool isTargeted(sf::RenderWindow &window);


private:
	void unloadObject() { 
		outOfPlay = true;  
		delete sprite; 
	}
	void loadObject(std::string filename, sf::Vector2f pos, sf::Vector2i srcPos, sf::Vector2i srcSize);
	sf::Vector2f convertCoord(sf::RenderWindow &gWindow);
	virtual void updateTextRect();

};

#endif // OBJECT_H