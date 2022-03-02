#include "Warrior.h"
Warrior* Warrior::createNew()
{
	return new Warrior();
}

Warrior::Warrior()
{
	warrior_num++;

	name = L"default_warrior";

	type_warrior = WarriorType::default_warrior;
	physics_object->type_ally = AllyType::warrior;
}

Warrior::~Warrior()
{
	warrior_num--;
}


void Warrior::update()
{
	Chara::update();
}

int Warrior::warrior_num = 0;
int Warrior::getWarriorNum()
{
	return warrior_num;
}
