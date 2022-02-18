#include "idea_monster_slime.h"

#include "Defined.h"

idea_monster_slime* idea_monster_slime::createNew()
{
	return new idea_monster_slime();
}

idea_monster_slime::idea_monster_slime()
{
	name = L"ʷ��ķ";
	introduction = L"������ɵĹ�����������ۡ�";
	science_name = L"ʷ��ķ";

	//�趨������
	{
		getPhysicsChara()->bodyX = 1;
		getPhysicsChara()->bodyY = 1;

		getPhysicsChara()->can_fly = false;
		getPhysicsChara()->can_swim = false;
		getPhysicsChara()->steady = false;
	}

	//���ý�ɫ����
	{
		animation_length_idle = 40;
		animation_length_moving = 30;
		animation_length_skill_basic = 40;
		animation_length_skill_special = 40;
		animation_length_disturbed = 40;
		animation_length_dead = 60;

		delay_skill_basic = 0;
		delay_skill_special = 0;

		animation_type_idle = AnimationType::monster_slime_idle;
		animation_type_moving = AnimationType::monster_slime_moving;
		animation_type_skill_basic = AnimationType::monster_slime_eject;
		animation_type_skill_special = AnimationType::monster_slime_absorb;
		animation_type_disturbed = AnimationType::monster_slime_idle;
		animation_type_dead = AnimationType::monster_slime_dead;

		rendering_unit->deltaY = 8;
	}

	//���ý�ɫ����
	{
		moving_speed = low_speed;

		health_max = 4;
		health = 4;
		health_recovery_speed = 0.2 / 60;
		health_recovery_accumulation = 0;

		burning_damage_accumulation = 0;
		poisoned_damage_accumulation = 0;
		oxygen_damage_accumulation = 0;

		stamina_max = 4;
		stamina = 4;
		stamina_recovery_speed = 0.2 / 60;
		stamina_recovery_accumulation = 0;
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

idea_monster_slime::~idea_monster_slime()
{
	
}

void idea_monster_slime::update()
{
	Monster::update();
}

void idea_monster_slime::onBasicSkill()
{
	Monster::onBasicSkill();
}

void idea_monster_slime::onBurning()
{
	Monster::onBurning();
}

void idea_monster_slime::onDead()
{
	Monster::onDead();
}

void idea_monster_slime::onHit()
{
	Monster::onHit();
}

void idea_monster_slime::onIdle()
{
	Monster::onIdle();
}

void idea_monster_slime::onImpact(int _impact)
{
	Monster::onImpact(_impact);
}

void idea_monster_slime::onKill()
{
	Monster::onKill();
}

void idea_monster_slime::onMoving()
{
	Monster::onMoving();
}

void idea_monster_slime::onPoisoned()
{
	Monster::onPoisoned();
}

void idea_monster_slime::onSpecialSkill()
{
	Monster::onSpecialSkill();
}

void idea_monster_slime::decide_action()
{
}
