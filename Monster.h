#pragma once
#include "Chara.h"

//��Ϸ���� ����
//���ǵ�����
class Monster :
    public Chara
{
public:
	static Monster* createNew();//�����µĹ���

	void update() override;

	static int getMonsterNum();

protected:
	static int monster_num;

	Monster();
	~Monster()override;
};

