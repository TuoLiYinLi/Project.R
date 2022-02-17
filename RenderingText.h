#pragma once
#include "RenderingUnit.h"

//渲染单元 文字单元
class RenderingText :
    public RenderingUnit
{
public:
    //创建新的动画元件
    static class RenderingText* createNew();
    //创建单行Unicode字
    void setTexture(const wchar_t* unicode_str, double scale, SDL_Color color);
    void setTexture(const wchar_t* unicode_str, double scale, SDL_Color color, SDL_Color bg_color);

    //创建多行Unicode字
    void setTexture(const wchar_t* unicode_str, double scale, SDL_Color color,int wrapLength);
    void setTexture(const wchar_t* unicode_str, double scale, SDL_Color color, SDL_Color bg_color, int wrapLength);

protected:
    RenderingText();
    ~RenderingText() override;
};

