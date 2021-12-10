#pragma once
#include <list>

class PhysicChara;
class PhysicFacility;
class PhysicProjectile;

class Grid
{
public:
	static Grid* createNew(unsigned int x, unsigned int y);
	void destroy() const;

	std::list<PhysicChara*>* list_physics_chara;
	std::list<PhysicFacility*>* list_physics_facility;
	std::list<PhysicProjectile*>* list_physics_projectile;

protected:
	Grid(unsigned int x, unsigned int y);
	~Grid();
	unsigned int X, Y;//自己的位置
};

