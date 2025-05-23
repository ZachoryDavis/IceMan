#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init() {

	this->iceman = new IceMan(IID_PLAYER, 30, 60, GraphObject::right, 1, 0, this, 10);

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 60; j++) {
			if (i >= 30 && i <= 33 && j > 3) {

			}
			else {
				this->iceField[i][j] = new Ice(IID_ICE, i, j, GraphObject::right, 0.25, 3, this);
			}
		}
	}

	numberOfBoulder = min(currentLevelNumber / 2 + 2, 9);
	for (int i = 0; i < numberOfBoulder; i++) {

	}

	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
	// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.

	showTextBar();

	//decLives();
	//return GWSTATUS_PLAYER_DIED;
	return 9;
}

void StudentWorld::cleanUp() {

}

void StudentWorld::showTextBar() {
	int level = getLevel(),
		lives = getLives(),
		health = iceman->getHealth(),
		squirts = iceman->getNumberOfSquirts(),
		gold = iceman->getNumberOfGold(),
		oilLeftOnField = numberOfOil - 1, //fix this
		sonar = iceman->getNumberOfSonar(),
		score = 000000; //fix this

	string text = "Level: " + std::to_string(level) +
		" Lives: " + std::to_string(lives) +
		" Health: " + std::to_string(health) +
		" Water: " + std::to_string(squirts) +
		" Gold: " + std::to_string(gold) +
		" Oil Left: " + std::to_string(oilLeftOnField) +
		" Sonar: " + std::to_string(sonar) +
		" Score: " + std::to_string(score);

	setGameStatText(text);
}