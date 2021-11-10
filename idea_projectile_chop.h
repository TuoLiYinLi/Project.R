#pragma once
#include "PenetrableProj.h"

class idea_projectile_chop :
    public PenetrableProj
{
public:
    static idea_projectile_chop* createNew();
    virtual void destroy();

    //����Ŀ���ɫ�ᴥ��
    virtual void onHit(Chara* c);
    //����Ŀ�꽨���ᴥ��
    virtual void onHit(Facility* f);
protected:
    std::list<Chara*>* hitCharaList;//�Ѿ����й��Ľ�ɫ
    std::list<Facility*>* hitFaciList;//�Ѿ����й�����ʩ
    idea_projectile_chop();
    ~idea_projectile_chop();
};

