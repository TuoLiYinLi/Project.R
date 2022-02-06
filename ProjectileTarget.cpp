#include "ProjectileTarget.h"


#include "PhysicsChara.h"

ProjectileTarget* ProjectileTarget::createNew()
{
	return new ProjectileTarget();
}

void ProjectileTarget::update()
{
	PhysicsProjectile::update();
}


ProjectileTarget::ProjectileTarget()
{
	type_projectile = ProjectileType::target;

	target = nullptr;
}

ProjectileTarget::~ProjectileTarget() = default;

void ProjectileTarget::setVelocity(double _v)
{
	if(!target)
	{
		return;
	}

	const double x_distance = target->X - X;
	const double y_distance = target->Y - Y;

	if (abs(x_distance) < _v)
	{
		x_v = x_distance;
		y_v = y_distance;
		return;
	}

	const double d = sqrt(x_distance * x_distance + y_distance * y_distance);

	if (d <= 0)
	{
		x_v = 0;
		y_v = 0;
		return;
	}

	const double mo = 1 / d;

	x_v = x_distance * mo * _v;
	y_v = y_distance * mo * _v;
}
