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

const int NUM_PHASES = 3;
enum Phase { codePhase = 0, movePhase = 1, endOfTurnPhase = 2 };

const int NUM_FLAGS = 4;
enum flagTypes
{
	phaseSetupComplete,				//  Flag:  Phase Setup Complete
	phaseComplete,					//  Flag:  Phase Complete
	actRobot,						//  Flag:  Robot Activated
	actBoard						//  Flag:  Board Activated

};

#define PROGRAM_CARD_LIST "ProgramList.txt"
#define PROGRAM_SPRITESHEET "ProgramSpriteSheet.png"
#define OPTION_CARD_LIST "OptionList.txt"
#define OPTION_SPRITESHEET "OptionSpriteSheet.png"

const sf::Vector2f START_LOC = { 75, 75 }; ////////////  For Now
const sf::Vector2i SCREEN_DIM = { 800, 800 };
const float MIN_ZOOM = 300;
const float MAX_ZOOM = 5000;
const float ZOOM_QTY = .9f;
const float DELAY = 4000;

class Game {
	sf::RenderWindow window;
	sf::View view;
	sf::Clock clock;
	float cTime;
	Map map;
	Player *cPlyr;
	std::vector<Player*> playerList;
	std::vector<Deck*> decks;
	int cPhase;
	int cRegPhase;
	bool flag[NUM_FLAGS];									//  Hold an array of flags for game decisions	
	ResourceManager<sf::Font> fontList;
	ResourceManager<sf::Int16> soundList;					// https://gist.github.com/eXpl0it3r/c4edb9bcc1f00e29a79b

public:
	Game(std::string filename) : map(filename, START_LOC) { loadGame(); }
	void playGame();

private:
	void loadGame();
	void unloadGame();
	void phaseSetup();
	void endPhase();
	void drawGame();
	void zoomView(sf::Vector2i, int inOut);
	bool moveRobot(Player *plyr, int direction);
	void checkRobotDeath();
	void checkRobotDamaged();
	void addRobotToPlay(sf::Vector2i desBoard, sf::Vector2i desTile);
	void repositionRobot(sf::Vector2i desBoard, sf::Vector2i desTile, sf::Vector2i curBoard, sf::Vector2i curTile);
	void removeRobotFromPlay(sf::Vector2i boardNum, sf::Vector2i tileNum);
	void activateBoard();

};
#endif // GAME_H
