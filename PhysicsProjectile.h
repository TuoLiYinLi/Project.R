#pragma once
#include "Grid.h"
#include "PhysicsObject.h"
#include <list>

enum class ProjectileType
{
    none,//��
	point,//����Ͷ����.����ĳ���ض�λ��
    target,//Ŀ��Ͷ����,�����ض��Ľ�ɫ
    flying,//����Ͷ����,��������������
};

class PhysicsProjectile :
    public PhysicsObject
{
public:
    static PhysicsProjectile* createNew();

	void update() override;
    void renewSignedGrids() override;   //�Ե�ͼǩ���Լ���λ��

    ProjectileType type_projectile; //Ͷ��������


    void renewHitCharas() const; //��ȡ��ײ��������
    void renewHitFacilities() const;//��ȡ��ײ������ʩ
    void renewHitProjectiles() const;//��ȡ��ײ����Ͷ����

    std::list<PhysicsChara*>* getHitCharas() const; //��ȡ��ײ��������
    std::list<PhysicsFacility*>* getHitFacilities() const;//��ȡ��ײ������ʩ
    std::list<PhysicsProjectile*>* getHitProjectiles() const;//��ȡ��ײ����Ͷ����

    double x_v;
    double y_v;

protected:
    PhysicsProjectile();
    ~PhysicsProjectile() override;

    void move(double _dx, double _dy);

    std::list<Grid*>* list_grid_signed;

    std::list<PhysicsChara*>* hit_charas;   //��ײ��������
    std::list<PhysicsFacility*>* hit_facilities;    //��ײ������ʩ
    std::list<PhysicsProjectile*>* hit_projectiles; //��ײ����Ͷ����
};

