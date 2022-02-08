#pragma once
#include "Facility.h"
#include "GameObject.h"
#include "Monster.h"
#include "Warrior.h"

class idea_UI_inspector :
    public GameObject
{
public:

    static idea_UI_inspector* createNew();

    void updateOnRendering() override;

    void enable();
    void disable();
protected:
    idea_UI_inspector();
    ~idea_UI_inspector()override;

    void renew_texture()const;

    void create_texture(int w, int h)const;

    void destroy_texture()const;

    void renew_state();//�����û�����״̬

    SDL_Texture* texture_exit_button;

    Monster* tar_monster;//ѡȡ�Ĺ���
    Warrior* tar_warrior;//ѡȡ������
    Facility* tar_facility;//ѡȡ����ʩ

    bool flag_enable;//�Ƿ�����
};

