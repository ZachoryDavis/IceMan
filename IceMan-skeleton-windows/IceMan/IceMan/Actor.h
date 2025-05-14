#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class Actor {
public:
	virtual ~Actor();
};


class Human : public Actor {
public:
	virtual ~Human();
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
	virtual ~IceMan();
};


class Protester : public Human {
public:
	virtual ~Protester();
};


class boulder : public Solid {
public:
	~Boulder();
};


class Ice : public Solid {
public:
	~Ice();
};


class RegularProtester : public protester {
public:
	~RegularProtester();
};


class HardcoreProtester : public protester {
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
