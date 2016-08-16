// Game Impletementation File

#include "Game.h"

//*************************************************************
//  Load Game
void Game::loadGame() {
	window.create(sf::VideoMode(SCREEN_DIM.x, SCREEN_DIM.y), "RoboRally!");
	//decks.push_back(Deck(PROGRAM_SPRITESHEET, PROGRAM_CARD_LIST, sf::Vector2f(0, 700), DeckType::program)); /////////////  CHANGE POS TO VARIABLE
	//decks.push_back(Deck(PROGRAM_SPRITESHEET, PROGRAM_CARD_LIST, sf::Vector2f(200, 700), DeckType::option)); /////////////  CHANGE POS TO VARIABLE
	//decks[DeckType::option].setColor(sf::Color::Blue);  // only being used to differentiate decks until spritesheets are created
 }

//*************************************************************
//  Unload Game
void Game::unloadGame() {
	window.close();
	map.unloadMap();
	playerList.clear();
	decks.clear();
}

//*************************************************************
//  Game Loop
void Game::playGame() {
	//map.drawMap(window);			//  Debug:  Only Draws Once  : Uncomment Code in each draw function to use
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				//if (decks[0].isTargeted(window))
				//	std::cout << "Deck Clicked" << std::endl;
				if (map.mapTargeted(window))
					std::cout << "Tile Clicked" << std::endl;
				break;
			}
		}
		window.clear();
		drawGame();
		window.display();
	}
}
//*************************************************************
//  Draws all game members
void Game::drawGame() {
	map.drawMap(window);
	for (auto it = decks.begin(); it != decks.end(); ++it)
		it->draw(window);

}