#pragma once
#include "Chara.h"

enum class WarriorType
{
	default_warrior,
	miner,
};

//��Ϸ��� ����
//���ǵĵ���
class Warrior :
    public Chara
{
public:
	static Warrior* createNew();//�����µĹ���

	WarriorType type_warrior;

	void update() override;

	static int getWarriorNum();

protected:

	static int warrior_num;

	Warrior();
	~Warrior()override;
};

