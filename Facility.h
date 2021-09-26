#pragma once
#include <iostream>
#include "BlockingType.h"
#include "AnimSystem.h"
#include "StateType.h"
#include "MapSystem.h"
#include "Counting.h"
#include "AllyType.h"
#include "FacilitySystem.h"
class FacilitySystem;

class Facility
{
public:
	BlockingType blockingType;//���ֳ����赲����
	StateType stateType;//����״̬
	AnimationUnit* animUnit;//���еĶ���Ԫ��

	AllyType ally;//��Ӫ

	Counting* counting;//��ʩ���еļ�����

	int idleLength;//ͣ�Ͷ�����ʱ��,0����û�ж���
	int activateLength;//�������ʱ��,0����û�ж���
	int deathLength;//����������ʱ��,0����û�ж���
	int animProgress;//��ǰ��������

	int health;//һ����ʩ������ֵ
	int activateCycle;//��������,ֵΪ0��ʾ���ܼ���
	int activateCD;//�����ʱ
	
	int width;//���
	int height;//�߶�

	double x;//��������X
	double y;//��������Y

	std::list<Grid*>* occupiedGrids;//������ռ�õĸ���
	
	//����new ��ʩ
	static Facility* createNew();
	//����
	virtual void destroy();

	//�κ�ʱ�򴥷�
	virtual void onAnytime();
	//��������
	virtual void onActivate();
	//������
	virtual void onIdle();
	//����Ͷ�������
	virtual void onHit(Form* form);
	//������
	virtual void onDeath();

	//��ȡ��ǰ������Ӧ�Ķ�������
	virtual AnimType getAnimType();


	//ˢ���Լ���λ��
	void renewPosition();
	//��ȡ��ǰռ���ڴ����ʩ����
	static int getCurrentFacilityNum();
protected:
	static int currentNum;//��ǰռ���ڴ��Facility����
	Facility();
	~Facility();
};

