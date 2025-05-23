#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;


//read carey nachenberg lecture 6 and 7 sldies for polymorphism and inhertiance

class Actor : public GraphObject {

private:
	StudentWorld* studentWorld;
	bool alive;
public:
	Actor(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld);
	virtual ~Actor();
	virtual void doAction() = 0;
	bool isAlive();

	StudentWorld* getWorld();
};



//============== HUMAN CLASSES ===================
class Human : public Actor {
private:
	int health{};
public:
	Human(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health);
	virtual ~Human();

	void setHealth(int health);
	int getHealth();


};

class IceMan : public Human {
private:
	int numberOfSquirts{};
	int numberOfSonarKits{};
	int numberOfGoldNuggets{};
	//int iceManHealth;
public:
	IceMan(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health);
	virtual ~IceMan();

	void setNumberOfSquirts(int squirts);
	int getNumberOfSquirts();

	void setNumberOfSonar(int sonars);
	int getNumberOfSonar();

	void setNumberOfGold(int gold);
	int getNumberOfGold();

	void doAction();


};

class Protestor : public Human {
private:
public:
};

class RegularProtestor : public Protestor {
private:
public:
	//TODO: IMPLEMENT CONSTRUCTOR AND CLASS VARS
	RegularProtestor();
	virtual ~RegularProtestor();
};

class HardcoreProtestor : public Protestor {
private:
public:
	//TODO: IMPLEMENT
};



//================================================

//============= SOLID CLASSES ====================

class Ice : public Actor {
private:
public:

	Ice(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld);

	void doAction();
};

class Boulder : public Actor {
private:
	bool isStable{};
public:
	Boulder(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld);
	void doAction();
};

//================================================

//============= MISC CLASSES =====================

class Goodie : public Actor {
private:
public:

};

class Water : public Goodie {
private:
public:
};

class Sonar : public Goodie {
private:
public:
};

class Gold : public Goodie {
private:
public:
};

class OilBarrel : public Goodie {
private:
public:
};


//wtf do we do with this
//class Squirt : public IceMan {
//
//};
// 
//=================================================


#endif //ACTOR_H_