#include "idea_warrior_miner.h"

#include "idea_projectile_chop.h"

idea_warrior_miner* idea_warrior_miner::createNew()
{
	return new idea_warrior_miner();
}

void idea_warrior_miner::onBasicSkill()
{
	Warrior::onBasicSkill();
	const auto p = idea_projectile_chop::createNew();
	if (getPhysics()->getDirection() == PhysicsDirection::right)
	{
		p->setup(AllyType::warrior, static_cast<int>(round(physics_object->X)), getPhysics()->getDownGrid(),getPhysics()->getDirection(), false);
	}
	else if (getPhysics()->getDirection() == PhysicsDirection::left)
	{
		p->setup(AllyType::warrior, static_cast<int>(round(physics_object->X)), getPhysics()->getDownGrid(),getPhysics()->getDirection(), true);
	}
	p->owner = this;
}

void idea_warrior_miner::onSpecialSkill()
{
	Warrior::onSpecialSkill();
}

idea_warrior_miner::idea_warrior_miner()
{
	type_warrior = WarriorType::miner;

	name = L"矿工";
	introduction = L"最近不少矿工来这里采矿，大概是为了“黄金”而来。不懂得金沙价值的羸弱人类最终什么都得不到。";
	science_name = L"矿工";

	//设定物理体
	{
		getPhysics()->bodyX = 1;
		getPhysics()->bodyY = 2;

		getPhysics()->can_fly = false;
		getPhysics()->can_swim = false;
		getPhysics()->steady = false;

	}

	//设置角色动画
	{
		rendering_unit->width = 2 * PIXEL_RATE;
		rendering_unit->height = 2 * PIXEL_RATE;

		animation_length_idle = 40;
		animation_length_moving = 30;
		animation_length_skill_basic = 60;
		animation_length_skill_special = 40;
		animation_length_disturbed = 40;
		animation_length_dead = 60;

		delay_skill_basic = 45;
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

	//设置角色属性
	{
		moving_speed = low_speed;

		health_max = 8;
		health = 8;
		health_recovery_speed = 0;
		health_recovery_accumulation = 0;

		burning_damage_accumulation = 0;
		poisoned_damage_accumulation = 0;
		oxygen_damage_accumulation = 0;

		stamina_max = 4;
		stamina = 4;
		stamina_recovery_speed = 0.3 / 60;
		stamina_recovery_accumulation = 0;

		skill_basic_cost = 2;
		skill_special_cost = 0;
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

void idea_warrior_miner::decide_action()
{
	//索敌
	{
		const auto charas = GameToolkit::findCharaInArea(AllyType::monster, static_cast<int>(round(physics_object->X - 5)), getPhysics()->getDownGrid(), 11, 1);
		Chara* target = nullptr;
		double d = 6;
		for (const auto chara : charas)
		{
			const double current_d = abs(chara->physics_object->X - physics_object->X);
			if (current_d < d)
			{
				d = current_d;
				target = chara;
			}
		}
		if (target)
		{
			if (target->physics_object->X > physics_object->X)
			{
				actSkillBasic(PhysicsDirection::right);
			}
			else
			{
				actSkillBasic(PhysicsDirection::left);
			}
			return;
		}
	}
}
