#pragma once
#include <list>

#include "PhysicsObject.h"

#include "Grid.h"

class PhysicsFacility :
    public PhysicsObject
{
public:
    static PhysicsFacility* createNew();  //创建堆上对象

	void update() override; //更新对象
    void signPosition() override;   //对地图签入自己的位置
    
protected:
    PhysicsFacility();
    ~PhysicsFacility() override;


    FacilityType type_facility; //设施的种类
    std::list<Grid*>* list_grid_signed;
};

