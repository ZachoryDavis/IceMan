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


	//temp i think delete eventually when implement destructor
	void setAlive(bool aliveStatus);

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
	int numberOfOil{};
	//int iceManHealth;
public:
	IceMan(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health, std::string type);
	virtual ~IceMan();

	void setNumberOfSquirts(int squirts);
	int getNumberOfSquirts();
	void increaseSquirts() {
		this->numberOfSquirts += 5;
	}
	void decreaseSquirts() {
		if (this->numberOfSquirts > 0)
			this->numberOfSquirts--;
	}

	void setNumberOfSonar(int sonars);
	int getNumberOfSonar();

	void setNumberOfGold(int gold);
	int getNumberOfGold();

	void increaseOil();
	int getNumberOfOil();

	void increaseGold();

	void increaseSonar();
	int getNumOfSonar();

	void doAction();


};

class Protestor : public Human {
private:
	bool visible;
public:
	Protestor(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health, std::string type);
	virtual ~Protestor();
};

class RegularProtestor : public Protestor {
private:
	int numSquaresToMoveInCurrentDirection;
	bool leaveTheOilField;
public:
	//TODO: IMPLEMENT CONSTRUCTOR AND CLASS VARS
	RegularProtestor(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health, std::string type);
	void doAction();
	virtual ~RegularProtestor();
};

class HardcoreProtestor : public Protestor {
private:
	int numSquaresToMoveInCurrentDirection;
	bool leaveTheOilField;
public:
	HardcoreProtestor(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health, std::string type);
	void doAction();
	virtual ~HardcoreProtestor();
	//TODO: IMPLEMENT
};



//================================================

//============= SOLID CLASSES ====================

class Ice : public Actor {
private:
public:

	Ice(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type);

	void doAction();
	virtual ~Ice();
};



class Boulder : public Actor {
private:
	int m_state;
	int m_ticks = 0;
	bool isAlive = true;
public:
	Boulder(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type);
	void doAction();
	int getState();
	void changeState() { m_state++; };
	int getTicks() { return m_ticks; };
	int increaseTicks() { return m_ticks++; };
};

//================================================

//============= MISC CLASSES =====================

class Goodie : public Actor {
private:

public:
	Goodie(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type);
	virtual ~Goodie();
	void doAction();

};

class Water : public Goodie {
private:
	bool permanent;
	int ticksSinceSpawn;
public:
	Water(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type, bool permanent);
	virtual ~Water();

	void doAction();

	int getTicks();
	void increaseTicks();
};

class Sonar : public Goodie {
private:
	bool permanent;
	int ticksSinceSpawn;

public:
	Sonar(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type);
	void doAction();
	~Sonar();

	void increaseTicks();
	int getTicks();
};

class Gold : public Goodie {
private:
	bool icemanCanPickup;
	bool protestorCanPickup;
	bool permanent;

	int ticksSinceDropped{};
public:
	Gold(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type, bool icemanCanPickup, bool protestorCanPickup, bool permanent, bool visible);
	virtual ~Gold();
	void doAction();

	void increaseTicks();
	int getTicks();

};

class OilBarrel : public Goodie {
private:
public:
	OilBarrel(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type);
	virtual ~OilBarrel();

	void doAction();

};


class Squirt : public IceMan {
private:
	int travelDistance = 4;
public:
	Squirt(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type);
	void doAction() override;
};


#endif //ACTOR_H_