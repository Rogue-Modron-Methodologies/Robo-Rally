// Game header
// header guards
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.h"
#include "Player.h"
#include "Deck.h"
#include "ResourceManager.h"

enum class DeckType { movement = 0, upgrade = 1 };
enum class ResourceType { textures = 0, sounds = 1, fonts = 2 };


class Game {
	Map map;
	std::vector<Player> playerList;
	std::vector<Deck> decks;
	std::vector<ResourceManager<sf::Texture>> textureList;

public:
	Game(std::string filename ) : map(filename) {
	};


};


//void fun(DeckType type)
//{
//	decks[type].shuffle();
//}

#endif // GAME_H
