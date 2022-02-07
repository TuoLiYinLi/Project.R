#pragma once

#include "PhysicsObject.h"

#include <string>

#include "RenderingAnimation.h"

enum class GameObjectType
{
	default_object = 0,//Ĭ����Ϸ���
	default_chara = 1,//Ĭ�ϵĽ�ɫ���
	default_facility = 3,//Ĭ�ϵ���ʩ���
	default_projectile = 2,//Ĭ�ϵ�Ͷ�������
	default_particle = 4//Ĭ�ϵ��������
};

class GameObject
{
public:
	
	virtual void destroy();	//ͳһ���ٷ�ʽ

	virtual void update();	//�ܱ����ĸ����ǹ̶�������
	virtual void updateOnRendering();	//�ܱ����ĸ���,����Ⱦ֡ʱ����

	bool checkIfDestroy()const;//ѯ���Ƿ��������
	bool checkIfStatic()const;//����Ƿ�Ϊ��̬

	std::string name;	//����
	GameObjectType type_game_object;	//��Ϸ��������

	PhysicsObject* physics_object;	//���е��������
	RenderingUnit* rendering_unit;	//������Ԫ

	static int getGameObjectNum();//��ȡ��Ծ��GameObject����

protected:
	GameObject();	//��ֹ�ⲿֱ������ʵ��,GameObject��һ������ʵ�����ĳ�����
	virtual ~GameObject();	//Ϊ�˼̳��������ٲ��ұ�֤�ͷ��ڴ�,��������������

	bool flag_destroy;//�Ƿ��Ѿ���������
	bool flag_static;//�Ƿ�Ϊ��̬���(����������)

private:
	static int game_object_num;//��Ծ��game object����
};

