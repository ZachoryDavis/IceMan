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
			Gold* gold = new Gold(IID_GOLD, randomX, randomY, GraphObject::right, 1, 2, this, "gold", true, false, true, false);

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

	//int goodie = getLevel() * 30 + 290;

	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
	// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.

	showTextBar();

	int T = max(25, 200 - currentLevelNumber);
	int maxNumberOfProtestor = min(15, static_cast<int>(2 + currentLevelNumber * 1.5));
	int probabilityOfHardcore = min(90, currentLevelNumber * 30 + 290);

	//ticks++;


	//******************************
	//The stuff above is for the stuff below that's currently commented out because none of it works!!!!
	//No idea what I'm doing wrong, internet says its something to do with protestor cpp functions not matching
	//the .h functions idk I gave up on it for now
	//******************************


	if (ticks >= T && numberOfProtestor < maxNumberOfProtestor) {
		// Decide protestor type
		int randVal = rand() % 100;
		Actor* newProtestor = nullptr;
		if (randVal < probabilityOfHardcore) {
			// Spawn HardcoreProtestor
			newProtestor = new HardcoreProtestor(IID_HARD_CORE_PROTESTER, 60, 60, GraphObject::left, 1.0, 0, this, 20, "hardcoreprotestor");
		}
		else {
			// Spawn RegularProtestor
			newProtestor = new RegularProtestor(IID_PROTESTER, 60, 60, GraphObject::left, 1.0, 0, this, 5, "protestor");
		}
		actionList.push_back(newProtestor);
		//ticks = 0;
	}

	int numberOfProtesters;
	for (Actor* actor : actionList) {
		if (actor && (actor->getType() == "protestor" || actor->getType() == "hardcoreprotestor") && actor->isAlive())
			numberOfProtestor++;
	}

	spawnTickUnits();
	//can put tickvalue inside sw that is incremented everytime this is called, can use modulus to calculate when gold/protestor should be spawned
	if (iceman != nullptr && iceman->isAlive()) {
		iceman->doAction();
	}

	for (int i = 0; i < actionList.size(); i++) {
		if (actionList[i]->isAlive()) {
			actionList[i]->doAction();
		}
	}

	for (int i = 0; i < actionList.size(); ) {
		if (actionList[i] && !actionList[i]->isAlive()) {
			delete actionList[i];
			actionList.erase(actionList.begin() + i);
		}
		else {
			i++;
		}
	}
	increaseTicks();

	//decLives();
	//return GWSTATUS_PLAYER_DIED;

	if (numberOfOil == 0) {
		playSound(SOUND_FINISHED_LEVEL);
		return GWSTATUS_FINISHED_LEVEL;
	}
	if (this->iceman->isAlive()) {
		return GWSTATUS_CONTINUE_GAME;
	}
	else {
		return GWSTATUS_PLAYER_DIED;

	}

}

void StudentWorld::cleanUp() {

	if (iceman->isAlive()) {
		delete iceman;
		iceman = nullptr;
	}

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 60; j++) {
			if (iceField[i][j] != nullptr && iceField[i][j]->getType() == "ice") {
				delete iceField[i][j];
				iceField[i][j] = nullptr;
				//cout << i << " " << j << endl;
			}
		}
	}


	for (size_t i = 0; i < actionList.size(); ++i) {
		delete actionList[i];
		actionList[i] = nullptr;
	}
	actionList.clear();
	//for (int i = 0; i < actionList.size(); i++) {
	//	if (actionList[i] != nullptr) {
	//		delete actionList[i];
	//		actionList[i] = nullptr;
	//	}
	//}
}

void StudentWorld::showTextBar() {

	//FIX THIS LOOK AT REQUIREMENTS IN PAGE 22
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
		" Score: " + std::to_string(score) +
		//remove line below after testing
		" Ticks: " + std::to_string(getTicks());

	setGameStatText(text);
}

StudentWorld* StudentWorld::getWorld() {
	return this;
}


bool StudentWorld::itemMoveUp(int x, int y) {
	bool canMove = false;
	for (int i = x; i < x + 4; i++)
	{
		if (y < 60)
		{
			if (iceField[i][y + 4] == nullptr)
				canMove = true;
			else
				return false;
		}
		else
			return false;

		if (isBoulder(x, y + 1))
			return false;
	}
	return canMove;
}


bool StudentWorld::itemMoveDown(int x, int y)
{
	bool canMove = false;
	for (int i = x; i < x + 4; i++)
	{
		if (y > 0)
		{
			if (iceField[i][y - 1] == nullptr)
				canMove = true;
			else
				return false;

			if (isBoulder(x, y - 1))
				return false;
		}
		else
			return false;
	}
	return canMove;
}


bool StudentWorld::itemMoveLeft(int x, int y)
{
	bool canMove = false;
	for (int j = y; j < y + 4; j++)
	{
		if (x > 0)
		{
			if (iceField[x - 1][j] == nullptr)
				canMove = true;
			else
				return false;
		}
		else
			return false;

		if (isBoulder(x - 1, y))
			return false;

	}
	return canMove;
}


bool StudentWorld::itemMoveRight(int x, int y)
{
	bool canMove = false;
	for (int j = y; j < y + 4; j++)
	{
		if (x < 60)
		{
			if (iceField[x + 4][j] == nullptr)
				canMove = true;
			else
				return false;
		}
		else
			return false;

		if (isBoulder(x + 1, y))
			return false;
	}
	return canMove;
}


bool StudentWorld::atIntersection(int x, int y) {
	int numberWays = 0;
	if (itemMoveUp(x, y) || itemMoveDown(x, y))
		numberWays++;
	if (itemMoveRight(x, y) || itemMoveLeft(x, y))
		numberWays++;
	if (numberWays > 1)
		return true;
	else return false;
}


// the boulder was defined by its bottom left corner, so I had it check
// the 4x4 area from that corner and define all of it as a boulder
bool StudentWorld::isBoulder(int x, int y) {
	for (Actor* actor : actionList) {
		if (actor != nullptr && actor->getType() == "boulder") {
			int boulder_x = actor->getX();
			int boulder_y = actor->getY();
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

		if (iceField[x + i][y - 1] != nullptr) { //Checks for ice below
			noIceBelow = false;
			break;
		}

		if (isBoulder(x + i, y - 1)) { //Checks for boulders below
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


bool StudentWorld::isIce(int x, int y) {
	if (x < 0 || x >= 64 || y < 0 || y >= 60) {
		return false; // Out of bounds
	}
	return (iceField[x][y] != nullptr && iceField[x][y]->getType() == "ice");
}


bool StudentWorld::sonarSearch(int x, int y) {

	playSound(SOUND_SONAR);
	int radius = 12;
	bool found = false;

	for (Actor* actor : actionList) {
		if (actor == nullptr)
			continue;
		string actorType = actor->getType();
		if (actorType == "gold" || actorType == "oilbarrel") {
			int actorX = actor->getX();
			int actorY = actor->getY();

			if (actorX >= x - radius && actorX <= x + radius && actorY >= y - radius && actorY <= y + radius) {
				actor->setVisible(true);
				found = true;
			}

		}
	}

	return found;
}


bool StudentWorld::fireSquirt(int x, int y, GraphObject::Direction dir) {
	if (iceman->getNumberOfSquirts() <= 0) {
		return false; // No squirts left
	}
	// Create a new Squirt actor
	Squirt* squirt = new Squirt(IID_WATER_SPURT, x, y, dir, 1, 2, this, "squirt");
	actionList.push_back(squirt);
	//iceman->decreaseSquirts(); // Decrease the number of squirts
	playSound(SOUND_PLAYER_SQUIRT);
	return true;
}


bool StudentWorld::overlap(std::pair<int, int> coords) {
	for (int i = 0; i < actionList.size(); i++) {
		if (actionList[i] != nullptr && (coords.first == actionList[i]->getX() && coords.second == actionList[i]->getY())) {
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

void StudentWorld::spawnTickUnits() {
	int goodie = getLevel() * 30 + 290;
	int goodieChance = rand() % goodie;

	//this works but it took like 2 min for anything to spawn?????

	//this looks so disgusting wtf did i write

	//check for the 1/goodieChance chance that a goodie is spawned
	//if (rand() % goodieChance == 0) {

	if (goodieChance == 0 && !overlap({ 0, 59 })) { // 1/5 chance that sonar is spawned
		//playSound(SOUND_DIG);
		Sonar* sonar = new Sonar(IID_SONAR, 0, 59, GraphObject::right, 1, 2, this, "sonar");
		actionList.push_back(sonar);
	}
	else {				  // 4/5 chance water is spawned
		int waterX = rand() % 64,
			waterY = rand() % 60;
		// check for requirement that water cannot spawn in blocked spots 
		if (canAddWater(waterX, waterY) && !overlap({ waterX, waterY })) {

			Water* water = new Water(IID_WATER_POOL, waterX, waterY, GraphObject::right, 1, 2, this, "water", false);
			actionList.push_back(water);
		}
	}
	//}
}


bool StudentWorld::canAddWater(int x, int y) {
	if (x < 0 || x + 3 >= 64 || y < 0 || y + 3 >= 60)
		return false;

	for (int i = x; i < x + 4; i++) {
		for (int j = y; j < y + 4; j++) {
			if (iceField[i][j] != nullptr) {
				return false;
			}
		}
	}
	return true;
}