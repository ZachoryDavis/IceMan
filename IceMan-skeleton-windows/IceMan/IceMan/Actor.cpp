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

Human::Human(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health)
	: Actor(imageID, startX, startY, startingDirection, size, depth, studentWorld) {

	
}

Human::~Human() {
	//TODO: IMPLEMENT
}

IceMan::IceMan(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health)
	: Human(imageID, startX, startY, startingDirection, size, depth, studentWorld, health) {
	 //where should we declare heallth??
}

IceMan::~IceMan() {
	//TODO: IMPLEMENT
}

