#pragma once
#include "PhysicsObject.h"
class PhysicsProjectile :
    public PhysicsObject
{
public:
    static PhysicsProjectile* createNew();

	void update() override;
    void signPosition() override;   //对地图签入自己的位置

    void move(double d_x, double d_y);

protected:
    PhysicsProjectile();
    ~PhysicsProjectile() override;

    

};

