#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
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

private:
	Actor* iceField[VIEW_WIDTH][VIEW_HEIGHT];
	std::vector<Actor*> actionList;
	IceMan* iceman;

	int numberOfIce,
		numberOfGold,
		numberOfBoulder,
		numberOfOil,
		numberOfProtestor,
		currentLevelNumber;

	
};

#endif // STUDENTWORLD_H_
