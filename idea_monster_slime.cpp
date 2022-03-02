#include "idea_monster_slime.h"

#include "Defined.h"
#include "idea_projectile_little_slime_ball.h"

idea_monster_slime* idea_monster_slime::createNew()
{
	return new idea_monster_slime();
}

void idea_monster_slime::update()
{
	Monster::update();
	if (!gene_container.getGeneTag(GeneTag::sludge_essence)
		&& action_type != CharaActionType::dead)
	{
		setAnimationDead();
	}
}

void idea_monster_slime::onBasicSkill()
{
	Monster::onBasicSkill();
	const auto p = idea_projectile_little_slime_ball::createNew();
	if(getPhysics()->getDirection()==PhysicsDirection::right)
	{
		p->setup(AllyType::monster, static_cast<int>(round(physics_object->X)), static_cast<int>(round(physics_object->Y)), true);
	}
	else if (getPhysics()->getDirection() == PhysicsDirection::left)
	{
		p->setup(AllyType::monster, static_cast<int>(round(physics_object->X)), static_cast<int>(round(physics_object->Y)), false);
	}
	p->owner = this;
}

void idea_monster_slime::onSpecialSkill()
{
	Monster::onSpecialSkill();

	const auto f = GameToolkit::findFacilityIn(FacilityType::mucus, static_cast<int>(round(physics_object->X)), static_cast<int>(round(physics_object->Y)));
	if(!f.empty()&&f.front()->counting_container.getNumOf(CountingType::slime)>=4)
	{
		f.front()->counting_container.addNumOf(CountingType::slime, -4);
		//获得随机史莱姆基因
		gene_container.addGene(GeneMaker::random_slime_related());
	}
}

idea_monster_slime::idea_monster_slime()
{
	name = L"史莱姆";
	introduction = L"软泥组成的怪物，脆弱但廉价。\n*不会受到冲击伤害。";
	science_name = L"史莱姆";

	//设定物理体
	{
		getPhysics()->bodyX = 1;
		getPhysics()->bodyY = 1;

		getPhysics()->can_fly = false;
		getPhysics()->can_swim = false;
		getPhysics()->steady = false;
	}

	//设置角色动画
	{
		animation_length_idle = 40;
		animation_length_moving = 30;
		animation_length_skill_basic = 60;
		animation_length_skill_special = 80;
		animation_length_disturbed = 40;
		animation_length_dead = 60;

		delay_skill_basic = 12;
		delay_skill_special = 60;

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

		skill_basic_cost = 1;
		skill_special_cost = 4;

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

	gene_container.addGene(GeneMaker::sludge_essence());
}

void idea_monster_slime::decide_action()
{
	//索敌
	{
		const auto charas= GameToolkit::findCharaInArea(AllyType::warrior, static_cast<int>(round(physics_object->X - 3)), static_cast<int>(round(physics_object->Y)), 7, 1);
		Chara* target=nullptr;
		double d = 4;
		for (const auto chara : charas)
		{
			const double current_d = abs(chara->physics_object->X - physics_object->X);
			if(current_d<d)
			{
				d = current_d;
				target = chara;
			}
		}
		if(target)
		{
			if(target->physics_object->X > physics_object->X)
			{
				actSkillBasic(PhysicsDirection::right);
			}else
			{
				actSkillBasic(PhysicsDirection::left);
			}
			return;
		}
	}
	//没有目标敌人,改为寻找粘液设施
	{
		const auto f = GameToolkit::findFacilityInArea(FacilityType::mucus,
			physics_object->getLeftGrid(), physics_object->getDownGrid(), physics_object->bodyX, physics_object->bodyY);
		Facility* target = nullptr;
		for (const auto facility : f)
		{
			if (stamina >= 4 && facility->counting_container.getNumOf(CountingType::slime) > 4)
			{
				actSkillSpecial(getPhysics()->getDirection());
				return;
			}
		}
	}

	//没有粘液设施,改为巡逻
	{
		for (int i = 0; i < 4; ++i)
		{
			if(can_go(getPhysics()->getDirection()))
			{
				actMove(getPhysics()->getDirection());
			}else
			{
				turn_clockwise(false);
			}
		}
	}

}

void idea_monster_slime::turn_clockwise(bool reverse) const
{
	switch (getPhysics()->getDirection())
	{
	case PhysicsDirection::right: 
		if (!reverse)getPhysics()->setDirection(PhysicsDirection::down);
		else getPhysics()->setDirection(PhysicsDirection::up);
		break;
	case PhysicsDirection::up:
		if (!reverse)getPhysics()->setDirection(PhysicsDirection::right);
		else getPhysics()->setDirection(PhysicsDirection::left);
		break;
	case PhysicsDirection::left:
		if (!reverse)getPhysics()->setDirection(PhysicsDirection::up);
		else getPhysics()->setDirection(PhysicsDirection::down);
		break;
	case PhysicsDirection::down:
		if (!reverse)getPhysics()->setDirection(PhysicsDirection::left);
		else getPhysics()->setDirection(PhysicsDirection::right);
		break;
	}
}

bool idea_monster_slime::can_go(PhysicsDirection direction) const
{
	if(!getPhysics()->detectMoving(direction))
	{
		return false;
	}

	switch (direction)
	{
	case PhysicsDirection::right:
		{
			auto x = getPhysics()->getRightGrid();
			auto y = getPhysics()->getDownGrid();
			return GameToolkit::findBlockingIn(BlockingType::solid, x + 1, y + 1) ||
				GameToolkit::findBlockingInArea(BlockingType::support, x + 1, y, 1, 2);
		}
	case PhysicsDirection::left:
		{
			auto x = getPhysics()->getLeftGrid();
			auto y = getPhysics()->getDownGrid();
			return GameToolkit::findBlockingIn(BlockingType::solid, x - 1, y + 1) ||
				GameToolkit::findBlockingInArea(BlockingType::support, x - 1, y, 1, 2);
		}
	case PhysicsDirection::up: 
	case PhysicsDirection::down:
		return GameToolkit::findFacilityInArea(FacilityType::ladder,
			getPhysics()->getLeftGrid(), getPhysics()->getDownGrid(), getPhysics()->bodyX, 1).empty();
	}
#ifdef _DEBUG
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"idea_monster_slime::can_go意外返回");
#endif
	return false;
}
