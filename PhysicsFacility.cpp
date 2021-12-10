#include "PhysicsFacility.h"
#include "SDL.h"
#include "WorldSystem.h"

PhysicsFacility* PhysicsFacility::createNew()
{
	PhysicsFacility* physics_facility = new PhysicsFacility();
	if (physics_facility==nullptr)
	{
		SDL_Log(u8"警告 分配physics_facility内存不足");
	}
	return physics_facility;
}

PhysicsFacility::PhysicsFacility()
{
	type_physics = PhysicsType::facility;
	type_facility = FacilityType::air;

	//将自己添加到设施物理列表
	WorldSystem::getInstance()->list_physics_facility->push_front(this);

	list_grid_signed = new std::list<Grid*>();
}

PhysicsFacility::~PhysicsFacility()
{
	//将自己从设施物理列表移除
	WorldSystem::getInstance()->list_physics_facility->remove(this);

	delete list_grid_signed;
}


void PhysicsFacility::update()
{
	//调用父类更新
	PhysicsObject::update();
}

void PhysicsFacility::signPosition()
{
	
}
