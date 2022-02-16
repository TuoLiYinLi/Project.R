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

    SDL_Texture* texture_full;//�����Ĳ���
    int texture_full_height;//�������ʵĸ߶�
    int texture_full_width;//�������ʵĿ��

    double mouse_roll_speed;//����ṩ���ٶ�

    double position;//ģ���ʵ������
    double limit_length;//���Ƴ�������Զ����
    double velocity;//ģ���ʵ���˶��ٶ�
    double obstruction;//�ʵ������
    double resistance;//�������޵ĵֿ���(0,1.0)

    bool user_rolling;//�Ƿ��û����ڶԴ˹������

    Uint8 reset_color_a;
    Uint8 reset_color_r;
    Uint8 reset_color_g;
    Uint8 reset_color_b;

    void create_texture();
    void destroy_texture();
    bool can_destroy_texture;
};

