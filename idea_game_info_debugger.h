#pragma once
#include "GameObject.h"

//��ʾ��Ϸ��ϢDebug�����
class idea_game_info_debugger :
    public GameObject
{
public:
    static idea_game_info_debugger* createNew();
    void update() override;
protected:
    idea_game_info_debugger();
    ~idea_game_info_debugger()override;

    void renew_texture()const;

    void create_texture()const;

    void destroy_texture()const;

    void render_text()const;
};

