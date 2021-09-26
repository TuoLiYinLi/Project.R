#pragma once

#include <iostream>

#include "GlobalData.h"

#include "AnimSystem.h"
#include "MapSystem.h"
#include "GeneSystem.h"
#include "CharaSystem.h"
#include "FacilitySystem.h"
#include "ProjectileSystem.h"
#include "ParticleSystem.h"



class WorldSystem
{
public:
	static WorldSystem* getInstance();
	void destroyInstance();

	AnimSystem* animSys;
	CharaSystem* charaSys;
	FacilitySystem* faciSys;
	GeneSystem* geneSys;
	MapSystem* mapSys;
	ProjectileSystem* projSys;
	ParticleSystem* particleSys;
	
	//销毁角色
	void removeChara(Chara* chara);

	//添加设施
	Facility* addFacility_static(Facility* facility);
	//销毁设施
	void removeFacility_static(Facility* facility);

	//执行整个逻辑帧
	void logicGo();

	

	//执行所有角色逻辑帧
	void charaLogicGo();

	//执行所有设施逻辑帧
	void faciLogicGo();

	//执行所有投射物逻辑帧
	void projLogicGo();

	//执行粒子逻辑
	void particleLogicGo();

protected:
	WorldSystem();
	~WorldSystem();

	static WorldSystem* instance;

};

