#pragma once
#include "AnimSystem.h"
#include "ParticleSystem.h"
class ParticleSystem;

class TTFParticle
{
public:
	TTFUnit* fontUnit;//Ŀ������

	int livingTime;//���ӳ�����ʱ��

	double x;//���������X
	double y;//���������Y
	double scale;//���Ӵ�С����

	double v_x;//x�ٶ�
	double v_y;//y�ٶ�
	double v_scale;//���������ٶ�

	double a_x;//x���ٶ�
	double a_y;//y���ٶ�
	double a_scale;//���ż��ٶ�

	//�����µ�����
	static TTFParticle* createNew();
	//�����������
	void destroy();

protected:
	TTFParticle();
	~TTFParticle();
};

