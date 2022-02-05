#include "ProjectileFlying.h"

#include <SDL_log.h>

ProjectileFlying* ProjectileFlying::createNew()
{
	const auto p = new ProjectileFlying();
	if (!p)
	{
		SDL_Log(u8"警告 分配ProjectilePoint内存不足");
	}
	return p;
}

void ProjectileFlying::update()
{
	x_v *= damping;
	y_v *= damping;

	x_v += x_a;
	y_v += y_a + gravity;

	PhysicsProjectile::update();
}

ProjectileFlying::ProjectileFlying()
{
	type_projectile = ProjectileType::flying;

	gravity = 0;

	x_a = 0;
	y_a = 0;

	damping = 0.95;

}

ProjectileFlying::~ProjectileFlying() = default;
