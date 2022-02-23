#include "idea_projectile_little_slime_ball.h"
#include "PhysicsChara.h"
#include "PhysicsFacility.h"
#include "Chara.h"
#include "Facility.h"
#include "GameToolkit.h"

idea_projectile_little_slime_ball* idea_projectile_little_slime_ball::createNew()
{
	return new idea_projectile_little_slime_ball();
}

void idea_projectile_little_slime_ball::update()
{
	Projectile::update();
	//碰撞Chara
	for (const auto element : *getPhysics()->getHitCharas())
	{
		if (GameToolkit::checkIfHostile(physics_object->type_ally, element->type_ally))
		{
			const auto c = reinterpret_cast<Chara*>(element->game_object);
			c->onHit(this);
			readyToDestroy();
			return;
		}
	}

	if(getPhysics()->detectLocal(BlockingType::solid))
	{
		for (const auto element : *getPhysics()->getHitFacilities())
		{
			if (GameToolkit::checkIfHostile(physics_object->type_ally, element->type_ally))
			{
				const auto f = reinterpret_cast<Facility*>(element->game_object);
				f->onHit(this);
				break;
			}
		}
		readyToDestroy();
	}
}

void idea_projectile_little_slime_ball::setup(AllyType _ally, int _position_x, int _position_y,
                                              bool direction_right)
{
	flag_static = false;

	physics_object->type_ally = _ally;

	physics_object->setPosition(_position_x, _position_y);

	if(direction_right)
	{
		getPhysics()->x_v = 0.03;
	}else
	{
		getPhysics()->x_v = -0.03;
	}

	rendering_unit->setFlip(!direction_right);
	sync_animation();
}

PhysicsProjectile* idea_projectile_little_slime_ball::getPhysics() const
{
	return reinterpret_cast<PhysicsProjectile*>(physics_object);
}

idea_projectile_little_slime_ball::idea_projectile_little_slime_ball()
{
	flag_static = true;
	name = L"projectile_chop";

	//设置物理
	physics_object = PhysicsProjectile::createNew();

	//数据
	damage = 1;
	effect_burning = 0;
	effect_poisoned = 0;

	//设置动画
	animation_type = AnimationType::projectile_little_slime_ball;
	animation_progress = 0;
	animation_length = 20;

	//寿命
	life_time = 100;
}

