#pragma once

#include "PhysicsObject.h"
#include <string>

#include "RenderingAnimation.h"

enum class GameObjectType
{
	default_object=0,//Ĭ����Ϸ���
	default_chara=1,//Ĭ�ϵĽ�ɫ���
	default_facility=3,//Ĭ�ϵ���ʩ���
	default_projectile=2,//Ĭ�ϵ�Ͷ�������
};

class GameObject
{
public:
	
	virtual void destroy();	//ͳһ���ٷ�ʽ

	virtual void update();	//�ܱ����ĸ����ǹ̶�������
	virtual void updateOnRendering();	//�ܱ����ĸ���

	bool getIfDestroy()const;//ѯ���Ƿ��������
	std::string name;	//����
	GameObjectType type_game_object;	//��Ϸ��������

	PhysicsObject* physics_object;	//���е��������
	RenderingUnit* animation_unit;	//������Ԫ

	static int getGameObjectNum();//��ȡ��Ծ��GameObject����

protected:

	bool flag_destroy;//�Ƿ��Ѿ���������
	GameObject();	//��ֹ�ⲿֱ������ʵ��
	virtual ~GameObject();	//Ϊ�˼̳��������ٲ��ұ�֤�ͷ��ڴ�,��������������

private:
	static int game_object_num;//��Ծ��game object����
};

