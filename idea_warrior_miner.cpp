#include "idea_warrior_miner.h"

idea_warrior_miner* idea_warrior_miner::createNew()
{
	return new idea_warrior_miner();
}

idea_warrior_miner::idea_warrior_miner()
{
	name = L"��";
	introduction = L"������ٿ�������ɿ󣬴����Ϊ�ˡ��ƽ𡱶����������ý�ɳ��ֵ��������������ʲô���ò�����";
	science_name = L"��";

	//�趨������
	{
		getPhysicsChara()->bodyX = 1;
		getPhysicsChara()->bodyY = 2;

		getPhysicsChara()->can_fly = false;
		getPhysicsChara()->can_swim = false;
		getPhysicsChara()->steady = false;
	}

	//���ý�ɫ����
	{
		rendering_unit->width = 2 * PIXEL_RATE;
		rendering_unit->height = 2 * PIXEL_RATE;

		animation_length_idle = 40;
		animation_length_moving = 30;
		animation_length_skill_basic = 40;
		animation_length_skill_special = 40;
		animation_length_disturbed = 40;
		animation_length_dead = 60;

		delay_skill_basic = 0;
		delay_skill_special = 0;

		animation_type_idle = AnimationType::warrior_miner_pickaxe_idle;
		animation_type_moving = AnimationType::warrior_miner_pickaxe_moving;
		animation_type_skill_basic = AnimationType::warrior_miner_pickaxe_dig;
		animation_type_skill_special = AnimationType::warrior_miner_pickaxe_dig;
		animation_type_disturbed = AnimationType::warrior_miner_pickaxe_idle;
		animation_type_dead = AnimationType::warrior_miner_pickaxe_dead;

		rendering_unit->deltaY = 6;
		rendering_unit->deltaX = -18;
	}

	//���ý�ɫ����
	{
		moving_speed = low_speed;

		health_max = 6;
		health = 6;
		health_recovery_speed = 0;
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
