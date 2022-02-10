#pragma once
#include "UIObject.h"
class idea_UI_energy :
    public UIObject
{
public:
	static idea_UI_energy* createNew();

	void updateOnRendering() override;
protected:
	idea_UI_energy();
	~idea_UI_energy()override;

	RenderingUnit* inside_image;

	void create_texture()const;
	void renew_texture()const;
	void destroy_texture()const;
};

