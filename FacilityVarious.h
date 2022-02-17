#pragma once
#include <vector>

#include "Facility.h"

//��Ϸ���� ������ʩ
//������ͬ�����ͬ����ʩ
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

