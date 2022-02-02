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

void Warrior::onBasicSkill()
{
	Chara::onBasicSkill();
}

void Warrior::onBurning()
{
	Chara::onBurning();
}

void Warrior::onDead()
{
	Chara::onDead();
}

void Warrior::onHit()
{
	Chara::onHit();
}

void Warrior::onIdle()
{
	Chara::onIdle();
}

void Warrior::onImpact()
{
	Chara::onImpact();
}

void Warrior::onKill()
{
	Chara::onKill();
}

void Warrior::onMoving()
{
	Chara::onMoving();
}

void Warrior::onPoisoned()
{
	Chara::onPoisoned();
}

void Warrior::onSpecialSkill()
{
	Chara::onSpecialSkill();
}

int Warrior::warrior_num = 0;
int Warrior::getWarriorNum()
{
	return warrior_num;
}
