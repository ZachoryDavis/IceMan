#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>

class StudentWorld;


//read carey nachenberg lecture 6 and 7 sldies for polymorphism and inhertiance

class Actor : public GraphObject {

private:
	StudentWorld* studentWorld;
	bool alive;
	std::string type = "";
public:
	Actor(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type);
	virtual ~Actor();
	virtual void doAction() = 0;
	bool isAlive();

	std::string getType();

	StudentWorld* getWorld();
};



//============== HUMAN CLASSES ===================
class Human : public Actor {
private:
	int health{};
public:
	Human(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health, std::string type);
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
	IceMan(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health, std::string type);
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
	Protestor(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health, std::string type);

};

class RegularProtestor : public Protestor {
private:
public:
	//TODO: IMPLEMENT CONSTRUCTOR AND CLASS VARS
	RegularProtestor(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health, std::string type);
	virtual ~RegularProtestor();
};

class HardcoreProtestor : public Protestor {
private:
public:
	HardcoreProtestor(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health, std::string type);

	//TODO: IMPLEMENT
};



//================================================

//============= SOLID CLASSES ====================

class Ice : public Actor {
private:
public:

	Ice(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type);

	void doAction();
};



class Boulder : public Actor {
private:
	bool isStable{};
public:
	Boulder(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type);
	void doAction();
};

//================================================

//============= MISC CLASSES =====================

class Goodie : public Actor {
private:
public:
	Goodie(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type);

};

class Water : public Goodie {
private:
public:
	Water(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type);

};

class Sonar : public Goodie {
private:
public:
	Sonar(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type);

};

class Gold : public Goodie {
private:
public:
	Gold(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type);

};

class OilBarrel : public Goodie {
private:
public:
	OilBarrel(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type);

};


//wtf do we do with this
//class Squirt : public IceMan {
//
//};
// 
//=================================================


#endif //ACTOR_H_