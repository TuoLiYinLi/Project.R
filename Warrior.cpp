#include "Warrior.h"
Warrior* Warrior::createNew()
{
	return new Warrior();
}

Warrior::Warrior()
{
	warrior_num++;
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
