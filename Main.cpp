//  Robo Rally Game
//  Need to get License Info
//  Jamie and Jordan

#include "Game.h"

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

int main() {

	Game game("robotstew.csv");

	//game.printGame();		//for bug checking Tile and TileFeature private member variables
							//Game, Map and Board habe printXxxx() functions to reach printTile() function

	game.playGame();


	GLOBAL::textureList.unloadAllResources();
	#ifdef _MSC_VER
		printf(_CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
	#endif

	return 0;
}