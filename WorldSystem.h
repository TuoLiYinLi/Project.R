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

	void logicGo();	//逻辑更新
	void logicGoOnRendering()const;	//渲染时的物件更新

	void sortGameObjectList()const;//对游戏物体重新排序

	std::list<PhysicsChara*>* list_physics_chara;	//角色物理全集
	std::list<PhysicsFacility*>* list_physics_facility;	//设施物理全集
	std::list<PhysicsProjectile*>* list_physics_projectile;	//投射物物理全集

	std::list<GameObject*>* list_game_objects;	//游戏物件全集

	//游戏数据
	double goldust_energy;//金沙能量
	double goldust_energy_recovery;//金沙能量恢复速度

	int enemy_wave_CD;//敌人下一波倒计时
	int enemy_wave_num;//当前波次数

	Grid* getGrid(int _x,int _y)const;

protected:
	//单例实例
	std::vector<std::vector<Grid*>*>* map;//全部的网格
	static WorldSystem* instance;	//唯一实例
	WorldSystem();
	~WorldSystem();

	void logicGo_physics() const;	//物理更新
	void logicGo_game_objects()	const;	//物件更新
	void logicGo_game_data();	//游戏数据更新

	double goldust_energy_accumulation;//金沙能量恢复累积量

	static bool compareGameObjects(GameObject* o1, GameObject* o2);
};

