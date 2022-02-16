#pragma once
#include "Chara.h"
class Monster :
    public Chara
{
public:
	static Monster* createNew();//�����µĹ���

	void update() override;

	static int getMonsterNum();

protected:
	//�����ӿ�
	void onIdle()override;//������״̬ʱ ÿ֡����
	void onMoving()override;//���ƶ�״̬ʱ ÿ֡����
	void onBasicSkill()override;//������������ʹ��ʱ ���̴���
	void onSpecialSkill()override;//������������ʹ��ʱ ���̴���
	void onKill()override;//������ֵ����ʱ ���̴���
	void onDead()override;//����������ʧʱ ���̴���
	void onImpact(int _impact)override;//���ܵ��ⲿ���ʱ ���̴���
	void onHit()override;//���ܵ�Ͷ����ֱ���˺�ʱ ���̴���
	void onBurning()override;//���Լ�ȼ��ʱ ÿ֡����
	void onPoisoned()override;//���Լ��ж�ʱ ÿ֡����

protected:
	static int monster_num;

	Monster();
	~Monster()override;
};

