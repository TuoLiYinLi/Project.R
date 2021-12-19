#pragma once
#include "Grid.h"
#include "PhysicsObject.h"
#include <list>

enum class ProjectileType
{
    none,//无
	point,//定点投射物.飞向某个特定位置
    target,//目标投射物,飞向特定的角色
    flying,//飞行投射物,按照物理规则飞行
};

class PhysicsProjectile :
    public PhysicsObject
{
public:
    static PhysicsProjectile* createNew();

	void update() override;
    void renewSignedGrids() override;   //对地图签入自己的位置

    ProjectileType type_projectile; //投射物类型


    void renewHitCharas() const; //获取碰撞到的人物
    void renewHitFacilities() const;//获取碰撞到的设施
    void renewHitProjectiles() const;//获取碰撞到的投射物

    std::list<PhysicsChara*>* getHitCharas() const; //获取碰撞到的人物
    std::list<PhysicsFacility*>* getHitFacilities() const;//获取碰撞到的设施
    std::list<PhysicsProjectile*>* getHitProjectiles() const;//获取碰撞到的投射物

    double x_v;
    double y_v;

protected:
    PhysicsProjectile();
    ~PhysicsProjectile() override;

    void move(double _dx, double _dy);

    std::list<Grid*>* list_grid_signed;

    std::list<PhysicsChara*>* hit_charas;   //碰撞到的人物
    std::list<PhysicsFacility*>* hit_facilities;    //碰撞到的设施
    std::list<PhysicsProjectile*>* hit_projectiles; //碰撞到的投射物
};

