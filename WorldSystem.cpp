#include "Defined.h"
#include "WorldSystem.h"

#include "PhysicsProjectile.h"
#include "PhysicsChara.h"
#include  "PhysicsFacility.h"
#include "GameObject.h"
#include "GameToolkit.h"

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
	SDL_Log(u8"WorldSystem construct");

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

	goldust_energy = 0;
	goldust_energy_recovery = GOLDUST_RECOVERY;
	goldust_energy_accumulation = 0;
	goldust_goal = 1000;

	enemy_wave_CD = 0;
	enemy_wave_num = 0;
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

	SDL_Log(u8"WorldSystem destruct");
}

void WorldSystem::logicGo()
{
	logicGo_game_data();
	logicGo_physics();
	logicGo_game_objects();
}

void WorldSystem::sortGameObjectList()const
{
	list_game_objects->sort(compareGameObjects);
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
}

void WorldSystem::logicGo_game_objects() const
{

	auto i = list_game_objects->begin();
	while (i != list_game_objects->end())
	{
		if(!(*i)->checkIfStatic())
		{
			(*i)->update();
		}
		if((*i)->checkIfDestroy())
		{
			(*i)->destroy();
			i = list_game_objects->erase(i);
		}else
		{
			++i;
		}
	}
}

void WorldSystem::logicGoOnRendering() const
{
	auto i = list_game_objects->begin();
	while (i != list_game_objects->end())
	{
		if(!(*i)->checkIfStatic())
		{
			(*i)->updateOnRendering();
		}
		if ((*i)->checkIfDestroy())
		{
			(*i)->destroy();
			i = list_game_objects->erase(i);
		}
		else
		{
			++i;
		}
	}
}


void WorldSystem::logicGo_game_data()
{
	goldust_energy_accumulation += goldust_energy_recovery;
	const int delta = static_cast<int>(floor(goldust_energy_accumulation));
	goldust_energy += delta;
	goldust_energy_accumulation -= delta;

	enemy_wave_CD--;
	if(enemy_wave_CD<=0)
	{
		//ÏÂÒ»²¨
		enemy_wave_num++;
		enemy_wave_CD = GameToolkit::getWaveTime(enemy_wave_num);
	}
}


Grid* WorldSystem::getGrid(int _x, int _y) const
{
	if (_x >= 0 && _x < WORLD_WIDTH && _y >= 0 && _y < WORLD_HEIGHT)
	{
		return map->at(_x)->at(_y);
	}
	else
	{
		return nullptr;
	}
}

bool WorldSystem::compareGameObjects(GameObject* o1, GameObject* o2)
{
	return static_cast<int>(o1->type_game_object) < static_cast<int>(o2->type_game_object);
}
