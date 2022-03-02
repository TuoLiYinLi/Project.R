#include "idea_projectile_chop.h"
#include "PhysicsProjectileFlying.h"

#include "Chara.h"
#include "Facility.h"
#include "GameToolkit.h"


idea_projectile_chop* idea_projectile_chop::createNew()
{
	return new idea_projectile_chop();
}

void idea_projectile_chop::update()
{
	Projectile::update();
	//碰撞Chara
	for (const auto element : *getPhysics()->getHitCharas())
	{
		if (GameToolkit::checkIfHostile(physics_object->type_ally, element->type_ally) && recorder_chara.record(element))
		{
			const auto c = reinterpret_cast<Chara*>(element->game_object);
			c->onHit(this);
		}
	}

	for (const auto element : *getPhysics()->getHitFacilities())
	{
		if (GameToolkit::checkIfHostile(physics_object->type_ally, element->type_ally) && recorder_facility.record(element))
		{
			const auto f = reinterpret_cast<Facility*>(element->game_object);
			f->onHit(this);
		}
	}
}


idea_projectile_chop::idea_projectile_chop()
{
	flag_static = true;
	name = L"projectile_chop";

	//设置物理
	physics_object = PhysicsProjectileFlying::createNew();

	//数据
	damage = 2;
	effect_burning = 0;
	effect_poisoned = 0;

	//设置动画
	animation_type = AnimationType::projectile_chop;
	animation_progress = 0;
	animation_length = 30;

	//寿命
	life_time = 30;
}

void idea_projectile_chop::setup(AllyType _ally, int _position_x, int _position_y, PhysicsDirection direction, bool _flip)
{
	flag_static = false;

	physics_object->type_ally = _ally;

	physics_object->setPosition(_position_x, _position_y);

	switch (direction) { case PhysicsDirection::right:
		getPhysics()->setup(1.0 / 450, 0, 0, 1);
		break;
	case PhysicsDirection::up:
		getPhysics()->setup(0, -1.0 / 450, 0, 1);
		break;
	case PhysicsDirection::left:
		getPhysics()->setup(-1.0 / 450, 0, 0, 1);
		break;
	case PhysicsDirection::down:
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

