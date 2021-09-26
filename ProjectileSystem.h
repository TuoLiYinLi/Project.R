#pragma once
#include <iostream>

#include "Projectile.h"
class Projectile;

class ProjectileSystem
{
public:
	//��ȡ����ʵ��
	static ProjectileSystem* getInstance();
	//���������
	void destroyInstance();

	std::list<Projectile*>* projList;//Ͷ������б�
	
	//�Ƴ�Ͷ����
	void removeProjectile(Projectile* projectile);


	//�㱨�ڴ�ʹ��
	void reportMemory();

private:
	static ProjectileSystem* instance;//����ʵ��
	ProjectileSystem();
	~ProjectileSystem();
};

