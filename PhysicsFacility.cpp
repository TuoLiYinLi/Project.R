#include "PhysicsFacility.h"
#include "SDL.h"
#include "WorldSystem.h"

PhysicsFacility* PhysicsFacility::createNew()
{
	PhysicsFacility* physics_facility = new PhysicsFacility();
	if (physics_facility==nullptr)
	{
		SDL_Log(u8"���� ����physics_facility�ڴ治��");
	}
	return physics_facility;
}

PhysicsFacility::PhysicsFacility()
{
	type_physics = PhysicsType::facility;
	type_facility = FacilityType::air;

	//���Լ���ӵ���ʩ�����б�
	WorldSystem::getInstance()->list_physics_facility->push_front(this);

	list_grid_signed = new std::list<Grid*>();
}

PhysicsFacility::~PhysicsFacility()
{
	//���Լ�����ʩ�����б��Ƴ�
	WorldSystem::getInstance()->list_physics_facility->remove(this);

	delete list_grid_signed;
}


void PhysicsFacility::update()
{
	//���ø������
	PhysicsObject::update();
}

void PhysicsFacility::signPosition()
{
	
}
