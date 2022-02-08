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

    void renew_state();//更新用户交互状态

    SDL_Texture* texture_exit_button;

    Monster* tar_monster;//选取的怪物
    Warrior* tar_warrior;//选取的勇者
    Facility* tar_facility;//选取的设施

    bool flag_enable;//是否启用
};

