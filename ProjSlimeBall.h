#pragma once
#include "ImmediateProj.h"
class ProjSlimeBall :
    public ImmediateProj
{
public:
    static ProjSlimeBall* createNew();
    virtual void destroy();

    //����Ŀ���ɫ�ᴥ��
    virtual void onHit(Chara* c);
    //����Ŀ�꽨���ᴥ��
    virtual void onHit(Facility* f);
    //ʱ���������
    virtual void onEnd();

protected:
    ProjSlimeBall();
    ~ProjSlimeBall();
};

