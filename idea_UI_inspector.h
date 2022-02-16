#pragma once
#include "UIObject.h"

class UIScroll;
class idea_UI_inspector_exit;
class abstract_inspect_target;

class idea_UI_inspector :
    public UIObject
{
public:

    static idea_UI_inspector* createNew();

    void updateOnRendering() override;

    void enable();
    void disable();

    void set_target(abstract_inspect_target* _target);


protected:
    idea_UI_inspector();
    ~idea_UI_inspector()override;

    idea_UI_inspector_exit* exit_button;

    abstract_inspect_target* target;

    SDL_Texture* t_main;
    SDL_Texture* t_data;
    SDL_Texture* t_extra;

    UIScroll* s_main;
    UIScroll* s_data;
    UIScroll* s_extra;

    bool flag_enable;// «∑Ò∆Ù”√
};

