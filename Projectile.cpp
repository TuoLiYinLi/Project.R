#include "Projectile.h"
#include "Defined.h"
#include "PhysicsProjectile.h"

void Projectile::update()
{
	//推进动画
	animation_progress++;
	if (animation_progress >= animation_length)
	{
		animation_progress = 0;
	}

	//刷新动画的材质
	sync_animation();

	//寿命倒计时
	life_time--;
	if(life_time<=0)
	{
		readyToDestroy();
	}
}

void Projectile::sync_animation() const
{
	rendering_unit->x = physics_object->X;
	rendering_unit->y = physics_object->Y;

	getRenderingAnimation()->setTexture(animation_type, animation_length, animation_progress);
}

void Projectile::sync_flip() const
{
	const auto j = reinterpret_cast<PhysicsProjectile*>(physics_object)->x_v;
	if(j<0)
	{
		rendering_unit->setFlip(true);
	}
	else if(j>0)
	{
		rendering_unit->setFlip(false);
	}
}



void Projectile::update_depth() const
{
	rendering_unit->depth = DEPTH_WORLD_PROJECTILE + static_cast<float>(rendering_unit->y + rendering_unit->deltaY + rendering_unit->height / 2);
}


RenderingAnimation* Projectile::getRenderingAnimation() const
{
	return reinterpret_cast<RenderingAnimation*>(rendering_unit);
}

int Projectile::projectile_num = 0;

int Projectile::getProjectileNum()
{
	return projectile_num;
}

Projectile::Projectile()
{
	projectile_num ++;

	flag_static = true;

	name = L"default_projectile";

	type_game_object = GameObjectType::default_projectile;

	//动画
	rendering_unit = RenderingAnimation::createNew();
	animation_length = 60;
	animation_progress = 0;
	animation_type = AnimationType::debug_sequence_yellow;

	getRenderingAnimation()->setTexture(animation_type, animation_length, animation_progress);

	//物理

	//寿命
	life_time = 300;

	
}

Projectile::~Projectile()
{
	projectile_num--;
}