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




//================================================



//
//
//class Solid : public Actor {
//	public:
//		virtual ~Solid();
//};
//
//
//class Goodie : public Actor {
//	public:
//		virtual ~Goodie();
//};
//
//
//class IceMan : public Human {
//	public:
//		IceMan();
//		IceMan(int startX = 30, int startY = 60, int imageID = IID_PLAYER, Direction dir = right, double size = 1.0, unsigned int depth = 0, int health = 10);
//		virtual ~IceMan();
//	private:
//		int numberOfSquirts = 5;
//		int numberOfSonarKits = 1;
//		int numberOfGoldNuggets = 0;
//};
//
//
//class Protester : public Human {
//	public:
//		virtual ~Protester();
//};
//
//
//class Boulder : public Solid {
//
//public:
//	~Boulder();
//};
//
//
//class Ice : public Solid {
//public:
//	/*Ice(int startX, int startY, StudentWorld* sw) : Actor(IID_ICE, startX, startY, sw, right, 0.25, 3)
//	{
//		setVisible(true);
//	}*/
//
//	Ice(int startX, int startY, StudentWorld* studentWorld) : Solid()
//	~Ice();
//};
//
//
//class RegularProtester : public Protester {
//public:
//	~RegularProtester();
//};
//
//
//class HardcoreProtester : public Protester {
//public:
//	~HardcoreProtester();
//};
//
//
//class Squirts : public IceMan {
//	//Could just be a public Solid but pretty sure its a subclass
//	//of IceMan
//	public:
//		~Squirts();
//};
//
//
//class Water : public Goodie {
//	//Could be under Solid instead of Goodie if water is
//	//not a pick-upable item
//	public:
//		~Water();
//};
//
//
//class SonarKit : public Goodie {
//	public:
//		~SonarKit();
//};
//
//
//class GoldNugget : public Goodie {
//	public:
//		~GoldNugget();
//};
//
//
//class BarrelOfOil : public Goodie {
//	//Could be under Solid instead of Goodie if Barrel of Oil is
//	//not a pick-upable item
//	public:
//		~BarrelOfOil();
//};

#endif // ACTOR_H_
