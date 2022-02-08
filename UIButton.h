#pragma once
#include "UIObject.h"
class UIButton :
    public UIObject
{
public:
    static UIButton* createNew();

    SDL_Texture* texture_default;
    SDL_Texture* texture_pressed;
    SDL_Texture* texture_highlight;

    void onMouseUp() override;
    void onMousePressing() override;
    void onMouseEnter() override;
    void onMouseExit() override;

    void setCallback(void(*_function_name)());
	
protected:
    UIButton();
    ~UIButton()override;


    void(*callback_f)();//记录的回调函数
};

