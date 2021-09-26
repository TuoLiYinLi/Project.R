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
	
	//���ٽ�ɫ
	void removeChara(Chara* chara);

	//�����ʩ
	Facility* addFacility_static(Facility* facility);
	//������ʩ
	void removeFacility_static(Facility* facility);

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
	WorldSystem();
	~WorldSystem();

	static WorldSystem* instance;

};

