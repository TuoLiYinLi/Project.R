#include "idea_monster_slime.h"

#include "Defined.h"

idea_monster_slime* idea_monster_slime::createNew()
{
	return new idea_monster_slime();
}

idea_monster_slime::idea_monster_slime()
{
	name = L"史莱姆";
	introduction = L"软泥组成的怪物，脆弱但廉价。\n*不会受到冲击伤害。";
	science_name = L"史莱姆";

	//设定物理体
	{
		getPhysicsChara()->bodyX = 1;
		getPhysicsChara()->bodyY = 1;

		getPhysicsChara()->can_fly = false;
		getPhysicsChara()->can_swim = false;
		getPhysicsChara()->steady = false;
	}

	//设置角色动画
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

	//设置角色属性
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

		injured_on_impact = false;
	}

	//设置角色效果
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

void idea_monster_slime::decide_action()
{
	
}
