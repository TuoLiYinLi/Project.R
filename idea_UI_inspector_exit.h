#pragma once
#include "UIButton.h"
class idea_UI_inspector_exit :
    public UIButton
{
public:
    static  idea_UI_inspector_exit* createNew();

    void enable();
    void disable();

    void onMouseUp() override;
protected:
    idea_UI_inspector_exit();
    ~idea_UI_inspector_exit()override;
};

