#pragma once
#include "GameObject.h"

enum class FacilityState
{
	idle,
	activated,
	death
};

class Facility :
	public GameObject
{
public:
	static Facility* createNew();

	void update() override;

	FacilityState state;	//��ʩ��״̬
	int animation_progress;	//��ǰ��������

	int animation_length_idle;	//ͣ�Ͷ�����ʱ��,0����û�ж���
	int animation_length_activated;	//�������ʱ��,0����û�ж���
	int animation_length_death;	//����������ʱ��,0����û�ж���

	int health;	//һ����ʩ������ֵ

protected:
	Facility();
	~Facility() override;
};

