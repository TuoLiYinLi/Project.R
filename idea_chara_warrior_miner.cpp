#include "idea_chara_warrior_miner.h"
#include "Defined.h"
#include "GameToolkit.h"

idea_chara_warrior_miner* idea_chara_warrior_miner::createNew()
{
    return new idea_chara_warrior_miner();
}

void idea_chara_warrior_miner::destroy()
{
    delete this;
}

void idea_chara_warrior_miner::onDeath()
{
}

void idea_chara_warrior_miner::onAnytime()
{
}

void idea_chara_warrior_miner::onBasicSkill()
{
}

void idea_chara_warrior_miner::onSpecialSkill()
{
}

void idea_chara_warrior_miner::onMove()
{
}

void idea_chara_warrior_miner::onIdle()
{

	//寻找路径
	{
		//获取周围走到王的距离
		auto mapSys = MapSystem::getInstance();
		auto d_up = mapSys->getDWTK(x, getStandSpot() - 1);
		auto d_down = mapSys->getDWTK(x, getStandSpot() + 1);
		auto d_current = mapSys->getDWTK(x, getStandSpot());
		auto d_left = mapSys->getDWTK(x - 1, getStandSpot());
		auto d_right = mapSys->getDWTK(x + 1, getStandSpot());

		//if(!gameToolkit::ifLiquid(x,getHeadSpot()))
		{
			//在地面进行移动
			if (d_left > 0 && d_left < d_current) {
				move(DirectionType::left);
				return;
			}
			else if (d_right > 0 && d_right < d_current) {
				move(DirectionType::right);
				return;
			}
			else if (d_up > 0 && d_up < d_current) {
				move(DirectionType::up);
				return;
			}
			else if (d_down > 0 && d_down < d_current) {
				move(DirectionType::down);
				return;
			}
		}
	}
}

void idea_chara_warrior_miner::onImpact()
{
}

void idea_chara_warrior_miner::onBurning()
{
}

void idea_chara_warrior_miner::onHit(Form* form)
{
}

void idea_chara_warrior_miner::onBreed()
{
}

AnimType idea_chara_warrior_miner::getAnimType()
{
	switch (actionType)
	{
	case ActionType::idle:
		return AnimType::charaWarriorMiner1_idle;
		break;
	case ActionType::move:
		return AnimType::charaWarriorMiner1_walk;
		break;
	case ActionType::swim:
		return AnimType::charaWarriorMiner1_walk;
		break;
	case ActionType::basicSkill:
		return AnimType::charaWarriorMiner1_dig;
		break;
	case ActionType::specialSkill:
		return AnimType::charaWarriorMiner1_dig;
		break;
	case ActionType::breed:
		return AnimType::charaWarriorMiner1_idle;
		break;
	case ActionType::death:
		return AnimType::charaWarriorMiner1_death;
		break;
	case ActionType::falling:
		return AnimType::charaWarriorMiner1_idle;
		break;
	default:
		throw actionType;
		break;
	}

#ifdef _DEBUG
	std::cout << "\t\tERROR:未识别的CharaAction\n";
#endif // _DEBUG
	return AnimType::size;
}

idea_chara_warrior_miner::idea_chara_warrior_miner()
{
	tag = Tag::miner;

	name = "miner";

	form.setBasicPart(10, 10, 0, 8, 8, 0.02);
	form.setActionPart(40, 2, 40, 4, 60, 7, 60);
	form.setEffectPart(0.2, 0.2, 0, 0.002, 0.030);

	deathSpeed = 135;
	idleSpeed = 120;
	
	ifFly = false;
	ifSwim = true;
	ifBreathInWater = false;

	animProgress = 0;

	x = 10;
	y = 10;
	movingX = 0;
	movingY = 0;
	bodyWidth = 1;
	bodyHeight = 2;
	deltaX = 0;
	deltaY = 0;
	flip = false;

	burnDamage = 0;
	poisionedDamage = 0;
	breath = 600;
	stifleDamage = 0;

	animUnit = AnimationUnit::createNew();
	animUnit->type = AnimType::charaWarriorMiner1_idle;
	animUnit->angle = 0;
	animUnit->depth = 100;
	animUnit->deltaX = -9;
	animUnit->deltaY = 4;
	animUnit->height = 2 * 32;
	animUnit->width = 2 * 32;
	animUnit->x = x;
	animUnit->y = y;

	dtk = WORLD_HEIGHT * WORLD_HEIGHT;
}

idea_chara_warrior_miner::~idea_chara_warrior_miner()
{
}
