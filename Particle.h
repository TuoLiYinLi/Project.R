#pragma once
#include "GameObject.h"

//��Ϸ���� ��������
class Particle :
    public GameObject
{
public:
    static Particle* createNew();
	void update() override;

    //����

    int animation_length;
    int animation_progress;
    AnimationType animation;
    int life_time;

    //�˶��ʹ�С

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

