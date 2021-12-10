#pragma once
#include "GameObject.h"

enum class CharaAction
{
	idle,
	moving,
	falling,
	skill_basic,
	skill_special,
	death
};

class Chara :
	public GameObject
{
public:
	static Chara* createNew();

	CharaAction action;//���ڽ��е��ж�����
	int animation_progress;	//��ǰ��������

	int animation_length_idle;	//ͣ�Ͷ�����ʱ��,0����û�ж���
	int animation_length_moving;	//�������ʱ��,0����û�ж���
	int animation_length_falling;	//
	int animation_length_death;	//����������ʱ��,0����û�ж���


	

protected:
	Chara();
	~Chara() override;
};

