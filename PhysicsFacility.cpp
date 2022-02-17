#include "PhysicsFacility.h"
#include "SDL.h"
#include "WorldSystem.h"

PhysicsFacility* PhysicsFacility::createNew()
{
	return new PhysicsFacility();
}

PhysicsFacility::PhysicsFacility()
{
	physicsFacilityNumm++;

	type_physics = PhysicsType::facility;
	type_blocking = BlockingType::air;

	//将自己添加到设施物理列表
	WorldSystem::getInstance()->list_physics_facility->push_front(this);

	list_grid_signed = new std::list<Grid*>();
}

PhysicsFacility::~PhysicsFacility()
{
	//重置签入格
	for (auto it = list_grid_signed->begin(); it != list_grid_signed->end(); ++it)
	{
		Grid* grid = *it;
		grid->list_physics_facility->remove(this);
		grid->renewBlockingType(type_blocking);
	}
	list_grid_signed->clear();

	//将自己从设施物理列表移除
	WorldSystem::getInstance()->list_physics_facility->remove(this);

	delete list_grid_signed;
	physicsFacilityNumm--;
}


void PhysicsFacility::update()
{
	
}

void PhysicsFacility::renewSignedGrids()
{
	//重置
	for (auto it = list_grid_signed->begin(); it != list_grid_signed->end(); ++it)
	{
		Grid* grid = *it;
		grid->list_physics_facility->remove(this);
		grid->renewBlockingType(type_blocking);
	}
	list_grid_signed->clear();

	//重新签入

	const int x_start = getLeftGrid();
	const int x_end = getRightGrid();
	const int y_start = getTopGrid();
	const int y_end = getBottomGrid();

	for (int i = x_start; i <= x_end; i++)
	{
		for (int j = y_start; j <= y_end; j++)
		{
			Grid* grid = WorldSystem::getInstance()->getGrid(i, j);
			grid->list_physics_facility->push_back(this);
			grid->renewBlockingType(type_blocking);
			list_grid_signed->push_back(grid);
		}
	}
}


BlockingType PhysicsFacility::getFacilityType() const
{
	return type_blocking;
}


void PhysicsFacility::setFacilityType(BlockingType blocking)
{
	this->type_blocking = blocking;
}

int PhysicsFacility::physicsFacilityNumm = 0;

int PhysicsFacility::getPhysicsFacilityNum()
{
	return physicsFacilityNumm;
}
