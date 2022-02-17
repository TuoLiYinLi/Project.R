#pragma once
#include "UIObject.h"
#include <list>

class idea_UI_sizer_button;
class abstract_inspect_target;

//ui�еĽ�ɫ����ʩɸѡ��
class idea_UI_sizer :
    public UIObject
{
public:
    static idea_UI_sizer* createNew();

    void enable();//����
    void disable();//�ر�

    void onMouseRoll(bool forward) override;//����꿪ʼ����,�����ٶ�

    void updateOnRendering() override;//��Ⱦʱ����

    bool flag_enabled;//�Ƿ�����

    double display_length;//��ʾ����ĳ���
    double content_length;//��ť���ܳ���
    double velocity;//�����ٶ�
    double obstruction;//����
    double position;//�ʵ�����

protected:
    idea_UI_sizer();
    ~idea_UI_sizer()override;

    std::list<idea_UI_sizer_button*>* children;//���е�����UI��ť

    void update_position();//�����ʵ��˶�

    void create_button(int _offset, abstract_inspect_target* _target);//���쵥����ť
    int setup_buttons(int grid_x, int grid_y);//�������еİ�ť
    void clear_buttons()const;

    void set_border_line_texture()const;
};

