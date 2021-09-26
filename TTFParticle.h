#pragma once
#include "AnimSystem.h"
#include "ParticleSystem.h"
class ParticleSystem;

class TTFParticle
{
public:
	TTFUnit* fontUnit;//目标字体

	int livingTime;//粒子持续的时间

	double x;//世界的坐标X
	double y;//世界的坐标Y
	double scale;//粒子大小缩放

	double v_x;//x速度
	double v_y;//y速度
	double v_scale;//粒子缩放速度

	double a_x;//x加速度
	double a_y;//y加速度
	double a_scale;//缩放加速度

	//创建新的粒子
	static TTFParticle* createNew();
	//销毁这个粒子
	void destroy();

protected:
	TTFParticle();
	~TTFParticle();
};

