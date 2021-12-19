#include "Defined.h"
#include "WorldSystem.h"

#include "PhysicsProjectile.h"
#include "PhysicsChara.h"
#include  "PhysicsFacility.h"
#include "GameObject.h"

#include "SDL.h"
WorldSystem* WorldSystem::getInstance()
{
	if(instance==nullptr)
	{
		instance = new WorldSystem();
	}
	return instance;
}

void WorldSystem::destroyInstance()
{
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

WorldSystem* WorldSystem::instance = nullptr;

WorldSystem::WorldSystem()
{
	SDL_Log("WorldSystem construct");

	map = new std::vector<std::vector<Grid*>*>();
	for (int i = 0; i < WORLD_WIDTH; ++i)
	{
		auto line_of_grids = new std::vector<Grid*>();
		for (int j = 0; j < WORLD_HEIGHT; ++j)
		{
			line_of_grids->push_back(Grid::createNew(i, j));
		}
		map->push_back(line_of_grids);
	}


	list_physics_chara = new std::list<PhysicsChara*>();
	list_physics_facility = new std::list<PhysicsFacility*>();
	list_physics_projectile = new std::list<PhysicsProjectile*>();

	list_game_objects = new std::list<GameObject*>();
}

WorldSystem::~WorldSystem()
{
	for (int i = 0; i < WORLD_WIDTH; ++i)
	{
		for (int j = 0; j < WORLD_HEIGHT; ++j)
		{
			map->at(i)->at(j)->destroy();
		}
		delete map->at(i);
	}
	delete map;

	delete list_physics_chara;
	delete list_physics_facility;
	delete list_physics_projectile;

	SDL_Log("WorldSystem destruct");
}

void WorldSystem::logicGo() const
{
	logicGo_physics();
	logicGo_game_objects();
}

void WorldSystem::logicGo_physics() const
{
	for (auto i = list_physics_projectile->begin(); i != list_physics_projectile->end(); ++i)
	{
		(*i)->update();
	}

	for (auto i = list_physics_chara->begin(); i != list_physics_chara->end(); ++i)
	{
		(*i)->update();
	}
	/*
	for (auto i = list_physics_facility->begin(); i != list_physics_facility->end(); ++i)
	{
		(*i)->update();
	}
	 */
}

void WorldSystem::logicGo_game_objects() const
{
	for (auto i = list_game_objects->begin(); i != list_game_objects->end(); ++i)
	{
		(*i)->update();
	}
}

