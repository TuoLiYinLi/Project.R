#pragma once

#include "PhysicsObject.h"
#include <string>

#include "RenderingAnimation.h"

enum class GameObjectType
{
	default_object=0,//默认游戏物件
	default_chara=1,//默认的角色物件
	default_facility=3,//默认的设施物件
	default_projectile=2,//默认的投射物物件
};

class GameObject
{
public:
	
	virtual void destroy();	//统一销毁方式

	virtual void update();	//受遍历的更新是固定触发的
	virtual void updateOnRendering();	//受遍历的更新

	bool getIfDestroy()const;//询问是否可以销毁
	std::string name;	//名称
	GameObjectType type_game_object;	//游戏对象类型

	PhysicsObject* physics_object;	//持有的物理对象
	RenderingUnit* animation_unit;	//动画单元

	static int getGameObjectNum();//获取活跃的GameObject数量

protected:

	bool flag_destroy;//是否已经可以销毁
	GameObject();	//防止外部直接生成实例
	virtual ~GameObject();	//为了继承自我销毁并且保证释放内存,必须虚析构函数

private:
	static int game_object_num;//活跃的game object数量
};

