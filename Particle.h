#pragma once
#include "GameObject.h"

//游戏物体 单个粒子
class Particle :
    public GameObject
{
public:
    static Particle* createNew();
	void update() override;

    //动画

    int animation_length;
    int animation_progress;
    AnimationType animation;
    int life_time;

    //运动和大小

    double x_v;
    double y_v;
    double width;
    double height;
    double x_center;
    double y_center;
    double scale;
    

protected:
    Particle();
    ~Particle()override;

    void sync_animation() const;
    void update_position() const;
};

