#pragma once
#include "Grid.h"
#include "PhysicsObject.h"

//物理体 角色
class PhysicsChara :
    public PhysicsObject
{
public:
    static PhysicsChara* createNew();   //限制在内存中创造对象

    
    void update() override; //更新帧
    void renewSignedGrids() override;//对地图签入自己的位置
    
    bool getIfMoving() const;//获取是否正在运动
    bool getIfFalling() const;//获取是否正在掉落
    bool getIfHitBack() const;//获取是否正被击退
    double getSpeed() const;//获取速度
    int getImpact() const;//获取这一帧内角色受到的冲击力
	PhysicsDirection getDirection()const;//获取角色的方向

    void setMotion(PhysicsDirection direction, double speed, double inertia ,bool hit_back );  //设置运动状态
    void setPosition(int x, int y) override;//设置(传送)位置
	bool setDirection(PhysicsDirection direction);//设置角色的方向,如果成功返回true否则返回false

    bool detectLocal(BlockingType blocking)override;//检测当前占用位置是否具有某种类型的阻挡
    bool detectMoving(PhysicsDirection direction);//检查是否能向某个方向运动
    bool detectSubmersed() const;//检查是否被完全淹没
    bool detectFalling();//检查是否会向下掉落

    bool can_swim;//能否游泳
    bool can_fly;//能否飞行
    bool steady; //是否不可击退

    static int getPhysicsCharaNum();

protected:
    PhysicsChara();
    ~PhysicsChara() override;

    std::list<Grid*>* list_grid_signed; //已经签入的网格

    bool moving; //是否正在运动
    bool hitback;//是否处于被击退的状态

    double moving_speed;    //移动速度
    double moving_inertia; //惯性，继续运动的距离
    PhysicsDirection moving_direction;//移动方向

    int impact;//受到的冲击
    int falling_count;//记录下坠了多少距离

    static int physicsCharaNum;//当前活跃的角色物理体

private:
    void stepForward();//按步前进

};

