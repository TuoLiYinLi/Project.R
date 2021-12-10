#pragma once
#include "GameObject.h"

class Projectile:
	public GameObject
{
public:
	//����new Ͷ����
	static Projectile* createNew();
	
	int animation_length;	//ѭ��һ�ζ�����ʱ��
	int animation_progress;	//��������
	int life_time;	//�ܹ������ʱ��
	

protected:
	Projectile();
	~Projectile() override;


};

