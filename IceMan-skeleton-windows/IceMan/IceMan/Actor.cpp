
#include "Actor.h"
#include "StudentWorld.h"


Actor::Actor(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type)
	: GraphObject(imageID, startX, startY, startingDirection, size, depth), type(type) {
	this->studentWorld = studentWorld;
	this->alive = true;
}

Actor::~Actor() {
	//TODO: IMPLEMENT
}

bool Actor::isAlive() {
	return alive;
}

StudentWorld* Actor::getWorld() {
	return this->studentWorld;
}

std::string Actor::getType() {
	if (this->type != "")
		return this->type;
	else
		return ""; //default variable for when the cell is empty, the program doesnt try to return a null value
}

void Actor::setAlive(bool aliveStatus) {
    this->alive = aliveStatus;
}

Human::Human(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health, std::string type)
    : Actor(imageID, startX, startY, startingDirection, size, depth, studentWorld, type) {
    this->health = health;
}

Human::~Human() {
	//TODO: IMPLEMENT
}

void Human::setHealth(int health) {
	this->health = health;
}

int Human::getHealth() {
	return this->health;
}

//====================================================================================================================================
IceMan::IceMan(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, int health, std::string type)
	: Human(imageID, startX, startY, startingDirection, size, depth, studentWorld, health, type) {
	setHealth(10);
	this->numberOfSquirts = 5;
	this->numberOfSonarKits = 1;
	this->numberOfGoldNuggets = 0;
	setVisible(true);
}

IceMan::~IceMan() {
	//TODO: IMPLEMENT
}

void IceMan::setNumberOfSquirts(int squirts) {
	this->numberOfSquirts = squirts;
}

int IceMan::getNumberOfSquirts() {
	return this->numberOfSquirts;
}

void IceMan::setNumberOfSonar(int sonar) {
	this->numberOfSonarKits = sonar;
}

int IceMan::getNumberOfSonar() {
	return this->numberOfSonarKits;
}

void IceMan::setNumberOfGold(int gold) {
	this->numberOfGoldNuggets = gold;
}

int IceMan::getNumberOfGold() {
	return this->numberOfGoldNuggets;
}

void IceMan::increaseOil() {
    this->numberOfOil++;
}

int IceMan::getNumberOfOil() {
    return numberOfOil;
}

void IceMan::increaseGold() {
    this->numberOfGoldNuggets++;
}
//Added boundry checking for boulders
//Added checking for Ice to remove it if iceman moves over it
void IceMan::doAction() {
    int keyPress;
    StudentWorld* thisWorld = getWorld();
    const int iceManSize = 4;
    std::vector<Actor*> actionList = thisWorld->getList();

    ///////////////////////////////////////////////////////////////
    int x = getX();
    int y = getY();
    for (int new_x = 0; new_x < 4; new_x++) {
        for (int new_y = 0; new_y < 4; new_y++) {
            if (x + new_x < 64 && y + new_y < 60) {
                thisWorld->removeIce(x + new_x, y + new_y);
            }
        }
    }
   
    ///////////////////////////////////////////////////////////////

  
    ///////////////////////////////////////////////////
    if (thisWorld->getKey(keyPress)) {
        switch (keyPress)
        {
        case KEY_PRESS_LEFT:
            if (getDirection() != left) {
                this->setDirection(left);
            }
            if (getX() >= 1) {
                bool blocked = false;
                for (int new_y = 0; new_y < iceManSize; ++new_y) {
                    if (thisWorld->isBoulder(getX() - 1, getY() + new_y)) {
                        blocked = true;
                        break;
                    }
                }
                if (!blocked) {
                    moveTo(getX() - 1, getY());
                }
            }
            break;

        case KEY_PRESS_RIGHT:
            if (getDirection() != right) {
                this->setDirection(right);
            }
            if (getX() + iceManSize <= 63) {
                bool blocked = false;
                for (int new_y = 0; new_y < iceManSize; ++new_y) {
                    if (thisWorld->isBoulder(getX() + iceManSize, getY() + new_y)) {
                        blocked = true;
                        break;
                    }
                }
                if (!blocked) {
                    moveTo(getX() + 1, getY());
                }
            }
            break;

        case KEY_PRESS_UP:
            if (getDirection() != up) {
                this->setDirection(up);
            }
            if (getY() + iceManSize <= 59) {
                bool blocked = false;
                for (int new_x = 0; new_x < iceManSize; ++new_x) {
                    if (thisWorld->isBoulder(getX() + new_x, getY() + iceManSize)) {
                        blocked = true;
                        break;
                    }
                }
                if (!blocked) {
                    moveTo(getX(), getY() + 1);
                }
            }
            break;

        case KEY_PRESS_DOWN:
            if (getDirection() != down) {
                this->setDirection(down);
            }
            if (getY() >= 1) {
                bool blocked = false;
                for (int new_x = 0; new_x < iceManSize; ++new_x) {
                    if (thisWorld->isBoulder(getX() + new_x, getY() - 1)) {
                        blocked = true;
                        break;
                    }
                }
                if (!blocked) {
                    moveTo(getX(), getY() - 1);
                }
            }
            break;

        default:
            break;
        }
    }
}
//====================================================================================================================================


Ice::Ice(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type)
	: Actor(imageID, startX, startY, startingDirection, size, depth, studentWorld, type) {
	setVisible(true);
}

void Ice::doAction() {

}


Ice::~Ice() {

}



Boulder::Boulder(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type)
	: Actor(imageID, startX, startY, startingDirection, size, depth, studentWorld, type) {
	this->isStable = true;
	setVisible(true);
}

void Boulder::doAction() {
	if (!isAlive) //NGL I have no idea how the boulder would ever not be alive but packet said to check
        return;


}

Goodie::Goodie(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type) 
    : Actor(imageID, startX, startY, startingDirection, size, depth, studentWorld, type){

}

Goodie::~Goodie() {

}

void Goodie::doAction() {
    
}


OilBarrel::OilBarrel(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type)
    : Goodie(imageID, startX, startY, startingDirection, size, depth, studentWorld, type) {
    setVisible(false);
}

OilBarrel::~OilBarrel() {

}

void OilBarrel::doAction() {
    if (!isAlive()) {
        return;
    }
    else {
        StudentWorld* thisWorld = getWorld();
        IceMan* iceman = thisWorld->getIceMan();

        int iceManX = iceman->getX(),
            iceManY = iceman->getY(),
            thisX = getX(),
            thisY = getY();

        if (std::abs(iceManX - thisX) <= 4 && std::abs(iceManY - thisY) <= 4) {
            this->setVisible(true);
        }
        //test this
        if (std::abs(iceManX - thisX) <= 3 && std::abs(iceManY - thisY) <= 3) {
            setVisible(false);         
            setAlive(false);   
            thisWorld->decreaseOil();
            iceman->increaseOil();
            thisWorld->playSound(SOUND_FOUND_OIL); 
            thisWorld->increaseScore(1000);        
            return;
        }
    }
    
}

Gold::Gold(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type, bool icemanCanPickup, bool protestorCanPickup, bool permanent)
    : Goodie(imageID, startX, startY, startingDirection, size, depth, studentWorld, type) {
    setVisible(false);
    this->icemanCanPickup = icemanCanPickup;
    this->protestorCanPickup = protestorCanPickup;
    this->permanent = permanent;
}

Gold::~Gold() {

}

void Gold::doAction() {
    if (!isAlive()) {
        return;
    }
    else {
        StudentWorld* thisWorld = getWorld();
        IceMan* iceman = thisWorld->getIceMan();

        int iceManX = iceman->getX(),
            iceManY = iceman->getY(),
            thisX = getX(),
            thisY = getY();

        if (this->isVisible() == false && std::abs(iceManX - thisX) <= 4 && std::abs(iceManY - thisY) <= 4) {
            this->setVisible(true);
            return;
        }
        //test this
        if (this->icemanCanPickup == true && std::abs(iceManX - thisX) <= 3 && std::abs(iceManY - thisY) <= 3) {
            setVisible(false);
            setAlive(false);
            thisWorld->decreaseGold();
            iceman->increaseGold();
            thisWorld->playSound(SOUND_GOT_GOODIE);
            thisWorld->increaseScore(10);
            return;
        }

        //NEED TO IMPLEMENT TEMPORARY STATE AND PICKUPABLE AFTER PROTESTORS ARE IMPLEMENTED
    }

}
//Squirt::Squirt(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type)
//    : IceMan(imageID, startX, startY, startingDirection, size, depth, studentWorld, 10, type) {
//    setVisible(true);
//}

//void Squirt::doAction() {
//    
//}
