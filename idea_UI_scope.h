#pragma once
#include "GameObject.h"
class idea_UI_scope :
    public GameObject
{
public:
	static idea_UI_scope* createNew();
	void updateOnRendering() override;
	void enable();
	void disable();
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);//…Ë÷√—’…´
protected:
	idea_UI_scope();
	~idea_UI_scope()override;

	void create_texture()const;
	void renew_texture()const;
	void renew_state()const;
	void destroy_texture()const;

	Uint8 color_r;
	Uint8 color_g;
	Uint8 color_b;
	Uint8 color_a;
};

