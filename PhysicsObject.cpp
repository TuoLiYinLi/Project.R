#include "PhysicsObject.h"

#include "Defined.h"
#include "GameObject.h"
#include "WorldSystem.h"

void PhysicsObject::destroy()
{
	delete this;
}

PhysicsObject::PhysicsObject()
{
	physicsObjectNum++;

	game_object = nullptr;
	type_physics = PhysicsType::none;
	type_ally = AllyType::neutral;
	X = 0;
	Y = 0;
	bodyX = 1;
	bodyY = 1;
}

PhysicsObject::~PhysicsObject()
{

	//尝试销毁持有的game_object
	if(game_object)
	{
		game_object->physics_object = nullptr;
		game_object->destroy();
		game_object = nullptr;
	}

	physicsObjectNum--;
}

void PhysicsObject::update()
{

}

void PhysicsObject::setPosition(int x, int y)
{
	X = x;
	Y = y;
	renewSignedGrids();
}

bool PhysicsObject::detectForward(PhysicsDirection direction, BlockingType blocking) const
{
	int x_start = 0, x_end = 0,
		y_start = 0, y_end = 0;
	switch (direction)
	{
	case PhysicsDirection::right:
		x_start = getRightGrid() + 1;
		x_end = x_start;
		y_start = getTopGrid();
		y_end = getBottomGrid();
		break;
	case PhysicsDirection::up:
		x_start = getLeftGrid();
		x_end = getRightGrid();
		y_start = getTopGrid() - 1;
		y_end = y_start;
		break;
	case PhysicsDirection::left:
		x_start = getLeftGrid() - 1;
		x_end = x_start;
		y_start = getTopGrid();
		y_end = getBottomGrid();
		break;
	case PhysicsDirection::down:
		x_start = getLeftGrid();
		x_end = getRightGrid();
		y_start = getBottomGrid() + 1;
		y_end = y_start;
		break;
	}

	if (detectBorder(direction))
	{
		return true;
	}

	for (int i = x_start; i <= x_end; i++)
	{
		for (int j = y_start; j <= y_end; j++)
		{
			const Grid* grid = WorldSystem::getInstance()->getGrid(i, j);
			if (grid->getBlockingType(blocking))
			{
				return true;
			}
		}
	}
	return false;
}

bool PhysicsObject::detectBorder(PhysicsDirection direction) const
{
	switch (direction)
	{
	case PhysicsDirection::right:
		return getRightGrid() + 1 >= static_cast<int>(WORLD_WIDTH);
	case PhysicsDirection::up:
		return getTopGrid() - 1 < 0;
	case PhysicsDirection::left:
		return getLeftGrid() - 1 < 0;
	case PhysicsDirection::down:
		return getBottomGrid() + 1 >= static_cast<int>(WORLD_HEIGHT);
	}

	return false;
}

bool PhysicsObject::detectLocal(BlockingType blocking)
{
	const int x_start = getLeftGrid();
	const int x_end = getRightGrid();
	const int y_start = getTopGrid();
	const int y_end = getBottomGrid();

	for (int i = x_start; i <= x_end; i++)
	{
		for (int j = y_start; j <= y_end; j++)
		{
			const Grid* grid = WorldSystem::getInstance()->getGrid(i, j);
			if(grid->getBlockingType(blocking))
			{
				return true;
			}
		}
	}
	return false;
}


PhysicsType PhysicsObject::getPhysicsType() const
{
	return type_physics;
}

double PhysicsObject::getTop() const
{
	return Y;
}
double PhysicsObject::getBottom() const
{
	return Y + bodyY;
}
double PhysicsObject::getLeft() const
{
	return X;
}
double PhysicsObject::getRight() const
{
	return X + bodyX;
}

int PhysicsObject::getTopGrid() const
{
	const double top = getTop();
	return static_cast<int>(ceil(top - 0.5));
}
int PhysicsObject::getBottomGrid() const
{
	const double bottom = getBottom();
	return static_cast<int>(floor(bottom - 0.5));
}
int PhysicsObject::getLeftGrid() const
{
	const double left = getLeft();
	return static_cast<int>(ceil(left - 0.5));
}
int PhysicsObject::getRightGrid() const
{
	const double right = getRight();
	return static_cast<int>(floor(right - 0.5));
}

int PhysicsObject::physicsObjectNum = 0;

int PhysicsObject::getPhysicsObjectNum()
{
	return physicsObjectNum;
}
