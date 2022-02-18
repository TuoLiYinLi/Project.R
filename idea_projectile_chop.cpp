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
			hit_chara(c);
		}
	}

	for (const auto element : *getPhysics()->getHitFacilities())
	{
		if (GameToolkit::checkIfHostile(physics_object->type_ally, element->type_ally) && recorder_facility.record(element))
		{
			const auto f = reinterpret_cast<Facility*>(element->game_object);
			hit_facility(f);
		}
	}
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

void idea_projectile_chop::setup(AllyType _ally, int _position_x, int _position_y, CharaDirection direction, bool _flip)
{
	flag_static = false;

	physics_object->type_ally = _ally;

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

void idea_projectile_chop::hit_chara(Chara* c)
{
	c->onHit();
	c->health -= 2;
	if (c->health < 0)c->health = 0;
}

void idea_projectile_chop::hit_facility(Facility* f)
{
	f->onHit();
	f->health -= 1;
}
