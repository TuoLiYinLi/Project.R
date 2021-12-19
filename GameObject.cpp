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

	//���Լ���ӵ���ʩ�����б�
	WorldSystem::getInstance()->list_game_objects->push_front(this);
}

GameObject::~GameObject()
{

	//���ٰ󶨵���������
	if(physics_object)
	{
		physics_object->game_object = nullptr;
		physics_object->destroy();
		physics_object = nullptr;
	}


	//���Լ�����ʩ�����б��Ƴ�
	WorldSystem::getInstance()->list_game_objects->remove(this);
}

void GameObject::update()
{
	
}


