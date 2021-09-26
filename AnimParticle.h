#pragma once
#include "AnimationUnit.h"
#include "ParticleSystem.h"
class ParticleSystem;

class AnimParticle
{
public:
	AnimationUnit* animUnit;//Ŀ������

	int animCycle;//����ѭ��ʱ��
	int animProgress;//����

	int livingTime;//���ӳ�����ʱ��

	double x;//���������X
	double y;//���������Y
	double w;//��
	double h;//��
	double angle;//���ӵ���ת�Ƕ�(�Ƕ���)
	double scale;//���Ӵ�С����

	double v_x;//x�ٶ�
	double v_y;//y�ٶ�
	double v_angle;//���ٶ�
	double v_scale;//���������ٶ�

	double a_x;//x���ٶ�
	double a_y;//y���ٶ�
	double a_angle;//�Ǽ��ٶ�
	double a_scale;//���ż��ٶ�

	//�����µ�����
	static AnimParticle* createNew();
	//�����������
	void destroy();

protected:
	AnimParticle();
	~AnimParticle();
};

