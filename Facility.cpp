#include "Facility.h"

#include "Defined.h"
#include "GameToolkit.h"
#include "GlobalData.h"
#include "SDL.h"
#include "PhysicsFacility.h"
#include "idea_UI_inspector.h"

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
	science_name = L"默认学名";
	introduction = L"默认介绍";

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
		health_max = 8;

		counting_container = CountingContainer::createNew();
	}


}


Facility::~Facility() {
	push_nullptr();

	counting_container->destroy();
	counting_container = nullptr;

	facility_num--;
}

std::wstring Facility::getBrief()
{
	return name;
}

SDL_Texture* Facility::getThumbnail()
{
	return rendering_unit->getTexture();
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

std::wstring Facility::getDataInfo()
{
	std::wstring s = L"[生命] " + std::to_wstring(health) + L"/" + std::to_wstring(health_max) + L"\n"
		+ L"[位置] " + L"( " + std::to_wstring(static_cast<int>(physics_object->X)) + L" , " + std::to_wstring(static_cast<int>(physics_object->Y)) + L" )" + L'\n'
		+ L"[大小] " + L"( " + std::to_wstring(physics_object->bodyX) + L" " + wchar_multiply + L" " + std::to_wstring(physics_object->bodyY) + L" )" + L'\n';
		

	std::wstring s_state = L"[状态] ";
	switch (state)
	{
	case FacilityState::idle:
		s_state += L"闲置";
		break;
	case FacilityState::activated:
		s_state += L"激活";
		break;
	case FacilityState::dead:
		s_state += L"被破坏";
		break;
	}
	s += s_state + L"\n";

	return s;
}

std::wstring Facility::getExtraInfo()
{
	std::wstring s ;

	std::wstring s_counting = L"[计数物]";

	for (const auto type : counting_container->getAllTypes())
	{
		const auto n= CountingContainer::get_name(type);

		s_counting += L"\n  <" + n + L"> " + std::to_wstring(counting_container->getNumOf(type));
	}
	
	s += s_counting + L"\n";

	return s;
}

std::wstring Facility::getMainInfo()
{
	std::wstring s = L"[名称] " + science_name + L"\n"
		+ L"[介绍] " + introduction;
	return s;
}
