#include "CharaWarriorMiner.h"

CharaWarriorMiner* CharaWarriorMiner::createNew()
{
    return new CharaWarriorMiner();
}

void CharaWarriorMiner::destroy()
{
    delete this;
}

void CharaWarriorMiner::onDeath()
{
}

void CharaWarriorMiner::onAnytime()
{
}

void CharaWarriorMiner::onBasicSkill()
{
}

void CharaWarriorMiner::onSpecialSkill()
{
}

void CharaWarriorMiner::onMove()
{
}

void CharaWarriorMiner::onIdle()
{
	
}

void CharaWarriorMiner::onImpact()
{
}

void CharaWarriorMiner::onBurning()
{
}

void CharaWarriorMiner::onHit(Form* form)
{
}

void CharaWarriorMiner::onBreed()
{
}

AnimType CharaWarriorMiner::getAnimType()
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
		break;
	}

#ifdef _DEBUG
	std::cout << "\t\tERROR:Î´Ê¶±ðµÄCharaAction\n";
#endif // _DEBUG
	return AnimType::size;
}

CharaWarriorMiner::CharaWarriorMiner()
{
	tag = Tag::Miner;

	name = "Miner";

	form.setBasicPart(10, 10, 0, 8, 8, 0.01, 0);
	form.setActionPart(40, 2, 40, 4, 60, 7, 60);
	form.setEffectPart(0.2, 0.2, 0, 0.002, 0.030);

	deathSpeed = 135;
	idleSpeed = 120;
	breathType = BreathType::both;
	actionType = ActionType::idle;
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
	animUnit->deltaY = -12;
	animUnit->height = 2 * 32;
	animUnit->width = 2 * 32;
	animUnit->x = x;
	animUnit->y = y;
}

CharaWarriorMiner::~CharaWarriorMiner()
{
}
