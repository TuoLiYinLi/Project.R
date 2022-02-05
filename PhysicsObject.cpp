#include "PhysicsObject.h"

#include "GameObject.h"

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


void PhysicsObject::renewSignedGrids()
{
	
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
	return (int)ceil(top - 0.5);
}
int PhysicsObject::getBottomGrid() const
{
	const double bottom = getBottom();
	return (int)floor(bottom - 0.5);
}
int PhysicsObject::getLeftGrid() const
{
	const double left = getLeft();
	return (int)ceil(left - 0.5);
}
int PhysicsObject::getRightGrid() const
{
	const double right = getRight();
	return (int)floor(right - 0.5);
}

int PhysicsObject::physicsObjectNum = 0;

int PhysicsObject::getPhysicsObjectNum()
{
	return physicsObjectNum;
}
