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

	void logicGo() const;	//�߼�����

	std::vector<std::vector<Grid*>*>* map;//ȫ��������

	std::list<PhysicsChara*>* list_physics_chara;	//��ɫ����ȫ��
	std::list<PhysicsFacility*>* list_physics_facility;	//��ʩ����ȫ��
	std::list<PhysicsProjectile*>* list_physics_projectile;	//Ͷ��������ȫ��

	std::list<GameObject*>* list_game_objects;	//��Ϸ���ȫ��


protected:
	//����ʵ��
	static WorldSystem* instance;	//Ψһʵ��
	WorldSystem();
	~WorldSystem();

	void logicGo_physics() const;	//�������
	void logicGo_game_objects()	const;	//�������


};

