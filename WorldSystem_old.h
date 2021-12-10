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
	
	//���ٽ�ɫ
	void removeChara(Chara_old* chara);

	//�����ʩ
	Facility_old* addFacility_static(Facility_old* facility);
	//������ʩ
	void removeFacility_static(Facility_old* facility);

	//ִ�������߼�֡
	void logicGo();

	

	//ִ�����н�ɫ�߼�֡
	void charaLogicGo();

	//ִ��������ʩ�߼�֡
	void faciLogicGo();

	//ִ������Ͷ�����߼�֡
	void projLogicGo();

	//ִ�������߼�
	void particleLogicGo();

protected:
	WorldSystem_old();
	~WorldSystem_old();

	static WorldSystem_old* instance;

};

