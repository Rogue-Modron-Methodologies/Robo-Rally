// Game Impletementation File

#include "Game.h"

//*************************************************************
//  Load Game
void Game::loadGame() {
	window.create(sf::VideoMode(SCREEN_DIM.x, SCREEN_DIM.y), "RoboRally!");
	view.reset(sf::FloatRect(0, 0, SCREEN_DIM.x * 3.f, SCREEN_DIM.y * 3.f));
	window.setView(view);
	cPhase = program;
	playerList.push_back(new Player("Twonky"));
	cPlyr = playerList[0];
	cPlyr->initializeRobot(map.getTilePos({ 1, 0 }, { 2, 9 }), 0); //  will be replaced with "Starting Position Coordinates"
	map.addRobotToPlay(cPlyr->getRobot(), { 1, 0 }, { 2, 9 });
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
	bool drag = false, timerActive = false;
	sf::Event event;
	cTime = 0;
	while (window.isOpen()) {
		if (timerActive) 
			cTime += clock.getElapsedTime().asSeconds();
		if (!flag[phaseSetupComplete])
			phaseSetup();
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (cPhase)
				{
				case movePhase:
					if (flag[actRobot]) {
						switch (event.key.code)
						{
						case sf::Keyboard::Up:
							moveRobot(cPlyr, up);
							timerActive = true;
							break;
						case sf::Keyboard::Down:
							moveRobot(cPlyr, down);
							timerActive = true;
							break;
						case sf::Keyboard::Left:
							moveRobot(cPlyr, left);
							timerActive = true;
							break;
						case sf::Keyboard::Right:
							moveRobot(cPlyr, right);
							timerActive = true;
							break;
						}
					}
					break;
				}
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
				if (event.key.code == sf::Keyboard::X) {
					switch (cPhase)
					{

					case movePhase:
						if (cRegPhase <= 4) {
							flag[actBoard] = true;
						}
						else {
							cRegPhase = 0;
							flag[actRobot] = false;
							flag[actBoard] = false;
							flag[phaseComplete] = true;
						}
						break;
					case codePhase:
					case endOfTurnPhase:
						flag[phaseComplete] = true;
					}
				}
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

		if (drag) {
			mPosOld = mPosNew;
			mPosNew = sf::Mouse::getPosition(window);
			view.move((mPosOld.x - mPosNew.x) * view.getSize().x / 1000, (mPosOld.y - mPosNew.y) * view.getSize().y / 1000); // 1000 is a scaling ratio.  To be replaced
			window.setView(view);
		}
		else 
			mPosNew = sf::Mouse::getPosition(window);

		if (flag[actBoard] && cTime >= DELAY) {
			activateBoard();
			checkRobotDeath();
			cTime = 0;
			timerActive = false;
		}

		if (flag[phaseComplete])
			endPhase();
		
		window.clear();
		drawGame();
		window.display();
	}
}

//*************************************************************
//  inital phase setup
//
void Game::phaseSetup() {
	sf::Vector2i cBoard, cTile;
	flag[phaseComplete] = false;
	flag[actRobot] = false;
	flag[actBoard] = false;
	switch (cPhase)
	{
	case codePhase:
		std::cout << "Programming Phase Start:\n";
		std::cout << "Robots are back in Play\n";
		for (auto it = playerList.begin(); it != playerList.end(); ++it) {
			if ((*it)->getRobot().isOutOfPlay()) {
				std::cout << (*it)->getRobot().getName() << " : Coming OnLine\n";
				(*it)->resetRobot();
				map.getCurrentCoordinates((*it)->getRobotPosition(), cBoard, cTile);
				map.addRobotToPlay(cPlyr->getRobot(), cBoard, cTile);
			}
			std::cout << "Heal Powered Down Robots\n";
			std::cout << "Deal Cards / Program Bots / Program Options / Announce Power Down\n\n";
		}
		break;
	case movePhase:
		std::cout << "Robot/Board Movement Start:\n\n";
		flag[actRobot] = true;
		break;
	case endOfTurnPhase:
		std::cout << "End of Turn Effects:\n\n";
		break;
	}
	flag[phaseSetupComplete] = true;
}

//*************************************************************
//  sets cPhase to next phase, checks for end of phases
//  and sets back to beginning
void Game::endPhase() {
	switch (cPhase)
	{
	case codePhase:

		break;
	case movePhase:

		break;
	case endOfTurnPhase:

		break;
	}
	cPhase++;
	if (cPhase == NUM_PHASES)
		cPhase = 0;
	flag[phaseComplete] = false;
	flag[phaseSetupComplete] = false;
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
void Game::addRobotToPlay(sf::Vector2i desBoard, sf::Vector2i desTile) {
	cPlyr->setRobotPosition(map.getTilePos(desBoard, desTile), 0);
	map.addRobotToPlay(cPlyr->getRobot(), desBoard, desTile);
}

//*************************************************************
//  Sets sprite position of robot and adds it to the 
//  tile at the correct location also removes robot from 
//  current tile
void Game::repositionRobot(sf::Vector2i desBoard, sf::Vector2i desTile, sf::Vector2i curBoard, sf::Vector2i curTile) {
	cPlyr->setRobotPosition(map.getTilePos(desBoard, desTile), (int)cPlyr->getRobotOrientation());
	map.repositionRobot(cPlyr->getRobot(), desBoard, desTile, curBoard, curTile);
}

//*************************************************************
//  Removes the robot reference from the tile
void Game::removeRobotFromPlay(sf::Vector2i boardNum, sf::Vector2i tileNum)
{
	map.removeRobotFromPlay(boardNum, tileNum);
	cPlyr->removeRobotFromPlay();
}

//*************************************************************
//  Finds current position and destination position
//  Checks if destination is out of bounds
//  Checks if any tileFeatures on source/destination tiles
//		block movement
bool Game::moveRobot(Player *plyr, int direction) {
	std::cout << "Trying to move " << direction << "...";
	flag[actRobot] = false;
	flag[actBoard] = true;
	sf::Vector2i cBoard, cTile, dBoard, dTile;
	if (plyr->getRobot().isOutOfPlay())
		return false;
	map.getCurrentCoordinates(plyr->getRobotPosition(), cBoard, cTile);
	map.getDestinationCoordinates(cBoard, cTile, direction, (int)plyr->getRobotOrientation(), dBoard, dTile);
	const Tile *curTile = map.getTile(cBoard, cTile);
	const Tile *desTile = map.getTile(dBoard, dTile);

	// Checks if destination coordinates exist
	if (!map.getDestinationCoordinates(cBoard, cTile, direction, (int)plyr->getRobotOrientation(), dBoard, dTile) &&
		!(curTile->movementBlocked(direction) || desTile->movementBlocked(direction >= 180 ? direction - 180 : direction + 180))) {
		std::cout << "OFF BOARD = DEATH\n";
		removeRobotFromPlay(cBoard, cTile);
		return false;
	}

	// Checks if any current tileFeatures block movement
	if (curTile->movementBlocked(direction) || desTile->movementBlocked(direction >= 180 ? direction - 180 : direction + 180)) {
		std::cout << " blocked\n";
		return false;
	}

	repositionRobot(dBoard, dTile, cBoard, cTile);
	std::cout << " success!\n";
	return true;
}

//*************************************************************
//  Checks each robot to see if it's still running
//  Resets them if not.
void Game::checkRobotDeath() {
	sf::Vector2i cBoard, cTile;
	const Tile *curTile;
	for (auto it = playerList.begin(); it != playerList.end(); ++it) {
		map.getCurrentCoordinates((*it)->getRobotPosition(), cBoard, cTile);
		curTile = map.getTile(cBoard, cTile);
		if(curTile->causesDeath()) {
			std::cout << "PIT = DEATH\n";
			removeRobotFromPlay(cBoard, cTile);
		}
		if ((*it)->getRobot().getDamage() >= DEATH_HP) {
			std::cout << "DEATH BY DAMAGE\n";
			removeRobotFromPlay(cBoard, cTile);
		}
	}
}

//*************************************************************
//  Activate the Board Elements that the Robots are on.
//  
void Game::activateBoard() {
	std::cout << "BOARD ACTIVE: ";
	sf::Vector2i cBoard, cTile;
	int qty = 0, orientation = 0;
	const Tile *curTile;
	// Express Conveyors
	for (auto plyr = playerList.begin(); plyr != playerList.end(); ++plyr) {
		map.getCurrentCoordinates((*plyr)->getRobotPosition(), cBoard, cTile);
		curTile = map.getTile(cBoard, cTile);
		if (curTile->movesRobot(qty, orientation) && qty > 1) {
			moveRobot((*plyr), orientation);
			if (curTile->rotatesRobot(orientation))
				(*plyr)->rotateRobot(orientation);
		}

	}
	// Regular Conveyors
	for (auto plyr = playerList.begin(); plyr != playerList.end(); ++plyr) {
		map.getCurrentCoordinates((*plyr)->getRobotPosition(), cBoard, cTile);
		curTile = map.getTile(cBoard, cTile);
		if (curTile->movesRobot(qty, orientation)) {
			moveRobot((*plyr), orientation);
			if (curTile->rotatesRobot(orientation))
				(*plyr)->rotateRobot(orientation);
		}
	}
	// Pushers  //////////////////////////  Need to implement

	//// Gears
	//for (auto plyr = playerList.begin(); plyr != playerList.end(); ++plyr) {
	//	map.getCurrentCoordinates((*plyr)->getRobotPosition(), cBoard, cTile);
	//	curTile = map.getTile(cBoard, cTile);
	//	if (curTile->rotatesRobot(orientation))
	//		(*plyr)->rotateRobot(orientation);
	//}
	// Robot and Board Lasers Fire  ////////////////////////////////// Still need to implement robot lasers
	for (auto it = playerList.begin(); it != playerList.end(); ++it) {
		map.getCurrentCoordinates((*it)->getRobotPosition(), cBoard, cTile);
		curTile = map.getTile(cBoard, cTile);
		if (curTile->causesDamage(qty)) {
			std::cout << "ZAAP!!! " << qty << " damage!\n";
			(*it)->damageRobot(qty);
		}
	}
	// Robots touch flags     //////////////////////////  Need to implement

		cRegPhase++;
		std::cout << "Register Phase #" << cRegPhase << std::endl;
	if (cRegPhase <= 4) {
		flag[actRobot] = true;
	}
	else {
		cRegPhase = 0;
		flag[actRobot] = false;
		flag[phaseComplete] = true;
	}
	flag[actBoard] = false;
}