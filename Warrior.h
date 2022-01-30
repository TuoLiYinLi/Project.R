#pragma once
#include "Chara.h"
class Warrior :
    public Chara
{
public:
	static Warrior* createNew();//�����µĹ���

	void update() override;

	static int getWarriorNum();

protected:

	static int warrior_num;

	//�����ӿ�
	void onIdle()override;//������״̬ʱ ÿ֡����
	void onMoving()override;//���ƶ�״̬ʱ ÿ֡����
	void onBasicSkill()override;//������������ʹ��ʱ ���̴���
	void onSpecialSkill()override;//������������ʹ��ʱ ���̴���
	void onKill()override;//������ֵ����ʱ ���̴���
	void onDead()override;//����������ʧʱ ���̴���
	void onImpact()override;//���ܵ��ⲿ���ʱ ���̴���
	void onHit()override;//���ܵ�Ͷ����ֱ���˺�ʱ ���̴���
	void onBurning()override;//���Լ�ȼ��ʱ ÿ֡����
	void onPoisoned()override;//���Լ��ж�ʱ ÿ֡����

	Warrior();
	~Warrior()override;
};
