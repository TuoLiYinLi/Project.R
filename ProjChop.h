#pragma once
#include "PenetrableProj.h"

class ProjChop :
    public PenetrableProj
{
public:
    static ProjChop* createNew();
    virtual void destroy();

    //����Ŀ���ɫ�ᴥ��
    virtual void onHit(Chara* c);
    //����Ŀ�꽨���ᴥ��
    virtual void onHit(Facility* f);
protected:
    std::list<Chara*>* hitCharaList;//�Ѿ����й��Ľ�ɫ
    std::list<Facility*>* hitFaciList;//�Ѿ����й�����ʩ
    ProjChop();
    ~ProjChop();
};

