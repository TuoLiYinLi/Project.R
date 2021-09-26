#pragma once
#include <iostream>

#include "Projectile.h"
class Projectile;

class ProjectileSystem
{
public:
	//获取单例实例
	static ProjectileSystem* getInstance();
	//将单例清除
	void destroyInstance();

	std::list<Projectile*>* projList;//投射物的列表
	
	//移除投掷物
	void removeProjectile(Projectile* projectile);


	//汇报内存使用
	void reportMemory();

private:
	static ProjectileSystem* instance;//单例实例
	ProjectileSystem();
	~ProjectileSystem();
};

