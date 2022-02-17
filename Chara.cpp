#include "Chara.h"

#include "PhysicsChara.h"
#include "Defined.h"
#include "GameToolkit.h"
#include "idea_UI_inspector.h"
#include "SDL.h"


Chara* Chara::createNew()
{
	return new Chara();
}

PhysicsChara* Chara::getPhysicsChara() const
{
	return dynamic_cast<PhysicsChara*>(physics_object);
}

RenderingAnimation* Chara::getRenderingAnimation() const
{
	return dynamic_cast<RenderingAnimation*>(rendering_unit);
}

std::wstring Chara::getBrief()
{
	return name;
}

SDL_Texture* Chara::getThumbnail()
{
	return rendering_unit->getTexture();
}

std::wstring Chara::getMainInfo()
{
	std::wstring s = L"[ѧ��] " + science_name + L"\n"
		+ L"[�ǳ�] " + name + L"\n"
		+ L"[����] " + introduction;
	return s;
}

std::wstring Chara::getDataInfo()
{
	std::wstring s = L"[����] " + std::to_wstring(health) + L"/" + std::to_wstring(health_max) + L" (+" + std::to_wstring(health_recovery_speed * 60).substr(0, 4) + L"/s)" + L'\n'
		+ L"[����] " + std::to_wstring(stamina) + L"/" + std::to_wstring(stamina_max) + L" (+" + std::to_wstring(stamina_recovery_speed * 60).substr(0, 4) + L"/s)" + L'\n'
		+ L"[����] " + std::to_wstring(static_cast<int>(static_cast<double>(oxygen) / OXYGEN_MAX * 100)) + L"%" + L'\n'
		+ L"[λ��] " + L"( " + GameToolkit::double_reserve_decimal(physics_object->X, 1) + L" , " + GameToolkit::double_reserve_decimal(physics_object->Y, 1) + L" )" + L'\n'
		+ L"[��С] " + L"( " + std::to_wstring(physics_object->bodyX) + L" " + wchar_multiply + L" " + std::to_wstring(physics_object->bodyY) + L" )" + L'\n';

	std::wstring s_action = L"[�ж�] ";
	switch (action_type)
	{
	case CharaActionType::idle:
		s_action += L"����";
		break;
	case CharaActionType::skill_basic:
		s_action += L"ʹ�û�������";
		break;
	case CharaActionType::skill_special:
		s_action += L"ʹ����������";
		break;
	case CharaActionType::dead:
		s_action += L"����";
		break;
	case CharaActionType::disturbed:
		if (getPhysicsChara()->getIfHitBack())
		{
			s_action += L"������";
		}else if (getPhysicsChara()->getIfFalling())
		{
			s_action += L"׹��";
		}else
		{
			s_action += L"������";
		}
		break;
	case CharaActionType::moving:
		switch (getPhysicsChara()->getDirection())
		{
		case CharaDirection::up:
			s_action += L"�����ƶ�";
			break;
		case CharaDirection::down:
			s_action += L"�����ƶ�";
			break;
		case CharaDirection::left:
			s_action += L"�����ƶ�";
			break;
		case CharaDirection::right:
			s_action += L"�����ƶ�";
			break;
		}
		break;
	}
	s += s_action + L"\n";

	return s;
}

std::wstring Chara::getExtraInfo()
{
	std::wstring s;

	std::wstring s_statement= L"[״̬] ";
	if (effect_burning > 0)
	{
		s_statement += L"\n  <ȼ��> " + GameToolkit::double_reserve_decimal(static_cast<double>(effect_burning) / 60, 1) + L's';
	}
	if (effect_blind > 0)
	{
		s_statement += L"\n  <äĿ> " + GameToolkit::double_reserve_decimal(static_cast<double>(effect_blind) / 60, 1) + L's';
	}
	if (effect_charging > 0)
	{
		s_statement += L"\n  <����> " + GameToolkit::double_reserve_decimal(static_cast<double>(effect_charging) / 60, 1) + L's';
	}
	if (effect_dizzy > 0)
	{
		s_statement += L"\n  <ѣ��> " + GameToolkit::double_reserve_decimal(static_cast<double>(effect_dizzy) / 60, 1) + L's';
	}
	if (effect_poisoned > 0)
	{
		s_statement += L"\n  <ȼ��> " + GameToolkit::double_reserve_decimal(static_cast<double>(effect_poisoned) / 60, 1) + L's';
	}
	if (effect_resistant > 0)
	{
		s_statement += L"\n  <�ֿ�> " + GameToolkit::double_reserve_decimal(static_cast<double>(effect_resistant) / 60, 1) + L's';
	}
	if (effect_sealed > 0)
	{
		s_statement += L"\n  <��ӡ> " + GameToolkit::double_reserve_decimal(static_cast<double>(effect_sealed) / 60, 1) + L's';
	}
	s += s_statement;

	std::wstring s_counting = L"\n[������]";

	for (const auto type : counting_container->getAllTypes())
	{
		const auto n = CountingContainer::get_name(type);

		s_counting += L"\n  <" + n + L"> " + std::to_wstring(counting_container->getNumOf(type));
	}

	s += s_counting + L"\n";

	return s;
}


void Chara::update()
{
	//���ø�������
	GameObject::update();
	//����onImpact
	const int _impact = getPhysicsChara()->getImpact();
	if(_impact>0)onImpact(_impact);

	update_effect();
	update_attributes();
	update_animation();

	sync_animation();
}

void Chara::update_effect()
{
	//����Ч��
	if (effect_charging > 0)
	{
		effect_charging--;
	}
	else
	{
		effect_charging = 0;
	}

	//�ֿ�Ч��ʱ��
	if (effect_resistant > 0)
	{
		effect_resistant--;
	}
	else
	{
		effect_resistant = 0;
	}

	//�ж�Ч��ʱ��
	if (effect_poisoned > 0)
	{
		effect_poisoned--;
	}
	else
	{
		effect_poisoned = 0;
	}

	//ȼ��Ч��
	if(effect_burning>0)
	{
		effect_burning--;
	}else
	{
		effect_burning = 0;
	}

	//��ӡЧ��
	if (effect_sealed > 0)
	{
		effect_sealed--;
	}
	else
	{
		effect_sealed = 0;
	}

	//äĿЧ��
	if (effect_blind > 0)
	{
		effect_blind--;
	}
	else
	{
		effect_blind = 0;
	}

	//ѣ��Ч��
	if (effect_dizzy > 0)
	{
		effect_dizzy--;
	}
	else
	{
		effect_dizzy = 0;
	}
}

void Chara::update_attributes()
{
	//ȼ���˺�
	if (effect_burning > 0)
	{
		onBurning();
		burning_damage_accumulation += BURNING_SPEED;
		const int delta = static_cast<int>(floor(burning_damage_accumulation));
		health -= delta;
		burning_damage_accumulation -= delta;
		if(health<0)
		{
			health = 0;
		}
	}else
	{
		burning_damage_accumulation = 0;
	}

	//�ж�Ч��
	if (effect_poisoned > 0)
	{
		onPoisoned();
		poisoned_damage_accumulation += health * POISONED_SPEED;
		const int delta = static_cast<int>(floor(poisoned_damage_accumulation));
		health -= delta;
		poisoned_damage_accumulation -= delta;
		if(health<0)
		{
			health = 0;
		}
	}else
	{
		poisoned_damage_accumulation = 0;
	}

	//����ϵͳ
	if(getPhysicsChara()->detectSubmersed())
	{
		//��ˮ��û
		oxygen--;
		if(oxygen<0)
		{
			//ȱ��
			oxygen = 0;
			oxygen_damage_accumulation += health_max * OXYGEN_DAMAGE;
			const int delta = static_cast<int>(floor(oxygen_damage_accumulation));
			health -= delta;
			oxygen_damage_accumulation -= delta;
			if (health < 0)
			{
				health = 0;
			}
		}
	}else
	{
		//��û�б�ˮ��û
		oxygen++;
		if (oxygen>OXYGEN_MAX)
		{
			oxygen = OXYGEN_MAX;
		}
		oxygen_damage_accumulation = 0;
	}

	if(health<=0&&action_type!=CharaActionType::dead)
	{
		setAnimationDead();
	}

	//����ֵ�ָ�
	if (effect_poisoned <= 0)
	{
		health_recovery_accumulation += health_recovery_speed;
		const int delta = static_cast<int>(floor(health_recovery_accumulation));
		health += delta;
		health_recovery_accumulation -= delta;
		if(health>health_max)
		{
			health = health_max;
		}
	}
}

void Chara::update_animation() {

	//�ƽ�����
	animation_progress++;

	if (action_type != CharaActionType::disturbed && getIfDisturbed() && action_type != CharaActionType::dead)
	{
		setAnimationDisturbed();
	}else if (action_type == CharaActionType::idle)
	{
		decide_action();
	}

	switch (action_type)
	{
	case CharaActionType::idle:
		onIdle();
		//��ǰ������״̬
		{
			if (animation_progress >= animation_length_idle)
			{
				//�ظ����ö���
				animation_progress = 0;
			}
		}
		break;

	case CharaActionType::moving:
		onMoving();
		{
			//�����ƶ�״̬
			if (getIfMoving())
			{
				//��Ȼ�����˶�״̬
				if (animation_progress >= animation_length_moving)
				{
					animation_progress = 0;
				}
			}
			else
			{
				setAnimationIdle();
			}
		}
		break;

	case CharaActionType::disturbed:
		{
			//�����״̬
			if (getIfDisturbed())
			{
				//��Ȼ���ڱ����״̬
				if (animation_progress >= animation_length_disturbed)
				{
					animation_progress = 0;
				}
			}
			else
			{
				//�˳���϶���
				setAnimationIdle();
			}
		}
		break;

	case CharaActionType::skill_basic:
		{
			if(animation_progress == delay_skill_basic)
			{
				onBasicSkill();
			}

			if (animation_progress >= animation_length_skill_basic)
			{
				setAnimationIdle();
			}
		}
		break;

	case CharaActionType::skill_special:
		{
			if (animation_progress == delay_skill_special)
			{
				onSpecialSkill();
			}

			if (animation_progress >= animation_length_skill_special)
			{
				setAnimationIdle();
			}
		}
		break;

	case CharaActionType::dead:
		{
			//����״̬
			if (animation_progress >= animation_length_dead)
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

void Chara::decide_action()
{
	
}

void Chara::sync_animation()
{
	switch (action_type)
	{
	case CharaActionType::idle:
		//��ǰ������״̬
	{
		getRenderingAnimation()->setTexture(animation_type_idle, animation_length_idle, animation_progress);
	}
	break;

	case CharaActionType::moving:
		onMoving();
		{
			getRenderingAnimation()->setTexture(animation_type_moving, animation_length_moving, animation_progress);
		}
		break;

	case CharaActionType::disturbed:
	{
		getRenderingAnimation()->setTexture(animation_type_disturbed, animation_length_disturbed, animation_progress);
	}
	break;

	case CharaActionType::skill_basic:
	{
		getRenderingAnimation()->setTexture(animation_type_skill_basic, animation_length_skill_basic, animation_progress);
	}
	break;

	case CharaActionType::skill_special:
	{
		getRenderingAnimation()->setTexture(animation_type_skill_special, animation_length_skill_special, animation_progress);
	}
	break;

	case CharaActionType::dead:
	{
		getRenderingAnimation()->setTexture(animation_type_dead, animation_length_dead, animation_progress);
	}
	break;
	}

	//ˢ�½�ɫ����
	if (getPhysicsChara()->getDirection() == CharaDirection::right)
	{
		getRenderingAnimation()->setFlip(false);
	}
	else if (getPhysicsChara()->getDirection() == CharaDirection::left)
	{
		getRenderingAnimation()->setFlip(true);
	}

	//ˢ�½�ɫλ��
	getRenderingAnimation()->x = getPhysicsChara()->X;
	getRenderingAnimation()->y = getPhysicsChara()->Y;
	getRenderingAnimation()->width = getPhysicsChara()->bodyX * PIXEL_RATE;
	getRenderingAnimation()->height = getPhysicsChara()->bodyY * PIXEL_RATE;

	//ˢ�����
	update_depth();
}

void Chara::update_depth()const
{
	rendering_unit->depth = DEPTH_WORLD_CHARA + static_cast<float>(physics_object->Y);
}




int Chara::chara_num = 0;

Chara::Chara()
{
	chara_num++;

	name = L"default_character";
	science_name = L"Ĭ��ѧ��";
	introduction = L"Ĭ�Ͻ���";

	type_game_object = GameObjectType::default_chara;

	action_type = CharaActionType::idle;

	//�趨������
	{
		physics_object = PhysicsChara::createNew();
		physics_object->game_object = this;

		physics_object->type_ally = AllyType::neutral;

		getPhysicsChara()->bodyX = 1;
		getPhysicsChara()->bodyY = 1;

		getPhysicsChara()->can_fly = false;
		getPhysicsChara()->can_swim = false;
		getPhysicsChara()->steady = false;
	}

	//���ý�ɫ����
	{
		rendering_unit = RenderingAnimation::createNew();

		sync_animation();

		animation_progress = 0;

		animation_length_idle = 40;
		animation_length_moving = 30;
		animation_length_skill_basic = 40;
		animation_length_skill_special = 40;
		animation_length_disturbed = 40;
		animation_length_dead = 60;

		delay_skill_basic = 0;
		delay_skill_special = 0;

		animation_type_idle = AnimationType::debug_sequence_white;
		animation_type_moving = AnimationType::debug_sequence_white;
		animation_type_skill_basic = AnimationType::debug_sequence_blue;
		animation_type_skill_special = AnimationType::debug_sequence_red;
		animation_type_disturbed = AnimationType::debug_sequence_green;
		animation_type_dead = AnimationType::debug_sequence_black;
	}

	//���ý�ɫ����
	{
		moving_speed = LOW_SPEED;

		health_max = 4;
		health = 4;
		health_recovery_speed = 0.2/60;
		health_recovery_accumulation = 0;

		burning_damage_accumulation = 0;
		poisoned_damage_accumulation = 0;
		oxygen_damage_accumulation = 0;

		stamina_max = 4;
		stamina = 4;
		stamina_recovery_speed = 0.2/60;
		stamina_recovery_accumulation = 0;
		
		oxygen = OXYGEN_MAX;//����ֵ
	}
	//��ɫ������
	counting_container = CountingContainer::createNew();

	//���ý�ɫЧ��
	{
		effect_charging = 0;
		effect_resistant = 0;
		effect_poisoned = 0;
		effect_burning = 0;
		effect_sealed = 0;
		effect_blind = 0;
		effect_dizzy = 0;
	}

}

Chara::~Chara()
{
	push_nullptr();

	counting_container->destroy();
	counting_container = nullptr;

	chara_num--;
}

void Chara::setAnimationIdle()
{
	action_type = CharaActionType::idle;
	animation_progress = 0;
}

void Chara::setAnimationDead()
{
	onKill();
	action_type = CharaActionType::dead;
	animation_progress = 0;
}

void Chara::setAnimationDisturbed()
{
	action_type = CharaActionType::disturbed;
	animation_progress = 0;
}


int Chara::getCharaNum()
{
	return chara_num;
}

void Chara::setAnimationSkillBasic()
{
	action_type = CharaActionType::skill_basic;
	animation_progress = 0;
}

void Chara::setAnimationSkillSpecial()
{
	action_type = CharaActionType::skill_special;
	animation_progress = 0;
}

void Chara::setAnimationMoving()
{
	action_type = CharaActionType::moving;
	animation_progress = 0;
}

bool Chara::getIfDisturbed() const
{
	return getPhysicsChara()->getIfFalling()
		||getPhysicsChara()->getIfHitBack();
}

bool Chara::getIfMoving() const
{
	return getPhysicsChara()->getIfMoving()
		&& !getPhysicsChara()->getIfFalling()
		&& !getPhysicsChara()->getIfHitBack();
}

bool Chara::setDirection(CharaDirection d) const
{
	return getPhysicsChara()->setDirection(d);
}

void Chara::setPosition(int x, int y)
{
	getPhysicsChara()->setPosition(x, y);
	//���ö���
	this->setAnimationIdle();
	sync_animation();
}



void Chara::actMove(CharaDirection d)
{
	if (action_type != CharaActionType::idle)return;
	setAnimationMoving();
	getPhysicsChara()->setMotion(d, moving_speed, 1, false);
}

void Chara::actSkillBasic(CharaDirection d)
{
	if (setDirection(d) && action_type == CharaActionType::idle)
	setAnimationSkillBasic();
}

void Chara::actSkillSpecial(CharaDirection d)
{
	if (setDirection(d)&& action_type == CharaActionType::idle)
	setAnimationSkillSpecial();
}

void Chara::onBasicSkill()
{
	
}

void Chara::onBurning()
{
	
}

void Chara::onDead()
{

}

void Chara::onHit()
{
	
}

void Chara::onIdle()
{

}

void Chara::onImpact(int _impact)
{
	
}

void Chara::onKill()
{
	
}


void Chara::onMoving()
{
	
}

void Chara::onPoisoned()
{
	
}

void Chara::onSpecialSkill()
{
	
}

