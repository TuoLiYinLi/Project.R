#include "PhysicsChara.h"
#include "WorldSystem.h"
#include "SDL.h"

PhysicsChara* PhysicsChara::createNew()
{
	PhysicsChara* physics_chara = new PhysicsChara();
	if(!physics_chara)
	{
		SDL_Log(u8"���� ����physics_chara�ڴ治��");
	}
	return physics_chara;
}

PhysicsChara::PhysicsChara()
{
	type_physics = PhysicsType::chara;

	if_moving = false;
	//���Լ���ӵ���ɫ�����б�
	WorldSystem::getInstance()->list_physics_chara->push_front(this);
}

PhysicsChara::~PhysicsChara()
{
	//���Լ��ӽ�ɫ�����б��Ƴ�
	WorldSystem::getInstance()->list_physics_chara->remove(this);
}


void PhysicsChara::update()
{
	//���ø������
	PhysicsObject::update();
}

void PhysicsChara::move(Direction direction)
{
	
}

void PhysicsChara::signPosition()
{
	
}

