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

	//���Լ���ӵ���ʩ�����б�
	WorldSystem::getInstance()->list_physics_facility->push_front(this);

	list_grid_signed = new std::list<Grid*>();
}

PhysicsFacility::~PhysicsFacility()
{
	//����ǩ���
	for (auto it = list_grid_signed->begin(); it != list_grid_signed->end(); ++it)
	{
		Grid* grid = *it;
		grid->list_physics_facility->remove(this);
		grid->renewBlockingType(type_blocking);
	}
	list_grid_signed->clear();

	//���Լ�����ʩ�����б��Ƴ�
	WorldSystem::getInstance()->list_physics_facility->remove(this);

	delete list_grid_signed;
	physicsFacilityNumm--;
}


void PhysicsFacility::update()
{
	
}

void PhysicsFacility::renewSignedGrids()
{
	//����
	for (auto it = list_grid_signed->begin(); it != list_grid_signed->end(); ++it)
	{
		Grid* grid = *it;
		grid->list_physics_facility->remove(this);
		grid->renewBlockingType(type_blocking);
	}
	list_grid_signed->clear();

	//����ǩ��

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
