#pragma once
#include <list>
#include <vector>

#include "Grid.h"
//#include "PhysicsFacility.h"

class GameObject;
class PhysicsProjectile;
class PhysicsFacility;
class PhysicsChara;

class WorldSystem
{
public:
	static WorldSystem* getInstance();	//获取实例
	static  void destroyInstance();	//销毁和析构

	void logicGo() const;	//逻辑更新

	std::vector<std::vector<Grid*>*>* map;//全部的网格

	std::list<PhysicsChara*>* list_physics_chara;	//角色物理全集
	std::list<PhysicsFacility*>* list_physics_facility;	//设施物理全集
	std::list<PhysicsProjectile*>* list_physics_projectile;	//投射物物理全集

	std::list<GameObject*>* list_game_objects;	//游戏物件全集


protected:
	//单例实例
	static WorldSystem* instance;	//唯一实例
	WorldSystem();
	~WorldSystem();

	void logicGo_physics() const;	//物理更新
	void logicGo_game_objects()	const;	//物件更新


};

