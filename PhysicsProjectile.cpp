#include "PhysicsProjectile.h"

#include <SDL_log.h>

#include "WorldSystem.h"

PhysicsProjectile* PhysicsProjectile::createNew()
{
	PhysicsProjectile* physics_projectile = new PhysicsProjectile();
	if(!physics_projectile)
	{
		SDL_Log(u8"���� ����physics_projectile�ڴ治��");
	}
	return physics_projectile;
}

void PhysicsProjectile::update()
{
	//���ø������
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
	//���Լ���ӵ�Ͷ���������б�
	WorldSystem::getInstance()->list_physics_projectile->push_front(this);
}

PhysicsProjectile::~PhysicsProjectile()
{
	//���Լ���Ͷ�����б��Ƴ�
	WorldSystem::getInstance()->list_physics_projectile->remove(this);
}


