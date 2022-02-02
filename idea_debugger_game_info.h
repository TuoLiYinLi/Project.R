#pragma once
#include "GameObject.h"
#include <list>

//显示游戏信息Debug的物件
class idea_debugger_game_info :
    public GameObject
{
public:
    static idea_debugger_game_info* createNew();
    void updateOnRendering() override;
protected:
    idea_debugger_game_info();
    ~idea_debugger_game_info()override;

    void renew_texture()const;

    void create_texture()const;

    void destroy_texture()const;

    void render_text()const;

    std::list<SDL_Texture*>* last_text_textures;
};

