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
	cPlyr->initializeRobot(map.getTilePos({ 1, 0 }, { 2, 9 }), 0); //  will be replaced with "Starting Position Coordinates"
	map.moveRobotToMap(cPlyr->getRobot(), { 1, 0 }, { 2, 9 });
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
	sf::Vector2i mPosNew, mPosOld;
	bool drag = false;
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
						zoomView(sf::Vector2i(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), 1);
					}
				}
				else if (event.key.code == sf::Keyboard::Subtract) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
						zoomView(sf::Vector2i(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), -1);
					}
				}

				//// DEBUGGING AREA
				if (event.key.code == sf::Keyboard::X)
					playerList[0]->resetRobot();


				break;
			case sf::Event::MouseButtonPressed:
				drag = true;
				if (decks[0]->isTargeted(window))
					std::cout << "Deck Clicked" << std::endl;
				if (map.mapTargeted(window)) {
					map.debugDraw(window);
				}
				break;
			case sf::Event::MouseButtonReleased:
				drag = false;
				break;
			case sf::Event::MouseWheelScrolled:
				zoomView(sf::Vector2i((int)event.mouseWheelScroll.x, (int)event.mouseWheelScroll.y), (int)event.mouseWheelScroll.delta);
				break;
			}
		}
		// Check for Robot Death ---- Currently only checks for pits.
		checkRobotDeath();

		if (drag) {
			mPosOld = mPosNew;
			mPosNew = sf::Mouse::getPosition(window);
			view.move((mPosOld.x - mPosNew.x) * view.getSize().x / 1000, (mPosOld.y - mPosNew.y) * view.getSize().y / 1000); // 1000 is a scaling ratio.  To be replaced
			window.setView(view);
		}
		else 
			mPosNew = sf::Mouse::getPosition(window);

		
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
void Game::zoomView(sf::Vector2i pos, int inOut) {
	const sf::Vector2f before = window.mapPixelToCoords(pos);
	view = window.getView();
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

//*************************************************************
//  Sets sprite position of robot and adds it to the 
//  tile at the correct location
void Game::placeRobotOnBoard(sf::Vector2i boardNum, sf::Vector2i tileNum) {
	cPlyr->setRobotPosition(map.getTilePos(boardNum, tileNum), 0);
	map.moveRobotToMap(cPlyr->getRobot(), boardNum, tileNum);
}

//*************************************************************
//  Removes the robot reference from the tile
void Game::removeRobotFromBoard(sf::Vector2i boardNum, sf::Vector2i tileNum)
{
	//cPlyr->setRobotPosition(map.getTilePos(boardNum, tileNum), 0);
	map.removeRobotFromBoard(boardNum, tileNum);
}

//*************************************************************
//  Finds current position and destination position
//  Checks if destination is out of bounds
//  Checks if any tileFeatures on source/destination tiles
//		block movement
bool Game::moveRobot(int direction) {
	sf::Vector2i cBoard, cTile, dBoard, dTile;
	map.getCurrentCoordinates(cPlyr->getRobotPosition(), cBoard, cTile);
	// Checks if destination coordinates exist
	if (!map.getDestinationCoordinates(cBoard, cTile, direction, (int)cPlyr->getRobotOrientation(), dBoard, dTile) &&
		!(map.movementBlocked(direction, cBoard, cTile) || map.movementBlocked(direction >= 180 ? direction - 180 : direction + 180, dBoard, dTile))) {
		std::cout << "OFF BOARD = DEATH\n";
		cPlyr->resetRobot();
		return false;
	}

	// Checks if any current tileFeatures block movement
	if (map.movementBlocked(direction, cBoard, cTile) || map.movementBlocked(direction >= 180 ? direction - 180 : direction + 180, dBoard, dTile))
		return false;
	removeRobotFromBoard(cBoard, cTile);
	placeRobotOnBoard(dBoard, dTile);
	return true;
}

//*************************************************************
//  Checks each robot to see if it's still running
//  Resets them if not.
void Game::checkRobotDeath() {
	sf::Vector2i cBoard, cTile;
	for (auto it = playerList.begin(); it != playerList.end(); ++it) {
		map.getCurrentCoordinates((*it)->getRobotPosition(), cBoard, cTile);
		if (map.causesDeath(cBoard, cTile)) {
			std::cout << "PIT = DEATH\n";
			(*it)->resetRobot();
			removeRobotFromBoard(cBoard, cTile);
			map.getCurrentCoordinates((*it)->getRobotPosition(), cBoard, cTile);
			placeRobotOnBoard(cBoard, cTile);

		}
	}
}