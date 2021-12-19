#pragma once
#include <list>

#include "PhysicsObject.h"

#include "Grid.h"

class PhysicsFacility :
    public PhysicsObject
{
public:
    static PhysicsFacility* createNew();  //�������϶���

	void update() override; //���¶���
    void renewSignedGrids() override;   //�Ե�ͼǩ���Լ���λ��
    BlockingType getFacilityType()const;
    void setFacilityType(BlockingType blocking);
    
protected:
    PhysicsFacility();
    ~PhysicsFacility() override;


    BlockingType type_blocking; //��ʩ������
    std::list<Grid*>* list_grid_signed;
};

