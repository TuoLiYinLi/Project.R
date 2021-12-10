#include "PhysicsChara.h"
#include "WorldSystem.h"
#include "SDL.h"

PhysicsChara* PhysicsChara::createNew()
{
	PhysicsChara* physics_chara = new PhysicsChara();
	if(!physics_chara)
	{
		SDL_Log(u8"警告 分配physics_chara内存不足");
	}
	return physics_chara;
}

PhysicsChara::PhysicsChara()
{
	type_physics = PhysicsType::chara;

	if_moving = false;
	//将自己添加到角色物理列表
	WorldSystem::getInstance()->list_physics_chara->push_front(this);
}

PhysicsChara::~PhysicsChara()
{
	//将自己从角色物理列表移除
	WorldSystem::getInstance()->list_physics_chara->remove(this);
}


void PhysicsChara::update()
{
	//调用父类更新
	PhysicsObject::update();
}

void PhysicsChara::move(Direction direction)
{
	
}

void PhysicsChara::signPosition()
{
	
}

