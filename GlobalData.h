#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
class GlobalData
{
public:
	//��ʼ��SDL��ܱ���
	static SDL_Window* win ;
	static SDL_Renderer* renderer ;
	static SDL_Event evt;
	static TTF_Font* font;
	static bool quitFlag ;
	//ÿ�����֡��������Ⱦ��
	static Uint32 FPS ;
	//����¼����һ��ʱ�� SDL_GetTicks
	static Uint32 lastTicks ;
	//��һ֡����һ֡�仯��ʱ��
	static Uint32 deltaTime ;
	//�߼�֡����ʱ
	static Uint32 logicFrameCD ;
	//����һ����һ�ֵĵ���
	static Uint32 perSecondCountDown ;
	
	//ħ����λ��X
	static int KingX;

	//ħ����λ��Y
	static int KingY;

};

