#pragma once

#include "PhysicsObject.h"
#include <string>

#include "RenderingAnimation.h"

enum class GameObjectType
{
	default_object,//Ĭ����Ϸ���
	default_chara,//Ĭ�ϵĽ�ɫ���
	default_facility,//Ĭ�ϵ���ʩ���
	default_projectile//Ĭ�ϵ�Ͷ�������
};

class GameObject
{
public:
	
	virtual void destroy();	//ͳһ���ٷ�ʽ

	virtual void update();	//�ܱ����ĸ���

	bool getIfDestroy()const;//ѯ���Ƿ��������
	std::string name;	//����
	GameObjectType type_game_object;	//��Ϸ��������

	PhysicsObject* physics_object;	//���е��������
	RenderingAnimation* animation_unit;	//������Ԫ


protected:
	bool flag_destroy;//�Ƿ��Ѿ���������
	GameObject();	//��ֹ�ⲿֱ������ʵ��
	virtual ~GameObject();	//Ϊ�˼̳��������ٲ��ұ�֤�ͷ��ڴ�,��������������

};

