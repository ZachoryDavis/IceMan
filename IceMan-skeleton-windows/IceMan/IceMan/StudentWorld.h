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

	~StudentWorld() {
		delete this->iceman;
		
		for (auto x : actionList) {
			delete x;
		}
		actionList.clear();

		for (int i = 0; i < 64; i++) {
			for (int j = 0; j < 60; j++) {
				if (iceField[i][j] != nullptr) {
					delete iceField[i][j];
				}
			}
		}
	}

	virtual int init();

	virtual int move();

	virtual void cleanUp();

	void showTextBar();

	StudentWorld* getWorld();

	Actor* getIceField();

	bool isBoulder(int x, int y);

	bool belowBoulder(int x, int y);

	bool overlap(std::pair<int, int>  coords);

	void removeIce(int x, int y);

	bool isIce(int x, int y);

	bool sonarSearch(int x, int y);

	bool fireSquirt(int x, int y, GraphObject::Direction dir);

	std::vector<Actor*> getList();

	IceMan* getIceMan();

	void decreaseOil();
	
	void decreaseGold();

	void spawnTickUnits();

	void increaseTicks() {
		ticks++;
	}

	int getTicks() {
		return ticks;
	}

	bool canAddWater(int x, int y);

private:
	Actor* iceField[64][60];
	std::vector<Actor*> actionList;
	IceMan* iceman;

	int numberOfIce,
		numberOfGold,
		numberOfBoulder,
		numberOfOil,
		numberOfProtestor,
		currentLevelNumber = 0,
		ticks = 0;

	
};

#endif // STUDENTWORLD_H_
