#include "Actor.h"
#include "StudentWorld.h"


Actor::Actor(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld) 
	: GraphObject(imageID, startX, startY, startingDirection, size, depth) {

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

Human::Human(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health)
	: Actor(imageID, startX, startY, startingDirection, size, depth, studentWorld) {

	
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
IceMan::IceMan(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health)
	: Human(imageID, startX, startY, startingDirection, size, depth, studentWorld, health) {
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
	
	
	if (getWorld()->getKey(keyPress)) {
		switch (keyPress)
		{
		case KEY_PRESS_LEFT:
			if (getDirection() != left) {
				this->setDirection(left);
			}
			break;

			//if(getX() >= 1 && )
		case KEY_PRESS_RIGHT:
			if (getDirection() != right) {
				this->setDirection(right);
			}
			break;

		case KEY_PRESS_UP:
			if (getDirection() != up) {
				this->setDirection(up);
			}
			break;

		case KEY_PRESS_DOWN:
			if (getDirection() != down) {
				this->setDirection(down);
			};
			break;

		default:
			break;
		}
	}
}
//====================================================================================================================================


Ice::Ice(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld) : Actor(IID_ICE, startX, startY, right, 0.25, 3 , studentWorld) { 
	setVisible(true);
}

void Ice::doAction() {

}

Boulder::Boulder(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld) : Actor(IID_BOULDER, startX, startY, down, 1, 1, studentWorld) {
	this->isStable = true;
	setVisible(true);	
}

void Boulder::doAction() {

}