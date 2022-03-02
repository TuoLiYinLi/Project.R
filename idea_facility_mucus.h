#pragma once
#include "Facility.h"
class idea_facility_mucus :
    public Facility
{
public:
    static idea_facility_mucus* createNew();

    void onHit(Projectile* p) override;
protected:
    idea_facility_mucus();
};

