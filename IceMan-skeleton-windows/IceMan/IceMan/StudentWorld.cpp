#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}


//Made the boulders first and stored their cordinates as pairs in a vector so I can check for
//boulders later on when I am making the ice field
int StudentWorld::init() {

	this->iceman = new IceMan(IID_PLAYER, 30, 60, GraphObject::right, 1, 0, this, 10, "player");

	std::vector<std::pair<int, int>> boulderPosition;
	numberOfBoulder = min<unsigned int>(getLevel() / 2 + 2, 9);

	for (int i = 0; i < numberOfBoulder; i++) {
		int randomX = rand() % 64,
			randomY = rand() % 60;
		boulderPosition.push_back({ randomX, randomY });

		Boulder* boulder = new Boulder(IID_BOULDER, randomX, randomY, GraphObject::down, 1, 1, this, "boulder");
		iceField[randomX][randomY] = boulder;
		actionList.push_back(boulder);
	}



	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 60; j++) {

			bool boulderHere = false;
			for (pair<int, int>& pos : boulderPosition) {

				int boulder_x = pos.first;
				int boulder_y = pos.second;

				if (i >= boulder_x && i <= boulder_x + 3 && j >= boulder_y && j <= boulder_y + 3) {
					boulderHere = true;
					break;
				}

			}

			if (i >= 30 && i <= 33 && j > 3) {
				this->iceField[i][j] = nullptr;
			}

			else if (!boulderHere) {
					this->iceField[i][j] = new Ice(IID_ICE, i, j, GraphObject::right, 0.25, 3, this, "ice");
			}

		}
	}

	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
	// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.

	showTextBar();

	if (iceman->isAlive()) {
		iceman->doAction();
	}
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

StudentWorld* StudentWorld::getWorld() {
	return this;
}


// the boulder was defined by its bottom left corner, so I had it check
// the 4x4 area from that corner and define all of it as a boulder
bool StudentWorld::isBoulder(int x, int y) {
	for (Actor* actor : actionList) {
		if (actor != nullptr && actor->getType() == "boulder") {
			int boulder_x = actor -> getX();
			int boulder_y = actor -> getY();
			if (x >= boulder_x && x <= boulder_x + 3 && y >= boulder_y && y <= boulder_y + 3) {
				return true;
			}
		}
	}
	return false;
}
//Also I made boulders as pointers and put the pointers into IceField as well as
//Pushed them into actionList, so that I can access them easily


void StudentWorld::removeIce(int x, int y) {
	if (iceField[x][y] != nullptr && iceField[x][y]->getType() == "ice") {
		delete iceField[x][y];
		iceField[x][y] = nullptr;
	}
}
