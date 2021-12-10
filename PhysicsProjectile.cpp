#include "PhysicsProjectile.h"

#include <SDL_log.h>

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

void PhysicsProjectile::update()
{
	//调用父类更新
	PhysicsObject::update();
}

void PhysicsProjectile::signPosition()
{
	
}

void PhysicsProjectile::move(double d_x, double d_y)
{
	X += d_x;
	Y += d_y;
}

PhysicsProjectile::PhysicsProjectile()
{
	//将自己添加到投射物物理列表
	WorldSystem::getInstance()->list_physics_projectile->push_front(this);
}

PhysicsProjectile::~PhysicsProjectile()
{
	//将自己从投射物列表移除
	WorldSystem::getInstance()->list_physics_projectile->remove(this);
}


