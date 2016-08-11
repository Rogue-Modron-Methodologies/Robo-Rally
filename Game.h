// Game header
// header guards
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Map.h"
#include "Player.h"
#include "Deck.h"

enum class DeckType { movement = 0, upgrade = 1 };
enum class ResourceType { textures = 0, sounds = 1, fonts = 2 };

const sf::Vector2f START_LOC = { 0, 0 }; ////////////  For Now
const sf::Vector2i SCREEN_DIM = { 1000, 1000 };


class Game {
	sf::RenderWindow window;
	Map map;
	std::vector<Player> playerList;
	std::vector<Deck> decks;
	ResourceManager<sf::Font> fontList;
	ResourceManager<sf::Int16> soundList;					// https://gist.github.com/eXpl0it3r/c4edb9bcc1f00e29a79b

public:
	Game(std::string filename) : map(filename, START_LOC) {
		window.create(sf::VideoMode(SCREEN_DIM.x, SCREEN_DIM.y), "RoboRally!");
	}

	void playGame() {
		map.drawMap(window);			//  Debug:  Only Draws Once  : Uncomment Code in each draw function to use
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				}
			}
			window.clear();
			//map.drawMap(window);
			window.display();
		}
	}

};


//void fun(DeckType type)
//{
//	decks[type].shuffle();
//}

#endif // GAME_H
