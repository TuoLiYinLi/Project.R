#pragma once
#include "GameObject.h"
class idea_physics_debugger :
    public GameObject
{
public:
    static idea_physics_debugger* createNew();
    void update() override;
protected:
    idea_physics_debugger();
    ~idea_physics_debugger()override;

    void renew_texture()const;

    void create_texture()const;

    void destroy_texture()const;

    void render_one_grid(int grid_x,int grid_y)const;

    void render_all_grids()const;
};

