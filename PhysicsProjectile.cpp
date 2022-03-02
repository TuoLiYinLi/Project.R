#include "PhysicsProjectile.h"

#include <SDL_log.h>
#include "WorldSystem.h"

PhysicsProjectile* PhysicsProjectile::createNew()
{
	return new PhysicsProjectile();
}

PhysicsProjectile::PhysicsProjectile()
{
	physicsProjectileNum++;

	//���Լ���ӵ�Ͷ���������б�
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
	//����ǩ��ĸ���
	for (auto it = list_grid_signed->begin(); it != list_grid_signed->end(); ++it)
	{
		const Grid* grid = *it;
		grid->list_physics_projectile->remove(this);
	}
	list_grid_signed->clear();
	//���Լ���Ͷ�����б��Ƴ�
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
	//����
	for (auto it = list_grid_signed->begin(); it != list_grid_signed->end(); ++it)
	{
		const Grid* grid = *it;
		grid->list_physics_projectile->remove(this);
	}
	list_grid_signed->clear();

	//����ǩ��

	const int x_start = getLeftGrid();
	const int x_end = getRightGrid();
	const int y_start = getUpGrid();
	const int y_end = getDownGrid();

	for (int i = x_start; i <= x_end; i++)
	{
		for (int j = y_start; j <= y_end; j++)
		{
			Grid* grid = WorldSystem::getInstance()->getGrid(i, j);
			if(grid)
			{
				grid->list_physics_projectile->push_back(this);
				list_grid_signed->push_back(grid);
			}
		}
	}

	renewHitCharas();
	renewHitFacilities();
	renewHitProjectiles();
}


void PhysicsProjectile::renewHitCharas() const
{
	hit_charas->clear();

	const int up = getUpGrid();
	const int down = getDownGrid();
	const int left = getLeftGrid();
	const int right = getRightGrid();

	for (int x = left; x <= right; ++x)
	{
		for (int y = up; y <= down; ++y)
		{
			Grid* g = WorldSystem::getInstance()->getGrid(x, y);
			if(!g)return;
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

	const int up = getUpGrid();
	const int down = getDownGrid();
	const int left = getLeftGrid();
	const int right = getRightGrid();

	for (int x = left; x <= right; ++x)
	{
		for (int y = up; y <= down; ++y)
		{
			Grid* g = WorldSystem::getInstance()->getGrid(x, y);
			if (!g)return;
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

	const int up = getUpGrid();
	const int down = getDownGrid();
	const int left = getLeftGrid();
	const int right = getRightGrid();

	for (int x = left; x <= right; ++x)
	{
		for (int y = up; y <= down; ++y)
		{
			Grid* g = WorldSystem::getInstance()->getGrid(x, y);
			if (!g)return;
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

bool PhysicsProjectile::detectLocal(BlockingType blocking)
{
	for (auto i = list_grid_signed->begin(); i != list_grid_signed->end(); ++i)
	{
		if ((*i)->getBlockingType(blocking))
		{
			return true;
		}
	}
	return false;
}

void PhysicsProjectile::move(double _dx, double _dy)
{
	X += _dx;
	Y += _dy;
	renewSignedGrids();
}


int PhysicsProjectile::physicsProjectileNum = 0;

int PhysicsProjectile::getPhysicsProjectileNum()
{
	return physicsProjectileNum;
}
