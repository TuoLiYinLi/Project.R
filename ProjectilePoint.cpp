#include "ProjectilePoint.h"

ProjectilePoint* ProjectilePoint::createNew()
{
	return new ProjectilePoint();
}

void ProjectilePoint::update()
{
	setVelocity(0.16);

	PhysicsProjectile::update();
}

ProjectilePoint::ProjectilePoint()
{
	type_projectile = ProjectileType::point;

	x_aiming = 0;
	y_aiming = 0;
}

ProjectilePoint::~ProjectilePoint() = default;

void ProjectilePoint::setVelocity(double _v)
{
	const double x_distance = x_aiming - X;
	const double y_distance = y_aiming - Y;

	if(abs(x_distance)<_v)
	{
		x_v = x_distance;
		y_v = y_distance;
		return;
	}

	const double d = sqrt(x_distance * x_distance + y_distance * y_distance);

	if(d<=0)
	{
		x_v = 0;
		y_v = 0;
		return;
	}

	const double mo = 1/d;

	x_v = x_distance * mo * _v;
	y_v = y_distance * mo * _v;
}

void ProjectilePoint::setAiming(int _x, int _y)
{
	x_aiming = _x;
	y_aiming = _y;
}

