#pragma once
#include "RenderingUnit.h"
class RenderingText :
    public RenderingUnit
{
public:
    //创建新的动画元件
    static class RenderingText* createNew();

    void setTexture(const char* utf8_msg,SDL_Color color, double scale);

protected:
    RenderingText();
    ~RenderingText() override;
};

