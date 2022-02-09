#include "Facility.h"

#include "Defined.h"
#include "SDL.h"
#include "PhysicsFacility.h"

Facility* Facility::createNew() {
	return new Facility();
}

int Facility::facility_num = 0;

int Facility::getFacilityNum()
{
	return facility_num;
}

Facility::Facility() {
	facility_num++;

	name = L"default_facility";
	type_game_object = GameObjectType::default_facility;

	flag_static = true;

	//绑定物理体
	{
		physics_object = PhysicsFacility::createNew();
		physics_object->game_object = this;

		physics_object->type_ally = AllyType::peace;

		physics_object->bodyX = 1;
		physics_object->bodyY = 1;

		getPhysicsFacility()->setFacilityType(BlockingType::air);
	}

	//设施的动画
	{
		rendering_unit = RenderingAnimation::createNew();

		state = FacilityState::idle;
		animation_progress = 0;

		animation_length_idle = 0;
		animation_length_activated = 0;
		animation_length_dead = 0;

		activate_length = 0;
		activate_CD = 0;

		delay_activate = 0;

		animation_type_idle = AnimationType::debug_sequence_blue;
		animation_type_activated = AnimationType::debug_sequence_red;
		animation_type_dead = AnimationType::debug_sequence_black;

		setAnimationIdle();
	}

	//设施的数值
	{
		health = 8;

		counting_container = CountingContainer::createNew();
	}


}


Facility::~Facility() {
	counting_container->destroy();
	counting_container = nullptr;

	facility_num--;
}



void Facility::update()
{
	update_animation();
	sync_animation();
}

void Facility::update_depth()const
{
	rendering_unit->depth = DEPTH_WORLD_FACILITY + static_cast<float>(physics_object->Y);

}

void Facility::update_animation()
{
	animation_progress++;
	switch (state)
	{
	case FacilityState::idle:
		{
			//激活设施
			activate_CD++;
			if (activate_CD >= activate_length)
			{
				setAnimationActivate();
			}

			if (animation_progress >= animation_length_idle)
			{
				//重复闲置动画
				animation_progress = 0;
			}
			onIdle();
		}
		break;
	case FacilityState::activated:
		{
			if (animation_progress == delay_activate)
			{
				onActivate();
			}
			if(animation_progress>=animation_length_activated)
			{
				setAnimationIdle();
			}
		}
		break;
	case FacilityState::dead:
		{
			if(animation_progress>=animation_length_dead)
			{
				//已经播放完死亡动画
				onDead();
				flag_destroy = true;
				flag_static = true;
			}
		}
		break;
	}
}

void Facility::sync_animation()const
{
	switch (state)
	{
	case FacilityState::idle:
		getRenderingAnimation()->setTexture(animation_type_idle, animation_length_idle, animation_progress);
		break;
	case FacilityState::activated:
		getRenderingAnimation()->setTexture(animation_type_activated, animation_length_activated, animation_progress);
		break;
	case FacilityState::dead:
		getRenderingAnimation()->setTexture(animation_type_dead, animation_length_dead, animation_progress);
		break;
	}

	//刷新设施位置
	getRenderingAnimation()->x = physics_object->X;
	getRenderingAnimation()->y = physics_object->Y;
	getRenderingAnimation()->width = physics_object->bodyX * PIXEL_RATE;
	getRenderingAnimation()->height = physics_object->bodyY * PIXEL_RATE;

	//刷新深度
	update_depth();
}


void Facility::setPosition(int x, int y)
{
	physics_object->setPosition(x, y);
	setAnimationIdle();
	sync_animation();
}


void Facility::onIdle()
{
	
}

void Facility::onActivate()
{
	
}

void Facility::onKill()
{
	
}

void Facility::onHit()
{
	
}

void Facility::onDead()
{
	
}

RenderingAnimation* Facility::getRenderingAnimation() const
{
	return reinterpret_cast<RenderingAnimation*>(rendering_unit);
}

PhysicsFacility* Facility::getPhysicsFacility() const
{
	return reinterpret_cast<PhysicsFacility*>(physics_object);
}


void Facility::setAnimationIdle()
{
	state = FacilityState::idle;
	animation_progress = 0;
}

void Facility::setAnimationActivate()
{
	state = FacilityState::activated;
	animation_progress = 0;
}

void Facility::setAnimationDead()
{
	onKill();
	state = FacilityState::dead;
	animation_progress = 0;
}
