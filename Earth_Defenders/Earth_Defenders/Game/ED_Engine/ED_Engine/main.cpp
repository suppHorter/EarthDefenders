// To delete:
#include <stdlib.h>     //for using the function sleep
// To delete-

#include "Engine.h"
#include "EngineInitConfig.h"
#include "RandomNumberGenerator.cpp"

int main() {
	EngineInitConfig engineConfig = EngineInitConfig();
	// Falls nix im EPROM
	int rngSeed = engineConfig.engineStartSeed;
	// Falls im EPROM !engineConfig.engineStartSeed
	// int rngSeed = readEPROM();
	RandomNumberGenerator rng = RandomNumberGenerator();
	rng.setSeed(rngSeed);

	Engine gameEngine = Engine(rng);
	gameEngine.startGame();


	while(1) {
		gameEngine.calculateNextView();
		gameEngine.renderView();
		_sleep(1000);
	}


	getchar();
	getchar();
}