#pragma once
#include "RenderingUnit.h"
class RenderingText :
    public RenderingUnit
{
public:
    //�����µĶ���Ԫ��
    static class RenderingText* createNew();
    //��������Unicode��
    void setTexture(const wchar_t* unicode_str, double scale, SDL_Color color);

    //��������Unicode��
    void setTexture(const wchar_t* unicode_str, double scale, SDL_Color color,int wrapLength);

protected:
    RenderingText();
    ~RenderingText() override;
};

