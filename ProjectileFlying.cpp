#include "ProjectileFlying.h"

ProjectileFlying* ProjectileFlying::createNew()
{
	return new ProjectileFlying();
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
