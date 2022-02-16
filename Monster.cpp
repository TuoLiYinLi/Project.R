#include "Monster.h"

#include "WorldSystem.h"

Monster* Monster::createNew()
{ 
	return new Monster();
}

Monster::Monster()
{
	monster_num++;
	
	name = L"default_monster";
	physics_object->type_ally = AllyType::monster;
}

Monster::~Monster()
{

	monster_num--;
}

void Monster::update()
{
	Chara::update();
}

void Monster::onBasicSkill()
{
	Chara::onBasicSkill();
}

void Monster::onBurning()
{
	Chara::onBurning();
}

void Monster::onDead()
{
	Chara::onDead();
}

void Monster::onHit()
{
	Chara::onHit();
}

void Monster::onIdle()
{
	Chara::onIdle();
}

void Monster::onImpact(int _impact)
{
	Chara::onImpact(_impact);
}

void Monster::onKill()
{
	Chara::onKill();
}

void Monster::onMoving()
{
	Chara::onMoving();
}

void Monster::onPoisoned()
{
	Chara::onPoisoned();
}

void Monster::onSpecialSkill()
{
	Chara::onSpecialSkill();
}

int Monster::monster_num = 0;
int Monster::getMonsterNum()
{
	return monster_num;
}
