#pragma once
#include "RenderingUnit.h"
class RenderingText :
    public RenderingUnit
{
public:
    //�����µĶ���Ԫ��
    static class RenderingText* createNew();

    void setTexture(const char* utf8_msg,SDL_Color color, double scale);

protected:
    RenderingText();
    ~RenderingText() override;
};

