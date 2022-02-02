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
	static WorldSystem* getInstance();	//��ȡʵ��
	static  void destroyInstance();	//���ٺ�����

	void logicGo();	//�߼�����
	void logicGoOnRendering()const;	//��Ⱦʱ���������

	void sortGameObjectList()const;//����Ϸ������������

	std::list<PhysicsChara*>* list_physics_chara;	//��ɫ����ȫ��
	std::list<PhysicsFacility*>* list_physics_facility;	//��ʩ����ȫ��
	std::list<PhysicsProjectile*>* list_physics_projectile;	//Ͷ��������ȫ��

	std::list<GameObject*>* list_game_objects;	//��Ϸ���ȫ��

	//��Ϸ����
	double goldust_energy;//��ɳ����
	double goldust_energy_recovery;//��ɳ�����ָ��ٶ�

	int enemy_wave_CD;//������һ������ʱ
	int enemy_wave_num;//��ǰ������

	Grid* getGrid(int _x,int _y)const;

protected:
	//����ʵ��
	std::vector<std::vector<Grid*>*>* map;//ȫ��������
	static WorldSystem* instance;	//Ψһʵ��
	WorldSystem();
	~WorldSystem();

	void logicGo_physics() const;	//�������
	void logicGo_game_objects()	const;	//�������
	void logicGo_game_data();	//��Ϸ���ݸ���

	double goldust_energy_accumulation;//��ɳ�����ָ��ۻ���

	static bool compareGameObjects(GameObject* o1, GameObject* o2);
};

