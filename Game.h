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

const sf::Vector2f START_LOC = { 75, 75 }; ////////////  For Now
const sf::Vector2i SCREEN_DIM = { 800, 800 };
const float MIN_ZOOM = 300;
const float MAX_ZOOM = 5000;
const float ZOOM_QTY = .9f;

class Game {
	sf::RenderWindow window;
	sf::View view;
	Map map;
	Player *cPlyr;
	std::vector<Player*> playerList;
	std::vector<Deck*> decks;
	ResourceManager<sf::Font> fontList;
	ResourceManager<sf::Int16> soundList;					// https://gist.github.com/eXpl0it3r/c4edb9bcc1f00e29a79b

public:
	Game(std::string filename) : map(filename, START_LOC) { loadGame(); }
	void playGame();

private:
	void loadGame();
	void unloadGame();
	void drawGame();
	void zoomView(sf::Vector2i, int inOut);
	bool moveRobot(int direction);
	void Game::checkRobotDeath();
	void placeRobotOnBoard(sf::Vector2i boardNum, sf::Vector2i tileNum);
	void removeRobotFromBoard(sf::Vector2i boardNum, sf::Vector2i tileNum);

};
#endif // GAME_H
