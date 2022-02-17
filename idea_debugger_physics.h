#pragma once
#include "GameObject.h"


class idea_debugger_physics :
    public GameObject
{
public:
    static idea_debugger_physics* createNew();
    void updateOnRendering() override;
protected:
    idea_debugger_physics();
    ~idea_debugger_physics()override;

    void renew_texture()const;

    void create_texture()const;

    void destroy_texture()const;

    void render_one_grid(int grid_x,int grid_y)const;

    void render_all_grids()const;
};

