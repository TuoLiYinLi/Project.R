#include "Grid.h"
#include "SDL.h"

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

	list_physics_chara = new std::list<PhysicChara*>();
	list_physics_facility = new std::list<PhysicFacility*>();
	list_physics_projectile = new std::list<PhysicProjectile*>();
}

Grid::~Grid()
{
	delete list_physics_chara;
	delete list_physics_facility;
	delete list_physics_projectile;
}


