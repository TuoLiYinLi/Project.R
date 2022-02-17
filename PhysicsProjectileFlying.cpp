#include "PhysicsProjectileFlying.h"

PhysicsProjectileFlying* PhysicsProjectileFlying::createNew()
{
	return new PhysicsProjectileFlying();
}

void PhysicsProjectileFlying::update()
{
	x_v *= damping;
	y_v *= damping;

	x_v += x_a;
	y_v += y_a + gravity;

	PhysicsProjectile::update();
}

PhysicsProjectileFlying::PhysicsProjectileFlying()
{
	type_projectile = ProjectileType::flying;

	gravity = 0;

	x_a = 0;
	y_a = 0;

	damping = 0.95;

}

PhysicsProjectileFlying::~PhysicsProjectileFlying() = default;

void PhysicsProjectileFlying::setup(double _x_a, double _y_a, double _gravity, double _damping)
{
	x_a = _x_a; y_a = _y_a; gravity = _gravity; damping = _damping;
}
