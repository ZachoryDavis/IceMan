#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"	
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
	}

	virtual int init()
	{
		//ICEMAN HAS TO BE ABOVE THE ICE 
		for (int i = 0; i < VIEW_WIDTH; i++) {
			for (int j = 0; j < VIEW_HEIGHT; j++) {
				if (i >= 30 && i <= 33 && j > 3) {
					
				}
				else {
					this->iceField[i][j] = new Ice(IID_ICE, i, j, GraphObject::right, 0.25, 3, this);
				}
			}
		}

		this->iceman = new IceMan(IID_PLAYER, 30, 60, GraphObject::right, 1, 0, this, 10);

		return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
	{
		// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
		// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
		decLives();
		//return GWSTATUS_PLAYER_DIED;
		return 9;
	}

	virtual void cleanUp()
	{
	}

private:
	Ice* iceField[VIEW_WIDTH][VIEW_HEIGHT];
	IceMan* iceman;

	int numberOfIce, 
		numberOfGold, 
		numberOfBoulder, 
		numberOfBarrel, 
		numberOfProtestor;

	
};

#endif // STUDENTWORLD_H_
