#pragma once
#include "UIButton.h"
#include "UIObject.h"

class idea_UI_speed_controller :
    public UIObject
{
public:
	static idea_UI_speed_controller* createNew();

	void updateOnRendering() override;
protected:
	idea_UI_speed_controller();
	~idea_UI_speed_controller()override;

	UIButton* b1;
	UIButton* b2;
	UIButton* b3;
	UIButton* b4;
	UIButton* b5;

	static  void set_time_stop();
	static  void set_time_go();
	static  void set_time_speed_1();
	static  void set_time_speed_2();
	static  void set_time_speed_3();

	SDL_Texture* texture_default;
	SDL_Texture* texture_selected;
	SDL_Texture* texture_highlight;
	SDL_Texture* texture_pressed;
};

