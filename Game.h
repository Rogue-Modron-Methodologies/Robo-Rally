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


enum class ResourceType { textures = 0, sounds = 1, fonts = 2 };

#define PROGRAM_CARD_LIST "ProgramList.txt"
#define PROGRAM_SPRITESHEET "ProgramSpriteSheet.png"
#define OPTION_CARD_LIST "OptionList.txt"
#define OPTION_SPRITESHEET "OptionSpriteSheet.png"

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
	Game(std::string filename) : map(filename, START_LOC) { loadGame(); }

	void playGame();
private:
	void loadGame();
	void unloadGame();


};

#endif // GAME_H
