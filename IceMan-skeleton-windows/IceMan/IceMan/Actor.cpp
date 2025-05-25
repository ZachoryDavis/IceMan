
#include "Actor.h"
#include "StudentWorld.h"


Actor::Actor(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type)
	: GraphObject(imageID, startX, startY, startingDirection, size, depth), type(type) {
	this->studentWorld = studentWorld;
	this->alive = true;
}

Actor::~Actor() {
	//TODO: IMPLEMENT
}

bool Actor::isAlive() {
	return alive;
}

StudentWorld* Actor::getWorld() {
	return this->studentWorld;
}

std::string Actor::getType() {
	if (this->type != "")
		return this->type;
	else
		return ""; //default variable for when the cell is empty, the program doesnt try to return a null value
}

Human::Human(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health, std::string type)
    : Actor(imageID, startX, startY, startingDirection, size, depth, studentWorld, type) {
    this->health = health;
}

Human::~Human() {
	//TODO: IMPLEMENT
}

void Human::setHealth(int health) {
	this->health = health;
}

int Human::getHealth() {
	return this->health;
}

//====================================================================================================================================
IceMan::IceMan(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health, std::string type)
	: Human(imageID, startX, startY, startingDirection, size, depth, studentWorld, health, type) {
	setHealth(10);
	this->numberOfSquirts = 5;
	this->numberOfSonarKits = 1;
	this->numberOfGoldNuggets = 0;
	setVisible(true);
}

IceMan::~IceMan() {
	//TODO: IMPLEMENT
}

void IceMan::setNumberOfSquirts(int squirts) {
	this->numberOfSquirts = squirts;
}

int IceMan::getNumberOfSquirts() {
	return this->numberOfSquirts;
}

void IceMan::setNumberOfSonar(int sonar) {
	this->numberOfSonarKits = sonar;
}

int IceMan::getNumberOfSonar() {
	return this->numberOfSonarKits;
}

void IceMan::setNumberOfGold(int gold) {
	this->numberOfGoldNuggets = gold;
}
int IceMan::getNumberOfGold() {
	return this->numberOfGoldNuggets;
}

void IceMan::doAction() {
	int keyPress;
	StudentWorld* thisWorld = getWorld();

	if (thisWorld->getKey(keyPress)) {
		switch (keyPress)
		{
		case KEY_PRESS_LEFT:
			if (getDirection() != left) {
				this->setDirection(left);
			}
			if (getX() >= 1 && !thisWorld->isBoulder(getX() - 1, getY())) {
				moveTo(getX() - 1, getY());
			}
			break;
			
		case KEY_PRESS_RIGHT:
			if (getDirection() != right) {
				this->setDirection(right);
			}

			if (getX() <= 59 && !thisWorld->isBoulder(getX() + 1, getY())) {
				moveTo(getX() + 1, getY());
			}

			break;

		case KEY_PRESS_UP:
			if (getDirection() != up) {
				this->setDirection(up);
			}

			if (getY() <= 59 && !thisWorld->isBoulder(getX(), getY() + 1)) {
				moveTo(getX(), getY() + 1);
			}
			break;

		case KEY_PRESS_DOWN:
			if (getDirection() != down) {
				this->setDirection(down);
			}

			if (getY() >= 1 && !thisWorld->isBoulder(getX(), getY() - 1)) {
				moveTo(getX(), getY() - 1);
			}
			break;

		default:
			break;
		}
	}
}
//====================================================================================================================================


Ice::Ice(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type)
	: Actor(imageID, startX, startY, startingDirection, size, depth, studentWorld, type) {
	setVisible(true);
}

void Ice::doAction() {

}

Boulder::Boulder(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type)
	: Actor(imageID, startX, startY, startingDirection, size, depth, studentWorld, type) {
	this->isStable = true;
	setVisible(true);
}

void Boulder::doAction() {

}
