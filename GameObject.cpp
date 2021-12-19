#include "GameObject.h"

#include <iostream>

#include "WorldSystem.h"

void GameObject::destroy()
{
	delete this;
}


GameObject::GameObject()
{
	name = u8"default_game_object";
	type_game_object = GameObjectType::default_object;
	physics_object = nullptr;

	//将自己添加到设施物理列表
	WorldSystem::getInstance()->list_game_objects->push_front(this);
}

GameObject::~GameObject()
{

	//销毁绑定的物理物体
	if(physics_object)
	{
		physics_object->game_object = nullptr;
		physics_object->destroy();
		physics_object = nullptr;
	}


	//将自己从设施物理列表移除
	WorldSystem::getInstance()->list_game_objects->remove(this);
}

void GameObject::update()
{
	
}


