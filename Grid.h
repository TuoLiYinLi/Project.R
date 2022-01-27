#pragma once
#include <list>
#include "PhysicsObject.h"

class PhysicsChara;
class PhysicsFacility;
class PhysicsProjectile;

class Grid
{
public:
	static Grid* createNew(unsigned int x, unsigned int y);
	void destroy() const;

	std::list<PhysicsChara*>* list_physics_chara;
	std::list<PhysicsFacility*>* list_physics_facility;
	std::list<PhysicsProjectile*>* list_physics_projectile;

	void renewBlockingType(BlockingType blocking_type);
	bool getBlockingType(BlockingType blocking_type) const;

	static int getGridNum();
protected:
	Grid(unsigned int x, unsigned int y);
	~Grid();
	unsigned int X, Y;//自己的位置


	bool blocking_air;
	bool blocking_support;
	bool blocking_liquid;
	bool blocking_solid;

private:
	static int grid_num;
};

