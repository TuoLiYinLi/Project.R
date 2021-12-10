#pragma once

#include "PhysicsObject.h"
#include <string>

enum class GameObjectType
{
	none,
	default_chara,
	default_facility,
	default_projectile
};

class GameObject
{
public:
	
	virtual void destroy();	//统一销毁方式

	virtual void update();	//受遍历的更新

	std::string name;	//名称
	GameObjectType type_game_object;	//游戏对象类型
	PhysicsObject* physics_object;	//持有的物理对象


protected:
	GameObject();	//防止外部直接生成实例
	virtual ~GameObject();	//为了继承自我销毁并且保证释放内存,必须虚析构函数

};

