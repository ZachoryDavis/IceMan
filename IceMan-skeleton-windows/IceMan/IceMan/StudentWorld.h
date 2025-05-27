#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include "Actor.h"	
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
	}

	virtual int init();

	virtual int move();

	virtual void cleanUp();

	void showTextBar();

	StudentWorld* getWorld();

	Actor* getIceField();

	bool isBoulder(int x, int y);

	bool overlap(std::pair<int, int>  coords);

	void removeIce(int x, int y);

	std::vector<Actor*> getList();

	IceMan* getIceMan();

	void decreaseOil();

	int getOil() {
		return this->numberOfOil;
	}
	

private:
	Actor* iceField[64][60];
	std::vector<Actor*> actionList;
	IceMan* iceman;

	int numberOfIce,
		numberOfGold,
		numberOfBoulder,
		numberOfOil,
		numberOfProtestor,
		currentLevelNumber = 0;

	
};

#endif // STUDENTWORLD_H_
