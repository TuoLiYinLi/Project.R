#pragma once
#include "UIObject.h"
#include <list>

class idea_UI_sizer_button;
class abstract_inspect_target;

//ui中的角色与设施筛选器
class idea_UI_sizer :
    public UIObject
{
public:
    static idea_UI_sizer* createNew();

    void enable();//启用
    void disable();//关闭

    void onMouseRoll(bool forward) override;//当鼠标开始滚动,设置速度

    void updateOnRendering() override;//渲染时更新

    bool flag_enabled;//是否被启用

    double display_length;//显示区域的长度
    double content_length;//按钮的总长度
    double velocity;//滚动速度
    double obstruction;//阻力
    double position;//质点坐标

protected:
    idea_UI_sizer();
    ~idea_UI_sizer()override;

    std::list<idea_UI_sizer_button*>* children;//持有的所有UI按钮

    void update_position();//更新质点运动

    void create_button(int _offset, abstract_inspect_target* _target);//创造单个按钮
    int setup_buttons(int grid_x, int grid_y);//创建所有的按钮
    void clear_buttons()const;

    void set_border_line_texture()const;
};

