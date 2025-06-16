#include "Actor.h"
#include "StudentWorld.h"
#include <algorithm>

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

        case KEY_PRESS_TAB:
            
            //kinda works, but gold needs to be in a temporary state after it is dropped by iceman
            if (numberOfGoldNuggets >= 1) {
                numberOfGoldNuggets--;
                //Gold* gold = new Gold(IID_GOLD, x, y, GraphObject::right, 1, 2, thisWorld, "gold", false, true, false, true);
                Gold* gold = new Gold(IID_GOLD, x, y, GraphObject::right, 1, 2, thisWorld, "gold", true, true, false, true);
                //iceField[randomX][randomY] = gold;
                actionList.push_back(gold);
            }
            break;

        case 'Z':
        case 'z':
            if (this->numberOfSonarKits > 0) {
                thisWorld->playSound(SOUND_SONAR);
                setNumberOfSonar(getNumberOfSonar() - 1);
                thisWorld->sonarSearch(getX(), getY());
            }

        case KEY_PRESS_SPACE:

            if (numberOfSquirts > 0) {
                decreaseSquirts();
                thisWorld->fireSquirt(getX(), getY(), getDirection());
            }
            break;

        default:
            break;
        }
    }

}

void IceMan::increaseSonar() {
    this->numberOfSonarKits++;
}

int IceMan::getNumOfSonar() {
    return numberOfSonarKits;
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
	m_state = 0;
	setVisible(true);
}


int Boulder::getState() {
	return m_state;
}


void Boulder::doAction() {

    StudentWorld* thisWorld = getWorld();
	if (!isAlive) //NGL I have no idea how the boulder would ever not be alive but packet said to check
        return;

    switch (m_state)
    {

    case 0: //Boulder is stable
        if (thisWorld->belowBoulder(getX(), getY()) == true) {
            changeState();
            break;
        }
        else
            break;

    case 1: //Boulder is waiting to fall
        if (getTicks() == 30) {
            changeState();
            break;
        }
        else {
			increaseTicks();
            break;
        }

    case 2: //Boulder is falling
        if (thisWorld->belowBoulder(getX(), getY()) == false) {
            setVisible(false);
            setAlive(false);
            getWorld()->playSound(SOUND_FALLING_ROCK);
            getWorld()->increaseScore(100);
            break;
        }
        else {
            moveTo(getX(), getY() - 1);
            thisWorld->playSound(SOUND_FALLING_ROCK);
            break;
		}

        /*if (getX() == thisWorld->getIceMan()->getX() && getY() == thisWorld->getIceMan()->getY()) {
            thisWorld->decLives();
        }*/

    default:
        break;
    }

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

Gold::Gold(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type, bool icemanCanPickup, bool protestorCanPickup, bool permanent, bool visible)
    : Goodie(imageID, startX, startY, startingDirection, size, depth, studentWorld, type) {
    setVisible(visible);
    this->icemanCanPickup = icemanCanPickup;
    this->protestorCanPickup = protestorCanPickup;
    this->permanent = permanent;

    this->ticksSinceDropped = 0;
}

Gold::~Gold() {

}

void Gold::increaseTicks() {
    this->ticksSinceDropped++;
}

int Gold::getTicks() {
    return this->ticksSinceDropped;
}


void Gold::doAction() {
    if (!isAlive()) {
        return;
    }

    //need to delete the instance from action list after it is deleted ???
    else if (isAlive() && this->permanent == true) {
        StudentWorld* thisWorld = getWorld();
        IceMan* iceman = thisWorld->getIceMan();

        int iceManX = iceman->getX(),
            iceManY = iceman->getY(),
            thisX = getX(),
            thisY = getY();

        //can just do with triple nested if else but that is so ugly


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
    else if (this->permanent == false) {

        StudentWorld* thisWorld = getWorld();
        IceMan* iceman = thisWorld->getIceMan();

        int iceManX = iceman->getX(),
            iceManY = iceman->getY(),
            thisX = getX(),
            thisY = getY();

        //add protestor check within 3 blcoks later
        if (this->getTicks() >= 30) {
            this->setVisible(false);
            return;
        }

        this->increaseTicks();
        return;
    }
    else {
        return;
    }
}


//Sonar::Sonar(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type)
//    : Goodie(imageID, startX, startY, startingDirection, size, depth, studentWorld, type) {
//    setVisible(false);
//}
//
//
//void Sonar::doAction() {
//    
//}


Water::Water(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type, bool permanent) 
    : Goodie(imageID, startX, startY, startingDirection, size, depth, studentWorld, type) {
    
    this->setVisible(true);
    this->permanent = false;
    this->ticksSinceSpawn = 0;

}

void Water::doAction() {
    if (!this->isAlive()) {
        return;
    }
    else {
        StudentWorld* thisWorld = getWorld();
        IceMan* iceman = thisWorld->getIceMan();
        int tickLifeSpan = std::max<int>(100, 300 - 10 * thisWorld->getLevel());

        int iceManX = iceman->getX(),
            iceManY = iceman->getY(),
            thisX = getX(),
            thisY = getY();

        //std::cout << this->ticksSinceSpawn << std::endl;

        if (!this->isAlive()) {
            return;
        }
        else if (this->ticksSinceSpawn >= tickLifeSpan) {
            this->setVisible(false);
            this->setAlive(false);

            return;
        }
        else {

            if (std::abs(iceManX - thisX) <= 3 && std::abs(iceManY - thisY) <= 3) {
                setVisible(false);
                setAlive(false);
                iceman->increaseSquirts();
                thisWorld->playSound(SOUND_GOT_GOODIE);
                thisWorld->increaseScore(100);
                return;
            }

            increaseTicks();
        }
    }
}

int Water::getTicks() {
    return this->ticksSinceSpawn;
}

void Water::increaseTicks() {
    this->ticksSinceSpawn++;
}

Water::~Water() {

}


Squirt::Squirt(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type)
    :IceMan(imageID, startX, startY, startingDirection, size, depth, studentWorld, 1, type)
{
    this->setVisible(true);
}


void Squirt::doAction() {
        if (!isAlive()) 
        return;

        if (travelDistance == 0) {
            setAlive(false);
            setVisible(false);
            return;
        }

        // Calculate next position
        int nextX = getX();
        int nextY = getY();
        switch (getDirection()) {
        case up:    nextY += 1; break;
        case down:  nextY -= 1; break;
        case left:  nextX -= 1; break;
        case right: nextX += 1; break;
        default: break;
        }

        // Check bounds
        if (nextX < 0 || nextX >= 64 || nextY < 0 || nextY >= 60) {
            setAlive(false);
            setVisible(false);
            return;
        }

        StudentWorld* world = getWorld();
        // Check for ice or boulder at next position
        if (world->isBoulder(nextX, nextY) || world->isIce(nextX, nextY)) {
            setAlive(false);
            setVisible(false);
            return;
        }
        


        // Move squirt
        moveTo(nextX, nextY);
        travelDistance--;
    
}


Sonar::Sonar(int imageID, int startX, int startY, Direction startingDirection, double size, unsigned int depth, StudentWorld* studentWorld, std::string type)
    : Goodie(imageID, startX, startY, startingDirection, size, depth, studentWorld, type) {
    this->setVisible(true);
    this->ticksSinceSpawn = 0;
}

void Sonar::doAction() {
    StudentWorld* thisWorld = getWorld();
    IceMan* iceman = thisWorld->getIceMan();
    int tickLifeSpan = std::max<int>(100, 300 - 10 * thisWorld->getLevel());

    int iceManX = iceman->getX(),
        iceManY = iceman->getY(),
        thisX = getX(),
        thisY = getY();

    //std::cout << this->ticksSinceSpawn << std::endl;

    if (!this->isAlive()) {
        return;
    }
    else if (this->ticksSinceSpawn >= tickLifeSpan) {
        this->setVisible(false);
        this->setAlive(false);

        return;
    }
    else {

        if (std::abs(iceManX - thisX) <= 3 && std::abs(iceManY - thisY) <= 3) {
            setVisible(false);
            setAlive(false);
            iceman->increaseSonar();
            thisWorld->playSound(SOUND_GOT_GOODIE);
            thisWorld->increaseScore(75);
            return;
        }

        increaseTicks();
    }
}

Sonar::~Sonar() {

}

void Sonar::increaseTicks() {
    this->ticksSinceSpawn++;
}

int Sonar::getTicks() {
    return this->ticksSinceSpawn;
}