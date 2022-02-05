#include "ProjectileTarget.h"

#include <SDL_log.h>

#include "PhysicsChara.h"

ProjectileTarget* ProjectileTarget::createNew()
{
	const auto p = new ProjectileTarget();
	if (!p)
	{
		SDL_Log(u8"警告 分配ProjectilePoint内存不足");
	}
	return p;
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
