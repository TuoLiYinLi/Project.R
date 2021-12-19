#include "Grid.h"
#include "SDL.h"
#include "PhysicsFacility.h"

Grid* Grid::createNew(unsigned int x, unsigned int y)
{
	Grid* g = new Grid(x, y);
	if (!g)
	{
		SDL_Log(u8"警告 Grid生成内存不足");
	}
	return g;
}

void Grid::destroy() const
{
	delete this;
}

Grid::Grid(unsigned int x, unsigned int y)
{
	X = x; Y = y;

	list_physics_chara = new std::list<PhysicsChara*>();
	list_physics_facility = new std::list<PhysicsFacility*>();
	list_physics_projectile = new std::list<PhysicsProjectile*>();

	blocking_solid = false;
	blocking_air = false;
	blocking_liquid = false;
	blocking_support = false;
}

Grid::~Grid()
{
	delete list_physics_chara;
	delete list_physics_facility;
	delete list_physics_projectile;
}

bool Grid::getBlockingType(BlockingType blocking_type) const
{
	switch (blocking_type)
	{
	case BlockingType::support:
		return blocking_support;
	case BlockingType::liquid:
		return blocking_liquid;
	case BlockingType::solid:
		return blocking_solid;
	case BlockingType::air:
		return blocking_air;
	}
	SDL_Log(u8"警告 未预料的返回Grid::getBlockingType");
	return false;
}

void Grid::renewBlockingType(BlockingType blocking_type)
{
	if(blocking_type==BlockingType::air)
	{
		return;
	}

	bool result=false;

	for (auto i = list_physics_facility->begin(); i != list_physics_facility->end(); ++i)
	{
		if ((*i)->getFacilityType() == blocking_type)
		{
			result = true;
			break;
		}
	}
	
	switch (blocking_type)
	{
	case BlockingType::support:
		blocking_support = result;
		break;
	case BlockingType::liquid:
		blocking_liquid = result;
		break;
	case BlockingType::solid:
		blocking_solid = result;
		break;
	case BlockingType::air:
		break;
	}
	if(blocking_liquid||blocking_solid||blocking_support)
	{
		blocking_air = false;
	}else
	{
		blocking_air = true;
	}
}
