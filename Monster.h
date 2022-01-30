#pragma once
#include "Chara.h"
class Monster :
    public Chara
{
public:
	static Monster* createNew();//�����µĹ���

	void update() override;

	void setPatrolArea(std::list<Grid*>* _grids);//�趨Ѳ����

	std::list <Grid*>* getPatrolArea()const;//��ȡѲ����

	bool getIfInPatrolArea()const;//����Ƿ���Ѳ������

	static int getMonsterNum();

protected:
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

protected:
	static int monster_num;

	std::list<Grid*>* patrol_area;//������Ի������

	Monster();
	~Monster()override;
};
