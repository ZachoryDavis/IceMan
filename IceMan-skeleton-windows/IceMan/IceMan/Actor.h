#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class Actor {
	public:
		virtual ~Actor();
		virtual void doSomething() = 0;

		private:
			
};


class Human : public Actor {
	public:
		virtual ~Human();
	private:
		int health{};
		
};


class Solid : public Actor {
	public:
		virtual ~Solid();
};


class Goodie : public Actor {
	public:
		virtual ~Goodie();
};


class IceMan : public Human {
	public:
		IceMan();
		IceMan(int startX = 30, int startY = 60, int imageID = IID_PLAYER, Direction dir = right, double size = 1.0, unsigned int depth = 0, int health = 10);
		virtual ~IceMan();
	private:
		int numberOfSquirts = 5;
		int numberOfSonarKits = 1;
		int numberOfGoldNuggets = 0;
};


class Protester : public Human {
	public:
		virtual ~Protester();
};


class Boulder : public Solid {
	public:
		~Boulder();
};


class Ice : public Solid {
	public:
		~Ice();
};


class RegularProtester : public Protester {
	public:
		~RegularProtester();
};


class HardcoreProtester : public Protester {
	public:
		~HardcoreProtester();
};


class Squirts : public IceMan {
	//Could just be a public Solid but pretty sure its a subclass
	//of IceMan
	public:
		~Squirts();
};


class Water : public Goodie {
	//Could be under Solid instead of Goodie if water is
	//not a pick-upable item
	public:
		~Water();
};


class SonarKit : public Goodie {
	public:
		~SonarKit();
};


class GoldNugget : public Goodie {
	public:
		~GoldNugget();
};


class BarrelOfOil : public Goodie {
	//Could be under Solid instead of Goodie if Barrel of Oil is
	//not a pick-upable item
	public:
		~BarrelOfOil();
};

#endif // ACTOR_H_
