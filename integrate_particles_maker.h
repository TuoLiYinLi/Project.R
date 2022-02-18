#pragma once
#include "GameToolkit.h"
#include "Defined.h"
template<class P>
class integrate_particles_maker
{
public:
	int num;//每次发射粒子数量
	int gap;//发射频率间隔
	int CD;//发射倒计时

	double v_max, v_min;//速度范围
	double v_angle_standard;//速度角基准
	double v_angle_range;//速度角范围

	double x_ori, y_ori;//起点
	double offset_radius;//偏移半径

	int max_time_decrease;//最大时间差

	integrate_particles_maker()
	{
		num = 1; gap = 1; v_max = 0; v_min = 0;
		v_angle_standard = 0; v_angle_range = 0;
		x_ori = 0; y_ori = 0; offset_radius = 0;
		CD = gap; max_time_decrease = 0;
	}

	void make_particle()
	{
		if(CD<=0)
		{
			CD = gap;
			//开始发射
			for (int i = 0; i < num; ++i)
			{
				P* p = P::createNew();

				auto v = GameToolkit::random(v_min, v_max);
				const auto v_angle = GameToolkit::random(v_angle_standard - v_angle_range, v_angle_standard + v_angle_range);
				p->x_v = v * cos(v_angle);
				p->y_v = v * sin(v_angle);

				const auto p_radius = GameToolkit::random(0.0, offset_radius);
				const auto p_angle = GameToolkit::random(-pi, pi);

				p->rendering_unit->x = x_ori + p_radius * cos(p_angle);
				p->rendering_unit->y = y_ori + p_radius * sin(p_angle);

				auto actual_time_decrease = GameToolkit::random(max_time_decrease);
				p->life_time -= actual_time_decrease;
				p->animation_progress += actual_time_decrease;
			}
		}
		CD--;
	}

	void update(
		int _num, int _gap, int _max_time_decrease,
		double _x_ori, double _y_ori, double _offset_radius,
		double _v_min, double _v_max, double _v_angle_standard, double _v_angle_range)
	{
		num = _num; gap = _gap; v_max = _v_max; v_min = _v_min;
		v_angle_standard = _v_angle_standard; v_angle_range = _v_angle_range;
		x_ori = _x_ori; y_ori = _y_ori; offset_radius = _offset_radius;
		CD = gap; max_time_decrease = _max_time_decrease;
	}

	void update_position(double _x, double _y)
	{
		x_ori = _x; y_ori = _y;
	}
};

