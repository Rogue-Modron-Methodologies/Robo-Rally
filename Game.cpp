// Game Impletementation File

#include "Game.h"

//*************************************************************
//  Load Game
void Game::loadGame() {
	window.create(sf::VideoMode(SCREEN_DIM.x, SCREEN_DIM.y), "RoboRally!");
	view.reset(sf::FloatRect(0, 0, SCREEN_DIM.x * 3.f, SCREEN_DIM.y * 3.f));
	window.setView(view);
	playerList.push_back(new Player("Twonky"));
	cPlyr = playerList[0];
	placeRobotOnBoard({ 1, 0 }, { 2, 9 });  //  will be replaced with "Starting Position Coordinates"
	decks.push_back(new Deck(PROGRAM_SPRITESHEET, PROGRAM_CARD_LIST, sf::Vector2f(2000, 100), DeckType::program)); /////////////  CHANGE POS TO VARIABLE
	//decks.push_back(Deck(PROGRAM_SPRITESHEET, PROGRAM_CARD_LIST, sf::Vector2f(200, 700), DeckType::option)); /////////////  CHANGE POS TO VARIABLE
	//decks[DeckType::option].setColor(sf::Color::Blue);  // only being used to differentiate decks until spritesheets are created
 }

//*************************************************************
//  Unload Game
void Game::unloadGame() {
	window.close();
	map.unloadMap();
	playerList.clear();
	for (unsigned i = 0; i < decks.size(); ++i)
		delete decks[i];
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
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Up)
					moveRobot(up);
				else if (event.key.code == sf::Keyboard::Down)
					moveRobot(down);
				else if (event.key.code == sf::Keyboard::Left)
					moveRobot(left);
				else if (event.key.code == sf::Keyboard::Right)
					moveRobot(right);

				if (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Numpad0) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
						view.reset(sf::FloatRect(0, 0, SCREEN_DIM.x * 3.f, SCREEN_DIM.y * 3.f));
						window.setView(view);
					}
				}
				else if (event.key.code == sf::Keyboard::Add) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
						zoomView(sf::Vector2i(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), window, 1);
					}
				}
				else if (event.key.code == sf::Keyboard::Subtract) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
						zoomView(sf::Vector2i(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), window, -1);
					}
				}

				//// DEBUGGING AREA
				if (event.key.code == sf::Keyboard::X)
					playerList[0]->resetRobot();


				break;
			case sf::Event::MouseButtonPressed:

				if (decks[0]->isTargeted(window))
					std::cout << "Deck Clicked" << std::endl;
				if (map.mapTargeted(window)) {
					map.debugDraw(window);
				}

				break;
			case sf::Event::MouseWheelScrolled:
				if (event.mouseWheelScroll.delta)
					zoomView(sf::Vector2i((int)event.mouseWheelScroll.x, (int)event.mouseWheelScroll.y), window, (int)event.mouseWheelScroll.delta);
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
		(*it)->draw(window);
	for (auto it = playerList.begin(); it != playerList.end(); ++it)
		(*it)->drawPlayer(window);

}

//*************************************************************
//	zooms in or out focused on where mouse position is
//  will only zoom in or out up to a max value 
void Game::zoomView(sf::Vector2i pos, sf::RenderWindow& window, int inOut) {
	const sf::Vector2f before = window.mapPixelToCoords(pos);
	sf::View view = window.getView();
	inOut > 0 ? view.zoom(ZOOM_QTY) : view.zoom(1 / ZOOM_QTY);
	window.setView(view);

	if (window.getView().getSize().x > MAX_ZOOM) {
		view.setSize(MAX_ZOOM, MAX_ZOOM);
		window.setView(view);
	}
	else if (window.getView().getSize().x < MIN_ZOOM) {
		view.setSize(MIN_ZOOM, MIN_ZOOM);
		window.setView(view);
	}

	const sf::Vector2f after = window.mapPixelToCoords(pos);
	const sf::Vector2f offset = before - after;
	view.move(offset);
	window.setView(view);
}

void Game::placeRobotOnBoard(sf::Vector2i boardNum, sf::Vector2i tileNum) {
	cPlyr->setRobotPosition(map.getTilePos(boardNum, tileNum), 0);
	map.moveRobotToMap(cPlyr->getRobot(), boardNum, tileNum);
}

void Game::removeRobotFromBoard(sf::Vector2i boardNum, sf::Vector2i tileNum)
{
	//cPlyr->setRobotPosition(map.getTilePos(boardNum, tileNum), 0);
	map.removeRobotFromMap(boardNum, tileNum);
}

bool Game::moveRobot(int direction) {
	sf::Vector2i cboard, ctile;
	sf::Vector2f rPos = cPlyr->getRobotPosition();
	map.getTileCoordinates(rPos, cboard, ctile);
	std::cout << "Board " << cboard.x << " " << cboard.y << " Tile " << ctile.x << " " << ctile.y << std::endl;
	// IF move isn't possible ---> return false

	//removeRobotFromBoard(playerNum, boardNum, tileNum);
	// If move is on same board
	// placeRobotOnBoard(int playerNum, sf::Vector2i boardNum, sf::Vector2i tileNum)    NEW LOCATION ON SAME BOARD
	// If move goes to new board
	// placeRobotOnBoard(int playerNum, sf::Vector2i boardNum, sf::Vector2i tileNum)    NEW LOCATION ON NEW BOARD
	// Check for robot death


	return true;
}
