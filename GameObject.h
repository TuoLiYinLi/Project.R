#pragma once

#include "PhysicsObject.h"
#include <string>

#include "AnimationUnit.h"

enum class GameObjectType
{
	default_object,//默认游戏物件
	default_chara,//默认的角色物件
	default_facility,//默认的设施物件
	default_projectile//默认的投射物物件
};

class GameObject
{
public:
	
	virtual void destroy();	//统一销毁方式

	virtual void update();	//受遍历的更新

	std::string name;	//名称
	GameObjectType type_game_object;	//游戏对象类型

	PhysicsObject* physics_object;	//持有的物理对象
	AnimationUnit* animation_unit;	//动画单元

protected:
	GameObject();	//防止外部直接生成实例
	virtual ~GameObject();	//为了继承自我销毁并且保证释放内存,必须虚析构函数

};

