#include "Facility.h"

#include "Defined.h"
#include "GameToolkit.h"
#include "SDL.h"
#include "PhysicsFacility.h"
#include "Projectile.h"

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
	science_name = L"Ĭ��ѧ��";
	introduction = L"Ĭ�Ͻ���";

	type_game_object = GameObjectType::default_facility;
	type_facility = FacilityType::default_facility;

	flag_static = true;

	//��������
	{
		physics_object = PhysicsFacility::createNew();
		physics_object->game_object = this;

		physics_object->type_ally = AllyType::peace;

		physics_object->bodyX = 1;
		physics_object->bodyY = 1;

		getPhysics()->setFacilityType(BlockingType::air);
	}

	//��ʩ�Ķ���
	{
		rendering_unit = RenderingAnimation::createNew();
		extra_depth = 0;

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

		damaged_highlight = 0;

		setAnimationIdle();
	}

	//��ʩ����ֵ
	{
		health = 8;
		health_max = 8;

		counting_container = integration_counting_container();
	}


}


Facility::~Facility() {
	push_nullptr();

	facility_num--;
}

std::wstring Facility::getBrief()
{
	return science_name;
}

SDL_Texture* Facility::getThumbnail()
{
	return rendering_unit->getTexture();
}


void Facility::update()
{
	update_animation();
	update_damaged_highlight();
	sync_animation();
}

void Facility::update_depth()const
{
	rendering_unit->depth = depth_world_facility + static_cast<float>(physics_object->Y) + extra_depth;

}

void Facility::update_animation()
{
	animation_progress++;
	switch (state)
	{
	case FacilityState::idle:
		{
			//������ʩ
			if(activate_length>0){
				activate_CD++;
				if (activate_CD >= activate_length)
				{
					setAnimationActivate();
				}
			}

			if (animation_progress >= animation_length_idle)
			{
				//�ظ����ö���
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
				//�Ѿ���������������
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
		getRendering()->setTexture(animation_type_idle, animation_length_idle, animation_progress);
		break;
	case FacilityState::activated:
		getRendering()->setTexture(animation_type_activated, animation_length_activated, animation_progress);
		break;
	case FacilityState::dead:
		getRendering()->setTexture(animation_type_dead, animation_length_dead, animation_progress);
		break;
	}

	//ˢ����ʩλ��
	getRendering()->x = physics_object->X;
	getRendering()->y = physics_object->Y;
	getRendering()->width = physics_object->bodyX * PIXEL_RATE;
	getRendering()->height = physics_object->bodyY * PIXEL_RATE;

	//ˢ�����
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

void Facility::onHit(Projectile* p)
{
	if(p->damage)
	health --;
	damaged_highlight = damaged_highlight_length;
	if(health<=0)
	{
		readyToDestroy();
	}
}

void Facility::onDead()
{
	
}

RenderingAnimation* Facility::getRendering() const
{
	return reinterpret_cast<RenderingAnimation*>(rendering_unit);
}

PhysicsFacility* Facility::getPhysics() const
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
	std::wstring s;
	if (getPhysics()->type_ally == AllyType::peace)
		s = std::wstring(L"[����] �����ƻ�\n")
		+ L"[λ��] " + L"( " + std::to_wstring(static_cast<int>(physics_object->X)) + L" , " + std::to_wstring(static_cast<int>(physics_object->Y)) + L" )" + L'\n'
		+ L"[��С] " + L"( " + std::to_wstring(physics_object->bodyX) + L" " + wchar_multiply + L" " + std::to_wstring(physics_object->bodyY) + L" )" + L'\n';

	else
		s = L"[����] " + std::to_wstring(health) + L"/" + std::to_wstring(health_max) + L"\n"
		+ L"[λ��] " + L"( " + std::to_wstring(static_cast<int>(physics_object->X)) + L" , " + std::to_wstring(static_cast<int>(physics_object->Y)) + L" )" + L'\n'
		+ L"[��С] " + L"( " + std::to_wstring(physics_object->bodyX) + L" " + wchar_multiply + L" " + std::to_wstring(physics_object->bodyY) + L" )" + L'\n';
		

	std::wstring s_state = L"[״̬] ";
	switch (state)
	{
	case FacilityState::idle:
		s_state += L"����";
		break;
	case FacilityState::activated:
		s_state += L"����";
		break;
	case FacilityState::dead:
		s_state += L"���ƻ�";
		break;
	}
	s += s_state + L"\n";

	std::wstring s_ally = L"[����] ";
	switch (physics_object->type_ally)
	{
	case AllyType::monster:s_ally += L"�ѷ�"; break;
	case AllyType::warrior:s_ally += L"�з�"; break;
	case AllyType::neutral:s_ally += L"����"; break;
	case AllyType::peace:s_ally += L"��ƽ"; break;
	}
	s += s_ally + L"\n";

	return s;
}

std::wstring Facility::getExtraInfo()
{
	std::wstring s ;

	std::wstring s_counting = L"[������]";

	for (const auto type : counting_container.getAllTypes())
	{
		const auto n= integration_counting_container::getName(type);

		s_counting += L"\n  <" + n + L"> " + std::to_wstring(counting_container.getNumOf(type));
	}
	
	s += s_counting + L"\n";

	return s;
}

std::wstring Facility::getMainInfo()
{
	std::wstring s = L"[����] " + science_name + L"\n"
		+ L"[����] " + introduction;
	return s;
}

void Facility::update_damaged_highlight()
{
	if (damaged_highlight > 0)
	{
		damaged_highlight--;

		rendering_unit->blend_color.b = 64;
		rendering_unit->blend_color.g = 0;
	}
	else
	{
		rendering_unit->blend_color.b = 255;
		rendering_unit->blend_color.g = 255;
	}
}
