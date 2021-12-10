#pragma once

#include "PhysicsObject.h"
#include <string>

enum class GameObjectType
{
	none,
	default_chara,
	default_facility,
	default_projectile
};

class GameObject
{
public:
	
	virtual void destroy();	//ͳһ���ٷ�ʽ

	virtual void update();	//�ܱ����ĸ���

	std::string name;	//����
	GameObjectType type_game_object;	//��Ϸ��������
	PhysicsObject* physics_object;	//���е��������


protected:
	GameObject();	//��ֹ�ⲿֱ������ʵ��
	virtual ~GameObject();	//Ϊ�˼̳��������ٲ��ұ�֤�ͷ��ڴ�,��������������

};

