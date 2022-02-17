#pragma once
#include "GameObject.h"
#include <string>


//理念 游戏信息Debugger
class idea_debugger_game_info :
    public GameObject
{
public:
    static idea_debugger_game_info* createNew();
    void updateOnRendering() override;
protected:
    idea_debugger_game_info();
    ~idea_debugger_game_info()override;

    void create_texture()const;

    void renew_texture()const;

    void destroy_texture()const;

    std::wstring create_text()const;
};

