#pragma once
#include "PhysicsObject.h"

enum class Direction
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
    bool if_moving; //�Ƿ������˶�

    void move(Direction direction);  //�ƶ�λ��
    void signPosition() override;

protected:


    PhysicsChara();
    ~PhysicsChara() override;

};

