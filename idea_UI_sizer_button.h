#pragma once
#include "UIObject.h"
class RenderingText;
class abstract_inspect_target;
class idea_UI_sizer;

//请使用setup启动
class idea_UI_sizer_button :
    public UIObject
{
public:
    static idea_UI_sizer_button* createNew();

    void updateOnRendering() override;

    void onMouseUp() override;//当鼠标弹起(激活)
    void onMousePressing() override;
    void onMouseEnter() override;
    void onMouseExit() override;
    void onMouseRoll(bool forward) override;//当鼠标滚动


    void setup(idea_UI_sizer* _parent, abstract_inspect_target* _target, int _offset);

protected:
    idea_UI_sizer_button();
    ~idea_UI_sizer_button()override;

    int position_offset;//自己相对父级的纵坐标
    idea_UI_sizer* parent;
    abstract_inspect_target* target;//针对的目标

    SDL_Texture* current_texture_;//当前状态的材质

    SDL_Texture* texture_default_;//每次创建纹理所使用的默认材质
    SDL_Texture* texture_highlight_;//每次创建纹理所使用的高亮材质
    SDL_Texture* texture_pressed_;//每次创建纹理所使用的按下材质

    void createTexture() const;//创建当前状态下对应的材质
    void destroyTexture()const;//销毁现在使用的材质

    void set_inspector();

    RenderingText* floating_text;//当有鼠标靠近时会呈现的提示字体

    void create_floating_text();
    void destroy_floating_text();

	void renew_floating_text_position()const;
};

