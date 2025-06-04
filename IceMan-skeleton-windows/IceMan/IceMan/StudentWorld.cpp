#include "StudentWorld.h"
#include <string>
#include <algorithm>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}


//Made the boulders first and stored their cordinates as pairs in a vector so I can check for
//boulders later on when I am making the ice field
int StudentWorld::init() {

	this->iceman = new IceMan(IID_PLAYER, 30, 60, GraphObject::right, 1, 0, this, 10, "player");
	//actionList.push_back(iceman);

	std::vector<std::pair<int, int>> boulderPosition;
	numberOfBoulder = min<unsigned int>(getLevel() / 2 + 2, 9);
	numberOfGold = max<unsigned int>(5 - getLevel() / 2, 2);
	numberOfOil = min<unsigned int>(2 + getLevel(), 21);

	for (int i = 0; i < numberOfBoulder; i++) {
		int randomX = rand() % 64,
			randomY = rand() % 60;
		if (!overlap({ randomX, randomY })) {
			boulderPosition.push_back({ randomX, randomY });


			Boulder* boulder = new Boulder(IID_BOULDER, randomX, randomY, GraphObject::down, 1, 1, this, "boulder");
			//iceField[randomX][randomY] = boulder;
			actionList.push_back(boulder);
		}
		else {
			i--;
		}

		Boulder* boulder = new Boulder(IID_BOULDER, randomX, randomY, GraphObject::down, 1, 1, this, "boulder");
		//iceField[randomX][randomY] = boulder;
		actionList.push_back(boulder);
	}

	for (int i = 0; i < numberOfOil; i++) {
		int randomX = rand() % 64,
			randomY = rand() % 60;
		if (!overlap({ randomX, randomY })) {
			OilBarrel* oil = new OilBarrel(IID_BARREL, randomX, randomY, GraphObject::right, 1, 2, this, "oil");

			//iceField[randomX][randomY] = oil;
			actionList.push_back(oil);
		}
		else {
			i--;
		}
	}

	for (int i = 0; i < numberOfGold; i++) {
		int randomX = rand() % 64,
			randomY = rand() % 60;
		if (!overlap({ randomX, randomY })) {
			Gold* gold = new Gold(IID_GOLD, randomX, randomY, GraphObject::right, 1, 2, this, "gold", true, false, true);

			//iceField[randomX][randomY] = gold;
			actionList.push_back(gold);
		}
	}

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 60; j++) {

			bool boulderHere = false;
			for (pair<int, int>& pos : boulderPosition) {

				int boulder_x = pos.first;
				int boulder_y = pos.second;

				if (i >= boulder_x && i <= boulder_x + 3 && j >= boulder_y && j <= boulder_y + 3) {
					boulderHere = true;
					//break;
					this->iceField[i][j] = nullptr;

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

	for (int i = 0; i < actionList.size(); i++) {
		if (actionList[i]->isAlive()) {
			actionList[i]->doAction();
		}
	}

	//decLives();
	//return GWSTATUS_PLAYER_DIED;

	return 9;
}

void StudentWorld::cleanUp() {

	//READ ACCESS VIOLATION INSIDE FIRST FOR LOOP DELEITNG ICE

	if (iceman->isAlive()) {
		delete iceman;
		iceman = nullptr;
	}


	// its trying to access something that is null, but shouldnt the nullptr check and ice check handle this????
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 60; j++) {
			if (iceField[i][j] != nullptr && iceField[i][j]->getType() == "ice") {
				delete iceField[i][j];
				iceField[i][j] = nullptr;
				cout << i << " " << j << endl;
			}
		}
	}

}

void StudentWorld::showTextBar() {
	IceMan* iceman = getIceMan();

	int level = getLevel(),
		lives = getLives(),
		health = iceman->getHealth(),
		squirts = iceman->getNumberOfSquirts(),
		gold = iceman->getNumberOfGold(),
		oilLeftOnField = numberOfOil,
		sonar = iceman->getNumberOfSonar(),
		score = getScore(); 

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


bool StudentWorld::belowBoulder(int x, int y) {
	bool noIceBelow = true;

	for (int i = 0; i < 4; i++) {

		if (iceField[x + i][y - 1] != nullptr) {
			noIceBelow = false;
			break;
		}

		if (isBoulder(x + i, y - 1)) {
			noIceBelow = false;
			break;
		}
	}

	return noIceBelow;
}


void StudentWorld::removeIce(int x, int y) {
	if (iceField[x][y] != nullptr && iceField[x][y]->getType() == "ice") {
		delete iceField[x][y];
		iceField[x][y] = nullptr;
		playSound(SOUND_DIG);
	}
}

bool StudentWorld::overlap(std::pair<int, int> coords) {
	for (int i = 0; i < actionList.size(); i++) {
		if (coords.first == actionList[i]->getX() && coords.second == actionList[i]->getY()) {
			return true;
		}
	}
	return false;
}

std::vector<Actor*> StudentWorld::getList() {
	return this->actionList;
}

IceMan* StudentWorld::getIceMan() {
	return this->iceman;
}

void StudentWorld::decreaseOil() {
	this->numberOfOil--;
}

void StudentWorld::decreaseGold() {
	this->numberOfGold--;
}