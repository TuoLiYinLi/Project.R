#include "Warrior.h"
Warrior* Warrior::createNew()
{
	const auto m = new Warrior();
	if (m == nullptr) {
#ifdef _DEBUG
		SDL_Log(u8"警告 new Monster()申请内存失败，值为nullptr");
#endif // _DEBUG

	}
	return m;
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
