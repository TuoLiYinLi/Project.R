#include "GlobalData.h"

//��ʼ��SDL��ܱ���
SDL_Window* GlobalData::win = nullptr;
SDL_Renderer* GlobalData::renderer = nullptr;
SDL_Event GlobalData::evt;
TTF_Font* GlobalData::font = nullptr;
bool GlobalData::quitFlag = false;
//ÿ�����֡��������Ⱦ��
Uint32 GlobalData::FPS = 0;
//����¼����һ��ʱ�� SDL_GetTicks
Uint32 GlobalData::lastTicks = 0;
//��һ֡����һ֡�仯��ʱ��
Uint32 GlobalData::deltaTime = 0;
//�߼�֡����ʱ
Uint32 GlobalData::logicFrameCD = 0;
//����һ����һ�ֵĵ���
Uint32 GlobalData::perSecondCountDown = 0;

int GlobalData::KingX = 0;
int GlobalData::KingY = 0;