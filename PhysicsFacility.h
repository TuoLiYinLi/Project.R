#pragma once
#include <list>

#include "PhysicsObject.h"

#include "Grid.h"

//物理体 设施
class PhysicsFacility :
    public PhysicsObject
{
public:
    static PhysicsFacility* createNew();  //创建堆上对象

	void update() override; //更新对象
    void renewSignedGrids() override;   //对地图签入自己的位置
    BlockingType getFacilityType()const;
    void setFacilityType(BlockingType blocking);
    
    static int getPhysicsFacilityNum();
protected:
    PhysicsFacility();
    ~PhysicsFacility() override;


    BlockingType type_blocking; //设施的种类
    std::list<Grid*>* list_grid_signed;

    static int physicsFacilityNumm;
};

