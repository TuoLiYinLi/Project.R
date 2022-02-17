#include "idea_projectile_chop.h"

#include "PhysicsProjectileFlying.h"

idea_projectile_chop* idea_projectile_chop::createNew()
{
	return new idea_projectile_chop();
}

idea_projectile_chop::idea_projectile_chop()
{
	flag_static = true;
	name = L"projectile_chop";

	//设置物理
	physics_object = PhysicsProjectileFlying::createNew();

	//设置动画
	animation_type = AnimationType::projectile_chop;
	animation_progress = 0;
	animation_length = 30;

	//寿命
	life_time = 30;
}

idea_projectile_chop::~idea_projectile_chop()
{
	
}

void idea_projectile_chop::setup(int _position_x, int _position_y, CharaDirection direction, bool _flip)
{
	flag_static = false;

	physics_object->setPosition(_position_x, _position_y);

	switch (direction) { case CharaDirection::right:
		getPhysics()->setup(1.0 / 450, 0, 0, 1);
		break;
	case CharaDirection::up:
		getPhysics()->setup(0, -1.0 / 450, 0, 1);
		break;
	case CharaDirection::left:
		getPhysics()->setup(-1.0 / 450, 0, 0, 1);
		break;
	case CharaDirection::down:
		getPhysics()->setup(0, 1.0 / 450, 0, 1);
		break;
	}
	rendering_unit->setFlip(_flip);
	sync_animation();
}


PhysicsProjectileFlying* idea_projectile_chop::getPhysics() const
{
	return reinterpret_cast<PhysicsProjectileFlying*>(physics_object);
}
