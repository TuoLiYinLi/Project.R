#include "CharaSlime.h"
#include "Defined.h"
#include "GameToolkit.h"

void CharaSlime::destroy() {
	delete this;
}

CharaSlime* CharaSlime::createNew() {
	return new CharaSlime();
}

void CharaSlime::clockwise(bool ifReverse)
{
	int d = int(myDirection);
	if (!ifReverse) {
		//顺时针旋转方向
		d--;
	}
	else
	{
		//逆时针旋转方向
		d++;
	}
	if (d < 0) {
		d += 4;
	}
	else if (d >= 4)
	{
		d -= 4;
	}
	myDirection = DirectionType(d);
}

CharaSlime::CharaSlime() {
#ifdef CHARA_DEBUG
	std::cout << "\tCharaSlime::CharaSlime()\n";
#endif // CHARA_DEBUG

	tag = Tag::Slime;

	name = "Slime";

	form.setBasicPart(4,4,0.01,8,8,0.01,0);
	form.setActionPart(40,2,40,4,60,7,60);
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
	bodyHeight = 1;
	deltaX = 0;
	deltaY = 0;
	flip = false;
	myDirection = DirectionType::right;

	burnDamage = 0;
	poisionedDamage = 0;
	breath = 600;
	stifleDamage = 0;

	animUnit = AnimationUnit::createNew();
	animUnit->type = AnimType::charaSlimeIdle;
	animUnit->angle = 0;
	animUnit->depth = 100;
	animUnit->deltaX = 0;
	animUnit->deltaY = 4;
	animUnit->height = bodyHeight * 32;
	animUnit->width = bodyWidth * 32;
	animUnit->x = x;
	animUnit->y = y;

	heightMark = 0;
}



CharaSlime::~CharaSlime() {
#ifdef CHARA_DEBUG
	std::cout << "\tCharaSlime::~CharaSlime()\n";
#endif // CHARA_DEBUG
}

AnimType CharaSlime::getAnimType() {
	switch (actionType)
	{
	case ActionType::idle:
		return AnimType::charaSlimeIdle;
		break;
	case ActionType::move:
		return AnimType::charaSlimeMove;
		break;
	case ActionType::swim:
		return AnimType::charaSlimeMove;
		break;
	case ActionType::basicSkill:
		return AnimType::charaSlimeBasic;
		break;
	case ActionType::specialSkill:
		return AnimType::charaSlimeSpecial;
		break;
	case ActionType::breed:
		return AnimType::charaSlimeSpecial;
		break;
	case ActionType::death:
		return AnimType::charaSlimeDeath;
		break;
	case ActionType::falling:
		return AnimType::charaSlimeIdle;
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


void CharaSlime::onDeath()
{
	std::cout << "\t\tCharaSlime::onDeath()\n";
	/*
	actionType = ActionType::death;
	animUnit->type = AnimType::charaSlimeDeath;
	animProgress = 0;
	*/
}

void CharaSlime::onAnytime()
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tCharaSlime::onAnytime()\n";
#endif // CHARA_ACTION_DEBUG
}

void CharaSlime::onMove()
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tCharaSlime::onMove()\n";
#endif // CHARA_ACTION_DEBUG
	/*
	actionType = ActionType::move;
	animUnit->type = AnimType::charaSlimeMove;
	animProgress = 0;
	switch (d)
	{
	case DirectionType::right:
		flip = false;
		movingX++;
		break;
	case DirectionType::up:
		movingY--;
		break;
	case DirectionType::left:
		flip = true;
		movingX--;
		break;
	case DirectionType::down:
		movingY++;
		break;
	default:
		break;
	}
	*/
}

void CharaSlime::onBasicSkill()
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tCharaSlime::onBasicSkill()\n";
#endif // CHARA_ACTION_DEBUG
	
}

void CharaSlime::onSpecialSkill()
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tCharaSlime::onSpecialSkill()\n";
#endif // CHARA_ACTION_DEBUG
}

void CharaSlime::onIdle()
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tCharaSlime::onIdle()\n";
#endif // CHARA_ACTION_DEBUG
	
	//决定是否要移动
	/*
	if (form.stamina >= form.staminaMax - 2) {
		//AI徘徊

		clockwise(false);
		int count = 0;
		while (true)
		{
			if (count >= 4) {
				std::cout << "\t\tWARN:史莱姆被完全挡住了\n";
				break;
			}

			switch (myDirection)
			{
			case DirectionType::right:
				if (gameToolkit::ifWalkable(getRightSpot() + 1, getStandSpot())) {
					move(DirectionType::right);
					return;
				}
				break;
			case DirectionType::up:
				if (gameToolkit::ifWalkable(x, getStandSpot() - 1)) {
					if (heightMark>=2)
					{
						clockwise(false);
						clockwise(false);
						break;
					}
					move(DirectionType::up);
					heightMark++;
					return;
				}
				break;
			case DirectionType::left:
				if (gameToolkit::ifWalkable(getRightSpot() - 1, getStandSpot())) {
					move(DirectionType::left);
					return;
				}
				break;
			case DirectionType::down:
				if (gameToolkit::ifWalkable(x, getStandSpot() + 1)) {
					if (heightMark <= -2)
					{
						clockwise(false);
						clockwise(false);
						break;
					}
					move(DirectionType::down);
					heightMark--;
					return;
				}
				break;
			default:
				throw myDirection;
				break;
			}
			clockwise(true);
			count++;
		}
	}
	*/
	
	auto mapSys = MapSystem::getInstance();
	//寻路特性:愚钝,只横向移动
	if (form.stamina >= form.moveST)
	{
		if (!gameToolkit::ifWalkable(getLeftSpot() - 1, getStandSpot()) && !gameToolkit::ifWalkable(getRightSpot() + 1, getStandSpot()))
		{
			if (gameToolkit::ifWalkable(x, getStandSpot() - 1))
			{
				move(DirectionType::up);
			}
			else if(gameToolkit::ifWalkable(x, getStandSpot() - 1))
			{
				move(DirectionType::down);
			}
		}

		if (!flip) 
		{
			//向右运动
			if (gameToolkit::ifWalkable(getRightSpot() + 1, getStandSpot()))
			{
				move(DirectionType::right);
			}
			else
			{
				flip = true;
			}
		}
		else
		{
			//向左运动
			if (gameToolkit::ifWalkable(getLeftSpot() - 1, getStandSpot()))
			{
				move(DirectionType::left);
			}
			else
			{
				flip = false;
			}
		}
	}
	


}

void CharaSlime::onImpact()
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tCharaSlime::onImpact()\n";
#endif // CHARA_ACTION_DEBUG
	gameToolkit::createText(x, y, "Ouch!", { 255,255,0,255 });
}

void CharaSlime::onBurning()
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tCharaSlime::onBurning()\n";
#endif // CHARA_ACTION_DEBUG
}

void CharaSlime::onHit(Form* form)
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tCharaSlime::onHit()\n";
#endif // CHARA_ACTION_DEBUG
	gameToolkit::applyForm(this, form);
}

void CharaSlime::onBreed()
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tCharaSlime::onBreed()\n";
#endif // CHARA_ACTION_DEBUG
}


