#pragma once
#include "UIObject.h"
class abstract_SizerTarget;
class idea_UI_sizer;

//��ʹ��setup����
class idea_UI_sizer_button :
    public UIObject
{
public:
    static idea_UI_sizer_button* createNew();

    void updateOnRendering() override;

    void onMouseUp() override;//����굯��(����)
    void onMousePressing() override;
    void onMouseEnter() override;
    void onMouseExit() override;
    void onMouseRoll(bool forward) override;//��������


    void setup(idea_UI_sizer* _parent, abstract_SizerTarget* _target, int _offset);

protected:
    idea_UI_sizer_button();
    ~idea_UI_sizer_button()override;

    int position_offset;//�Լ���Ը�����������
    idea_UI_sizer* parent;
    abstract_SizerTarget* target;//��Ե�Ŀ��

    SDL_Texture* current_texture_;//��ǰ״̬�Ĳ���

    SDL_Texture* texture_default_;//ÿ�δ���������ʹ�õ�Ĭ�ϲ���
    SDL_Texture* texture_highlight_;//ÿ�δ���������ʹ�õĸ�������
    SDL_Texture* texture_pressed_;//ÿ�δ���������ʹ�õİ��²���

    void createTexture() const;//������ǰ״̬�¶�Ӧ�Ĳ���
    void destroyTexture()const;//��������ʹ�õĲ���
};

