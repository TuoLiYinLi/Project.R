#pragma once
#include "Chara.h"

//��Ϸ��� ����
//���ǵĵ���
class Warrior :
    public Chara
{
public:
	static Warrior* createNew();//�����µĹ���

	void update() override;

	static int getWarriorNum();

protected:

	static int warrior_num;

	Warrior();
	~Warrior()override;
};

