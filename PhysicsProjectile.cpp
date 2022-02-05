#include "PhysicsProjectile.h"

#include <SDL_log.h>
#include "Defined.h"
#include "WorldSystem.h"

PhysicsProjectile* PhysicsProjectile::createNew()
{
	PhysicsProjectile* physics_projectile = new PhysicsProjectile();
	if(!physics_projectile)
	{
		SDL_Log(u8"警告 分配physics_projectile内存不足");
	}
	return physics_projectile;
}

PhysicsProjectile::PhysicsProjectile()
{
	physicsProjectileNum++;

	//将自己添加到投射物物理列表
	WorldSystem::getInstance()->list_physics_projectile->push_front(this);

	list_grid_signed = new std::list<Grid*>();

	type_physics = PhysicsType::projectile;
	type_projectile = ProjectileType::none;

	hit_charas = new std::list<PhysicsChara*>();
	hit_facilities = new std::list<PhysicsFacility*>();
	hit_projectiles = new std::list<PhysicsProjectile*>();

	x_v = 0;
	y_v = 0;
}

PhysicsProjectile::~PhysicsProjectile()
{
	//将自己从投射物列表移除
	WorldSystem::getInstance()->list_physics_projectile->remove(this);

	delete list_grid_signed;

	delete hit_charas;
	delete hit_facilities;
	delete hit_projectiles;

	physicsProjectileNum--;
}

void PhysicsProjectile::update()
{
	move(x_v, y_v);
}

void PhysicsProjectile::renewSignedGrids()
{
	//重置
	for (auto it = list_grid_signed->begin(); it != list_grid_signed->end(); ++it)
	{
		const Grid* grid = *it;
		grid->list_physics_projectile->remove(this);
	}
	list_grid_signed->clear();

	//重新签入

	const int x_start = getLeftGrid();
	const int x_end = getRightGrid();
	const int y_start = getTopGrid();
	const int y_end = getBottomGrid();

	if (x_start < 0 || x_end >= (int)WORLD_WIDTH || y_start < 0 || y_start >= (int)WORLD_HEIGHT)
	{
		SDL_Log(u8"projectile超出范围");
		return;
	}

	for (int i = x_start; i <= x_end; i++)
	{
		for (int j = y_start; j <= y_end; j++)
		{
			Grid* grid = WorldSystem::getInstance()->getGrid(i, j);
			grid->list_physics_projectile->push_back(this);
			list_grid_signed->push_back(grid);
		}
	}
}


void PhysicsProjectile::renewHitCharas() const
{
	hit_charas->clear();

	const int up = getTopGrid();
	const int down = getBottomGrid();
	const int left = getLeftGrid();
	const int right = getRightGrid();

	if (left < 0 || right >= (int)WORLD_WIDTH || up < 0 || down >= (int)WORLD_HEIGHT)
	{
		SDL_Log(u8"超出范围");
		return;
	}

	for (int x = left; x <= right; ++x)
	{
		for (int y = up; y <= down; ++y)
		{
			Grid* g = WorldSystem::getInstance()->getGrid(x, y);
			for (auto i = g->list_physics_chara->begin(); i != g->list_physics_chara->end(); ++i)
			{
				hit_charas->push_front(*i);
			}
		}
	}

}

void PhysicsProjectile::renewHitFacilities() const
{
	hit_facilities->clear();

	const int up = getTopGrid();
	const int down = getBottomGrid();
	const int left = getLeftGrid();
	const int right = getRightGrid();

	if (left < 0 || right >= (int)WORLD_WIDTH || up < 0 || down >= (int)WORLD_HEIGHT)
	{
		SDL_Log(u8"超出范围");
		return;
	}

	for (int x = left; x <= right; ++x)
	{
		for (int y = up; y <= down; ++y)
		{
			Grid* g = WorldSystem::getInstance()->getGrid(x, y);
			for (auto i = g->list_physics_facility->begin(); i != g->list_physics_facility->end(); ++i)
			{
				hit_facilities->push_front(*i);
			}
		}
	}
}

void PhysicsProjectile::renewHitProjectiles() const
{
	hit_projectiles->clear();

	const int up = getTopGrid();
	const int down = getBottomGrid();
	const int left = getLeftGrid();
	const int right = getRightGrid();

	if (left < 0 || right >= (int)WORLD_WIDTH || up < 0 || down >= (int)WORLD_HEIGHT)
	{
		SDL_Log(u8"超出范围");
		return;
	}

	for (int x = left; x <= right; ++x)
	{
		for (int y = up; y <= down; ++y)
		{
			Grid* g = WorldSystem::getInstance()->getGrid(x, y);
			for (auto i = g->list_physics_projectile->begin(); i != g->list_physics_projectile->end(); ++i)
			{
				if(*i!=this)
					hit_projectiles->push_front(*i);
			}
		}
	}

}

std::list<PhysicsChara*>* PhysicsProjectile::getHitCharas() const
{
	return  hit_charas;
}

std::list<PhysicsFacility*>* PhysicsProjectile::getHitFacilities() const
{
	return hit_facilities;
}

std::list<PhysicsProjectile*>* PhysicsProjectile::getHitProjectiles() const
{
	return hit_projectiles;
}

void PhysicsProjectile::move(double _dx, double _dy)
{
	X += _dx;
	Y += _dy;
	renewSignedGrids();
}


int PhysicsProjectile::physicsProjectileNum = 0;

int PhysicsProjectile::getPhysicsProjectilleNum()
{
	return physicsProjectileNum;
}
