#include "Chara.h"

#include "PhysicsChara.h"
#include "Defined.h"
#include "SDL.h"


Chara* Chara::createNew() {
	Chara* c = new Chara();
	if (!c) {
		SDL_Log(u8"���� ����Chara�ڴ治��");
	}
	return c;
}

PhysicsChara* Chara::getPhysicsChara() const
{
	return (PhysicsChara*)physics_object;
}

RenderingAnimation* Chara::getRenderingAnimation() const
{
	return (RenderingAnimation*)animation_unit;
}


void Chara::update()
{
	//���ø�������
	GameObject::update();

	update_attributes();
	update_effect();
	update_animation();
}

void Chara::update_attributes()
{
	//ȼ���˺�
	if (effect_burning > 0)
	{
		onBurning();
		burning_damage_accumulation += BURNING_SPEED;
		const int delta = (int)floor(burning_damage_accumulation);
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
		const int delta = (int)floor(poisoned_damage_accumulation);
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
			const int delta = (int)floor(oxygen_damage_accumulation);
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
		const int delta = (int)floor(health_recovery_accumulation);
		health += delta;
		health_recovery_accumulation -= delta;
		if(health>health_max)
		{
			health = health_max;
		}
	}
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

void Chara::update_animation() {
	if (action_type == CharaActionType::idle)
	{
		onIdle();
	}

	switch (action_type)
	{
	case CharaActionType::idle:
		//��ǰ������״̬
		{
			if (getPhysicsChara()->getIfFalling()
			|| getPhysicsChara()->getIfHitBack())
			{
				//��ɫ�������ܵ����
				setAnimationDisturbed();
			}
			else if (getIfMoving())
			{
				//��ɫ���������������˶�
				setAnimationMoving();
			}
			else if (animation_progress >= animation_length_idle)
			{
				//�ظ����ö���
				animation_progress = 0;
			}
			getRenderingAnimation()->setTexture(animation_type_idle, animation_length_idle, animation_progress);
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
				//�˳��ƶ�����
				setAnimationIdle();
			}
			getRenderingAnimation()->setTexture(animation_type_moving, animation_length_moving, animation_progress);
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
			getRenderingAnimation()->setTexture(animation_type_disturbed, animation_length_disturbed, animation_progress);
		}
		break;

	case CharaActionType::skill_basic:
		{
			if(animation_progress == trigger_CD_skill_basic)
			{
				onBasicSkill();
			}

			//ʹ�û�������״̬
			if (getIfDisturbed())
			{
				//��ɫ�������ܵ����
				setAnimationDisturbed();
			}
			else if (animation_progress >= animation_length_skill_basic)
			{
				setAnimationIdle();
			}
			getRenderingAnimation()->setTexture(animation_type_skill_basic, animation_length_skill_basic, animation_progress);
		}
		break;

	case CharaActionType::skill_special:
		{
			if (animation_progress == trigger_CD_skill_special)
			{
				onSpecialSkill();
			}
			//ʹ����������״̬
			if (getIfDisturbed())
			{
				//��ɫ�������ܵ����
				setAnimationDisturbed();
			}
			else if (animation_progress >= animation_length_skill_special)
			{
				setAnimationIdle();
			}
			getRenderingAnimation()->setTexture(animation_type_skill_special, animation_length_skill_special, animation_progress);
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
				return;
			}else
			{
				getRenderingAnimation()->setTexture(animation_type_dead, animation_length_dead, animation_progress);
			}
		}
		break;
	}

	//�ƽ�����
	animation_progress++;

	//ˢ�½�ɫ����
	if (getPhysicsChara()->getDirection() == CharaDirection::right)
	{
		getRenderingAnimation()->setFlip(false);
	}else if(getPhysicsChara()->getDirection() == CharaDirection::left)
	{
		getRenderingAnimation()->setFlip(true);
	}

	//ˢ�½�ɫλ��
	getRenderingAnimation()->x = getPhysicsChara()->X;
	getRenderingAnimation()->y = getPhysicsChara()->Y;
	getRenderingAnimation()->width = getPhysicsChara()->bodyX * PIXEL_RATE;
	getRenderingAnimation()->height = getPhysicsChara()->bodyY * PIXEL_RATE;

	//ˢ�����
	animation_unit->depth = RENDERING_DEPTH_WORLD_CHARA + (float)physics_object->Y;

}

int Chara::chara_num = 0;

Chara::Chara()
{
	chara_num++;

	name = u8"default_character";
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
		animation_unit = RenderingAnimation::createNew();
		animation_unit->depth = RENDERING_DEPTH_WORLD_CHARA;

		animation_progress = 0;

		animation_length_idle = 40;
		animation_length_moving = 30;
		animation_length_skill_basic = 40;
		animation_length_skill_special = 40;
		animation_length_disturbed = 40;
		animation_length_dead = 60;

		trigger_CD_skill_basic = 0;
		trigger_CD_skill_special = 0;

		animation_type_idle = AnimationType::charaSlimeIdle;
		animation_type_moving = AnimationType::charaSlimeMove;
		animation_type_skill_basic = AnimationType::default_banned;
		animation_type_skill_special = AnimationType::default_banned;
		animation_type_disturbed = AnimationType::charaSlimeIdle;
		animation_type_dead = AnimationType::charaSlimeDeath;
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

		magic_max = 4;
		magic = 4;
		magic_recovery_speed = 0.2/60;
		magic_recovery_accumulation = 0;

		stamina_max = 4;
		stamina = 4;
		stamina_recovery_speed = 0.2/60;
		stamina_recovery_accumulation = 0;
		
		oxygen = OXYGEN_MAX;//����ֵ
	}

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
	getRenderingAnimation()->setTexture(animation_type_idle, 0, 0);
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
}



void Chara::actMove(CharaDirection d) const
{
	if (action_type != CharaActionType::idle)return;
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

void Chara::onImpact()
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

