#pragma once
#include "Grid.h"
#include "PhysicsObject.h"

//��ɫ�ĳ���
enum class CharaDirection
{
	right,//��
    up,//��
    left,//��
    down//��
};

//������ ��ɫ
class PhysicsChara :
    public PhysicsObject
{
public:
    static PhysicsChara* createNew();   //�������ڴ��д������

    
    void update() override; //����֡
    void renewSignedGrids() override;//�Ե�ͼǩ���Լ���λ��
    
    bool getIfMoving() const;//��ȡ�Ƿ������˶�
    bool getIfFalling() const;//��ȡ�Ƿ����ڵ���
    bool getIfHitBack() const;//��ȡ�Ƿ���������
    double getSpeed() const;//��ȡ�ٶ�
    int getImpact() const;//��ȡ��һ֡�ڽ�ɫ�ܵ��ĳ����
	CharaDirection getDirection()const;//��ȡ��ɫ�ķ���

    void setMotion(CharaDirection direction, double speed, double inertia ,bool hit_back );  //�����˶�״̬
    void setPosition(int x, int y) override;//����(����)λ��
	bool setDirection(CharaDirection direction);//���ý�ɫ�ķ���,����ɹ�����true���򷵻�false

    bool detectForward(CharaDirection direction, BlockingType blocking) const;//���ĳ���������Ƿ���ĳ�����͵��赲
    bool detectLocal(BlockingType blocking)const;//��⵱ǰռ��λ���Ƿ����ĳ�����͵��赲
    bool detectMoving(CharaDirection direction) const;//����Ƿ�����ĳ�������˶�
    bool detectSubmersed() const;//����Ƿ���ȫ��û
    bool detectFalling() const;//����Ƿ�����µ���
    bool detectBorder(CharaDirection direction) const;//���ĳ�������Ƿ񵽴��ͼ�߼�

    bool can_swim;//�ܷ���Ӿ
    bool can_fly;//�ܷ����
    bool steady; //�Ƿ񲻿ɻ���

    static int getPhysicsCharaNum();

protected:
    PhysicsChara();
    ~PhysicsChara() override;

    std::list<Grid*>* list_grid_signed; //�Ѿ�ǩ�������

    bool moving; //�Ƿ������˶�
    bool hitback;//�Ƿ��ڱ����˵�״̬

    double moving_speed;    //�ƶ��ٶ�
    double moving_inertia; //���ԣ������˶��ľ���
    CharaDirection moving_direction;//�ƶ�����

    int impact;//�ܵ��ĳ��
    int falling_count;//��¼��׹�˶��پ���

    static int physicsCharaNum;//��ǰ��Ծ�Ľ�ɫ������

private:
    void stepForward();//����ǰ��

};

