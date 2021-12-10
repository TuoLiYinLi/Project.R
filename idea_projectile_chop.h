#pragma once
#include "PenetrableProj.h"

class idea_projectile_chop :
    public PenetrableProj
{
public:
    static idea_projectile_chop* createNew();
    virtual void destroy();

    //����Ŀ���ɫ�ᴥ��
    virtual void onHit(Chara_old* c);
    //����Ŀ�꽨���ᴥ��
    virtual void onHit(Facility_old* f);
protected:
    std::list<Chara_old*>* hitCharaList;//�Ѿ����й��Ľ�ɫ
    std::list<Facility_old*>* hitFaciList;//�Ѿ����й�����ʩ
    idea_projectile_chop();
    ~idea_projectile_chop();
};

