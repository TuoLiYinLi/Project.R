#include "Monster.h"

#include "WorldSystem.h"

Monster* Monster::createNew()
{ 
	return new Monster();
}

Monster::Monster()
{
	monster_num++;

	type_monster = MonsterType::default_monster;
	
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

int Monster::monster_num = 0;

int Monster::getMonsterNum()
{
	return monster_num;
}
