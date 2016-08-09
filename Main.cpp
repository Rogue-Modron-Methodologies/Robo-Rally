//  Robo Rally Game
//  Need to get License Info

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>
#include <string>

int main() {
	bool movR, movL, movU, movD;
	movR = movL = movU = movD = false;
	
	sf::Vector2f velocity = { 0, 0 };
	float acceleration = .1f;
	float posMaxAcc = 1;
	float negMaxAcc = -1;

	sf::Texture texture1;
	texture1.loadFromFile("Mauler.jpg");
	sf::Sprite sprite;
	sprite.setTexture(texture1);
	sprite.setScale(.2f, .2f);
	sprite.setColor(sf::Color::Green);

	sf::RenderWindow window(sf::VideoMode(800, 800), "ScrumBums SFML: Look it works!");
	//sf::CircleShape shape(20.f);
	//shape.setFillColor(sf::Color::Green);
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				if (event.key.code == sf::Keyboard::Right) {
					movR = true;
					movL = false;
				}
				if (event.key.code == sf::Keyboard::Left) {
					movL = true;
					movR = false;
				}	
				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Numpad8) {
					movU = true;
					movD = false;
				}
				if (event.key.code == sf::Keyboard::Down) {
					movD = true;
					movU = false;
				}
				if (event.key.code == sf::Keyboard::H) {
					sprite.setPosition(window.getSize().x / 2,window.getSize().y / 2);
				}
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Right)
					movR = false;
				if (event.key.code == sf::Keyboard::Left)
					movL = false;
				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Numpad8)
					movU = false;
				if (event.key.code == sf::Keyboard::Down)
					movD = false;
				break;
			}
		}

		if (movD) {
			if (velocity.y < posMaxAcc)
				velocity.y += acceleration;
			else
				velocity.y = posMaxAcc;
		}
		else if (movU) {
			if (velocity.y > negMaxAcc)
				velocity.y -= acceleration;
			else
				velocity.y = negMaxAcc;
		}
		else if (movR) {
			if (velocity.x < posMaxAcc)
				velocity.x += acceleration;
			else
				velocity.x = posMaxAcc;
		}
		else if (movL) {
			if (velocity.x > negMaxAcc)
				velocity.x -= acceleration;
			else
				velocity.x = negMaxAcc;
		}
		else {
			velocity.x = 0;
			velocity.y = 0;
		}
		
		//shape.move(velocity);
		sprite.move(velocity);
		window.clear();
		window.draw(sprite);
		//window.draw(shape);
		window.display();
	}

	return 0;
}