#pragma once

#include <iostream>

//#include "GlobalData.h"

#include "AnimationSystem.h"
#include "MapSystem.h"
#include "GeneSystem.h"
#include "CharaSystem.h"
#include "FacilitySystem.h"
#include "ProjectileSystem.h"
#include "ParticleSystem.h"



class WorldSystem_old
{
public:
	static WorldSystem_old* getInstance();
	void destroyInstance();

	AnimationSystem* animSys;
	CharaSystem* charaSys;
	FacilitySystem* faciSys;
	GeneSystem* geneSys;
	MapSystem* mapSys;
	ProjectileSystem* projSys;
	ParticleSystem* particleSys;
	
	//销毁角色
	void removeChara(Chara_old* chara);

	//添加设施
	Facility_old* addFacility_static(Facility_old* facility);
	//销毁设施
	void removeFacility_static(Facility_old* facility);

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
	WorldSystem_old();
	~WorldSystem_old();

	static WorldSystem_old* instance;

};

