#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;




class Actor : public GraphObject{

private:
	StudentWorld* studentWorld;
	bool alive;
public:
	Actor(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld);
	virtual ~Actor();
};



//============== HUMAN CLASSES ===================
class Human : public Actor {
private:
	int health{};
public:
	Human(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health);
	virtual ~Human();
		
};

class IceMan : public Human {
private:
	int numberOfSquirts = 5;
	int numberOfSonarKits = 1;
	int numberOfGoldNuggets = 0;
	//int iceManHealth;
public:
	IceMan(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health);
	virtual ~IceMan();

};

class RegularProtestor : public Human {
private:
public:
	//TODO: IMPLEMENT CONSTRUCTOR AND CLASS VARS
	RegularProtestor();
	virtual ~RegularProtestor();
};

//Inherit from RegularProtestor or Human ????
class HardcoreProtestor : public RegularProtestor {
private:
public:
	//TODO: IMPLEMENT
};



//================================================

//============= SOLID CLASSES ====================

class Solid : public Actor {
private:

public:

};

class Ice : public Solid {
private:
public:
	
};

class Boulder : public Solid {
private:
public:
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


#endif // ACTOR_H_
