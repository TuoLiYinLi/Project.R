#pragma once
#include <vector>

#include "Facility.h"

//游戏物体 多样设施
//囊括不同变体的同种设施
class FacilityVarious :
    public Facility
{
public:
    static FacilityVarious* createNew();
protected:
    FacilityVarious();
    ~FacilityVarious()override;

    std::vector<AnimationType>* list_various_texture;

    void setVariousTexture();
};

