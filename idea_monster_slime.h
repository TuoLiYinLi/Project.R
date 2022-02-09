#pragma once
#include "Monster.h"
class idea_monster_slime :
    public Monster
{
public:
    static idea_monster_slime* createNew();

    void update() override;

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
    idea_monster_slime();
    ~idea_monster_slime()override;
};

