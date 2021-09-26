#pragma once
#include "AnimationUnit.h"
#include "ParticleSystem.h"
class ParticleSystem;

class AnimParticle
{
public:
	AnimationUnit* animUnit;//目标字体

	int animCycle;//动画循环时间
	int animProgress;//动画

	int livingTime;//粒子持续的时间

	double x;//世界的坐标X
	double y;//世界的坐标Y
	double w;//宽
	double h;//高
	double angle;//粒子的旋转角度(角度制)
	double scale;//粒子大小缩放

	double v_x;//x速度
	double v_y;//y速度
	double v_angle;//角速度
	double v_scale;//粒子缩放速度

	double a_x;//x加速度
	double a_y;//y加速度
	double a_angle;//角加速度
	double a_scale;//缩放加速度

	//创建新的粒子
	static AnimParticle* createNew();
	//销毁这个粒子
	void destroy();

protected:
	AnimParticle();
	~AnimParticle();
};

