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
    void signPosition() override;   //�Ե�ͼǩ���Լ���λ��
    
protected:
    PhysicsFacility();
    ~PhysicsFacility() override;


    FacilityType type_facility; //��ʩ������
    std::list<Grid*>* list_grid_signed;
};

