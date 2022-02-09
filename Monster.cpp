#include "Monster.h"

#include "WorldSystem.h"

Monster* Monster::createNew()
{ 
	return new Monster();
}

Monster::Monster()
{
	monster_num++;

	patrol_area = new std::list<Grid*>();
	name = L"default_monster";
	physics_object->type_ally = AllyType::monster;
}

Monster::~Monster()
{
	delete patrol_area;

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



void Monster::setPatrolArea(std::list<Grid*>* _grids)
{
	delete patrol_area;
	patrol_area = _grids;
}

std::list<Grid*>* Monster::getPatrolArea() const
{
	return patrol_area;
}

bool Monster::getIfInPatrolArea() const
{
	for (int i = physics_object->getLeftGrid(); i <= physics_object->getRightGrid(); ++i)
	{
		for (int j =physics_object->getTopGrid(); j <= physics_object->getBottomGrid(); ++j)
		{
			auto t = std::find(patrol_area->begin(), patrol_area->end(), WorldSystem::getInstance()->getGrid(i, j));
			if (t == patrol_area->end())return false;
		}
	}
	return true;
}

int Monster::monster_num = 0;
int Monster::getMonsterNum()
{
	return monster_num;
}
