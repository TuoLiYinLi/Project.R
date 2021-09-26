#pragma once
#include <iostream>
#include <list>

#include "Form.h"
#include "ProjectileType.h"
#include "AllyType.h"

#include "Chara.h"
#include "Facility.h"
#include "MapSystem.h"



#include "ProjectileSystem.h"
class ProjectileSystem;

class Projectile
{
public:
	AllyType allyType;//���Ͷ����������һ��(�ҷ�Ͷ����ֻ���е���,�з�Ͷ����ֻ��������,����Ͷ�������˫��)
	AnimationUnit* animUnit;//���Ͷ����Ķ���

	Form form;//������������Ч��ʱ�Խ�ɫ�ύ�����ݱ�
	
	double x;//��������X
	double y;//��������Y
	
	double vx;//������ٶ�X
	double vy;//������ٶ�y

	double ax;//����ļ��ٶ�x
	double ay;//����ļ��ٶ�y

	double bodyWidth;//������
	double bodyHeight;//����߶�
	
	unsigned int animCycle;//ѭ��һ�ζ�����ʱ��
	unsigned int animProgress;//��������
	unsigned int livingTime;//�ܹ������ʱ��

	//����Ȼʱ�����
	virtual void onEnd();
	//�����г���ʱ
	virtual void onFlying();

	//����new Ͷ����
	static Projectile* createNew();
	virtual void destroy();

	//��ȡ��ǰռ���ڴ��Ͷ��������
	static int getCurrentProjNum();
protected:
	Projectile();
	~Projectile();
	static int currentProjNum;
};

