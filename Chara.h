#pragma once
#include <string>
#include <iostream>
#include <list>

#include "Form.h"

#include "ActionType.h"
#include "AllyType.h"
#include "DirectionType.h"

#include "MapSystem.h"
#include "AnimSystem.h"

#include "CharaSystem.h"
#include "Tag.h"
#include "Counting.h"

class CharaSystem;

class Chara
{
public:
	Tag tag;//��ǩ

	std::string name;//��ɫ����
	AnimationUnit* animUnit;//��ɫ������Ԫ
	Form form;//��ɫ��ֵ��

	AllyType ally;//��Ӫ

	int deathSpeed;//��������ʱ��
	int idleSpeed;//ͣ�Ͷ���ʱ��
	int breath;//ʣ�¶�������

	//��ɫ���ƶ�������ˮ������
	bool ifFly;//�Ƿ��ܹ�����
	bool ifSwim;//�Ƿ���ˮ�п�����Ӿ
	bool ifBreathInWater;//�Ƿ���ˮ�п��Ժ���

	ActionType actionType;//���ڽ��е��ж�����
	int animProgress;//�������ŵĽ���

	double x;//��������X
	double y;//��������Y

	double movingX;//�ں����˶�ʱ����ʣ��ֵ
	double movingY;//����ֱ�����˶�ʱ����ʣ��ֵ

	unsigned short bodyWidth;//��ɫ���
	unsigned short bodyHeight;//��ɫ�߶�

	int deltaX;//������Դ��Ⱦƫ��X
	int deltaY;//������Դ��Ⱦƫ��Y

	bool flip;//�Ƿ�����Ϊ�󣬷�Ϊ��

	double burnDamage;//�ܵ�ȼ�յ��ۻ��˺�
	double poisionedDamage;//�ܵ��ж����ۻ��˺�
	double stifleDamage;//�ۻ��ĺ����˺�
	double recoverAccumulate;//����ֵ�ָ��ۻ�
	double staminaAccumulate;//�ۻ����ӵ�st

	double fallingY;//����׹�佫Ҫ�½��ľ���
	int fallingDist;//�ӿ����ܹ���׹�����

	std::list<Grid*>* occupiedGrids;//ռ�õĸ�λ

	Counting* counting;

	//�Զ���Ѳ�߷�Χ
	std::vector<Grid*>* patrolArea;

	//�����µĽ�ɫ
	static Chara* createNew();
	 //�ֶ��ͷ��ڴ�
	virtual void destroy();

	//��ȡͷ����߶�
	double getHeadSpot();
	//��ȡվ����߶�
	double getStandSpot();
	//��ȡ���λ��
	double getLeftSpot();
	//��ȡ�Ҳ�λ��
	double getRightSpot();
	
	//����ʱ(��������)����
	virtual void onDeath();
	//���ϴ���(�κ����ÿ֡)����
	virtual void onAnytime();
	//ʹ�û�������ʱ����
	virtual void onBasicSkill();
	//��ʹ����������ʱ����
	virtual void onSpecialSkill();
	//�ƶ�״̬(����/׹��/�ƶ�)ʱ(ÿ֡)����
	virtual void onMove();
	//����״̬ʱ(ÿ֡)����
	virtual void onIdle();
	//����ײ��(����ײǽ/ǿ���)ʱ����
	virtual void onImpact();
	//ȼ��ʱ(ÿ֡)����
	virtual void onBurning();
	//��Ͷ�������ʱ����
	virtual void onHit(Form* form);
	//��ֳ���ʱ����
	virtual void onBreed();

	//��ȡ��ǰ������Ӧ�Ķ�������
	virtual AnimType getAnimType();

	//ʹ���ƶ�����
	void move(DirectionType d);

	//ˢ������ռ��λ��
	void renewPosition();
	//��ȡ��ǰ�ж��ٸ�Chara
	static int getCurrentCharaNum();
	
protected:
	static int currentCharaNum;//��¼�ж��ٸ�Charaռ���ڴ�
	 Chara();
	~Chara();
};

