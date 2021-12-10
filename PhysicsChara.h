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
    static PhysicsChara* createNew();   //限制在内存中创造对象

    
    void update() override; //更新帧
    bool if_moving; //是否正在运动

    void move(Direction direction);  //移动位置
    void signPosition() override;

protected:


    PhysicsChara();
    ~PhysicsChara() override;

};

