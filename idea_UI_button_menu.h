#pragma once
#include "UIButton.h"
class idea_UI_button_menu :
    public UIButton
{
public:
    static idea_UI_button_menu* createNew();
protected:
    idea_UI_button_menu();
    ~idea_UI_button_menu()override;
};

