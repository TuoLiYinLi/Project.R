#include "GameObject.h"

#include "WorldSystem.h"

void GameObject::destroy()
{
	delete this;
}

int GameObject::game_object_num = 0;

int GameObject::getGameObjectNum()
{
	return game_object_num;
}


GameObject::GameObject()
{
	game_object_num++;

	name = L"default_game_object";
	type_game_object = GameObjectType::default_object;

	flag_destroy = false;
	flag_static = false;

	physics_object = nullptr;
	rendering_unit = nullptr;

	//将自己添加到物体列表
	WorldSystem::getInstance()->list_game_objects->push_back(this);
	WorldSystem::getInstance()->sortGameObjectList();
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

	if (rendering_unit)
	{
		rendering_unit->destroy();
		rendering_unit = nullptr;
	}

	//不需要将自己从设施物理列表移除,由WorldSystem将对象移除
	//WorldSystem::getInstance()->list_game_objects->remove(this);

	game_object_num--;
}

void GameObject::update()
{
	
}

void GameObject::updateOnRendering()
{
	
}


bool GameObject::checkIfDestroy() const
{
	return flag_destroy;
}

void GameObject::readyToDestroy()
{
	flag_destroy = true;
	flag_static = true;
	if (rendering_unit)rendering_unit->flag_enable = false;
}


bool GameObject::checkIfStatic() const
{
	return flag_static;
}
