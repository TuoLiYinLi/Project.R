#pragma once
#include "UIObject.h"
class UIScroll :
    public UIObject
{
public:
    static UIScroll* createNew();

    void updateOnRendering() override;

    void onMouseRoll(bool forward) override;

    void setUp(SDL_Texture* _texture_full, int _x, int _y, int _texture_width, int _texture_height,
        int _display_height, double _limit_length, double _obstruction, double _resistant,double roll_speed);

protected:
    UIScroll();
    ~UIScroll()override;

    SDL_Texture* texture_full;//整个的材质
    int texture_full_height;//整个材质的高度
    int texture_full_width;//整个材质的宽度

    double mouse_roll_speed;//鼠标提供的速度

    double position;//模拟质点的坐标
    double limit_length;//限制超出的最远长度
    double velocity;//模拟质点的运动速度
    double obstruction;//质点的阻力
    double resistance;//超出界限的抵抗力(0,1.0)

    bool user_rolling;//是否用户正在对此滚动鼠标

    Uint8 reset_color_a;
    Uint8 reset_color_r;
    Uint8 reset_color_g;
    Uint8 reset_color_b;

    void create_texture();
    void destroy_texture();
    bool can_destroy_texture;
};

