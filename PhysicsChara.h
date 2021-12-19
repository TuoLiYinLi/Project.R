#pragma once
#include "Grid.h"
#include "PhysicsObject.h"

enum class CharaDirection
{
	right,
    up,
    left,
    down
};

class PhysicsChara :
    public PhysicsObject
{
public:
    static PhysicsChara* createNew();   //�������ڴ��д������

    
    void update() override; //����֡
    bool getSteady() const; //��ȡ�Ƿ��ǲ��ɻ��˵�
    bool getMoving() const;//��ȡ�Ƿ������˶�
    void setMotion(CharaDirection direction, double speed, double inertia ,bool hit_back );  //�����˶�״̬
    void renewSignedGrids() override;

    int getImpact() const;

    bool detectForward(CharaDirection direction, BlockingType blocking) const;//���ĳ���������Ƿ���ĳ�����͵��赲
    bool detectLocal(BlockingType blocking)const;//��⵱ǰռ��λ���Ƿ����ĳ�����͵��赲
    bool detectMoving(CharaDirection direction) const;
    bool detectSubmersed() const;//����Ƿ���ȫ��û
    bool detectFalling() const;
    bool detectBorder(CharaDirection direction) const;

    bool can_swim;//�ܷ���Ӿ
    bool can_fly;//�ܷ����


protected:
    PhysicsChara();
    ~PhysicsChara() override;
    std::list<Grid*>* list_grid_signed; //�Ѿ�ǩ�������


    bool moving; //�Ƿ������˶�
    bool steady; //�Ƿ񲻿ɻ���

    double moving_speed;    //�ƶ��ٶ�
    double moving_inertia; //���ԣ������˶��ľ���
    CharaDirection moving_direction;//�ƶ�����

    int impact;//�ܵ��ĳ��
    int falling_count;//��¼��׹�˶��پ���

private:
    void stepForward();//����ǰ��

};

