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
    static PhysicsChara* createNew();   //限制在内存中创造对象

    
    void update() override; //更新帧
    bool getSteady() const; //获取是否是不可击退的
    bool getMoving() const;//获取是否正在运动
    void setMotion(CharaDirection direction, double speed, double inertia ,bool hit_back );  //设置运动状态
    void renewSignedGrids() override;

    int getImpact() const;

    bool detectForward(CharaDirection direction, BlockingType blocking) const;//检测某个方向上是否有某种类型的阻挡
    bool detectLocal(BlockingType blocking)const;//检测当前占用位置是否具有某种类型的阻挡
    bool detectMoving(CharaDirection direction) const;
    bool detectSubmersed() const;//检查是否被完全淹没
    bool detectFalling() const;
    bool detectBorder(CharaDirection direction) const;

    bool can_swim;//能否游泳
    bool can_fly;//能否飞行


protected:
    PhysicsChara();
    ~PhysicsChara() override;
    std::list<Grid*>* list_grid_signed; //已经签入的网格


    bool moving; //是否正在运动
    bool steady; //是否不可击退

    double moving_speed;    //移动速度
    double moving_inertia; //惯性，继续运动的距离
    CharaDirection moving_direction;//移动方向

    int impact;//受到的冲击
    int falling_count;//记录下坠了多少距离

private:
    void stepForward();//按步前进

};

