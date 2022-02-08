#pragma once
#include "UIButton.h"
class idea_UI_button_exit :
    public UIButton
{
public:
    static  idea_UI_button_exit* createNew();
protected:
    idea_UI_button_exit();
    ~idea_UI_button_exit()override;
};

