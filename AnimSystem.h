#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "GlobalData.h"

#include "AnimType.h"
#include "AnimationUnit.h"
class AnimationUnit;
#include "TTFUnit.h"
class TTFUnit;

class AnimSystem
{
public:
	std::vector<std::vector<SDL_Texture*>*>* animList;//һ����ά�Ĳ����б�,���ڼ������еĶ�����Դ
	std::list<AnimationUnit*>* animUnitList;//������Ԫ�б�,������Ҫ��Ⱦ�Ķ���Ԫ��
	std::list<TTFUnit*>* fontUnitList;//���嵥Ԫ�б�

	//��ȡ����ʵ��
	static AnimSystem* getInstance();
	//���ٺ�����
	void destroyInstance();

	//ȥ������Ԫ��
	void removeAnimUnit(AnimationUnit* _animUnit);

	//ȥ������Ԫ��
	void removeTTFUnit(TTFUnit* _TTFUnit);

	//����ĳһ�ֶ�����Դ
	void loadAnim( AnimType antp);
	//������������Ķ�����Դ
	void loadAllAnim();
	//ж��ĳһ�ֶ�����Դ
	void unloadAnim(AnimType antp);
	//ж����������Ķ�����Դ
	void unloadAllAnim();

	//��Ⱦ�����Ķ�����Ԫ
	void renderOneUnit(AnimationUnit* au);
	//��Ⱦ�����Ķ�����Ԫ
	void renderOneUnit(TTFUnit* tu);
	//��Ⱦ���ж�����Ԫ(��������Ҫ��Ⱦ�Ĳ���)
	void renderAll();
	//���´���λ��
	void updateWindow();

	double vy;//���ڵ�Y����ı��ٶ�
	double vx;//���ڵ�X����ı��ٶ�
	double vs;//���ڵ�����ˮƽ�ı��ٶ�

	double viewX;//���ڵ�X��������
	double viewY;//���ڵ�Y��������
	double viewScale;//���ڵ�����ˮƽ

protected:

	
	//��ȡ������Ԫ�Ķ�����������Ӧ�Ĳ�����Դ
	SDL_Texture* getTextureFromAU(AnimationUnit* au);
	//����ʵ��
	static AnimSystem* instance;
	AnimSystem();
	~AnimSystem();

	double windowWidth;//���ڿ��
	double windowHeight;//���ڸ߶�
};

