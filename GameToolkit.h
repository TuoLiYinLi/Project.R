#pragma once
#include <string>
#include <SDL.h>

#include "Facility.h"
#include "PhysicsObject.h"
#include "integration_gene_container.h"

//��̬������
class GameToolkit
{
public:
	//����������ת��Ϊ��������
	static void transPositionWorldToWindow(double x_world,double y_world,double* x_window,double* y_window);
	//����������ת��Ϊ��������
	static void transPositionWindowToWorld(double x_window, double y_window, double* x_world, double* y_world);

	//����һ���ض���ɫ��͸������,����ָ�봫�ݳ����ɵĿ�Ⱥ͸߶�
	static SDL_Texture* createUnicodeLine(const wchar_t* unicode_str, SDL_Color color, int* width, int* height);
	static SDL_Texture* createUnicodeLine(const wchar_t* unicode_str, SDL_Color color, SDL_Color bg_color, int* width, int* height);
	static SDL_Texture* createUnicodeText(const wchar_t* unicode_str, SDL_Color color, int wrapLength, int* w, int* h);
	static SDL_Texture* createUnicodeText(const wchar_t* unicode_str, SDL_Color color, SDL_Color bg_color, int wrapLength, int* w, int* h);

	//���������Ӫ�Ƿ�ս(��ƽ��Ӫ��Զ���ж�,ͬ��ӪҲ���ж�)
	static bool checkIfHostile(AllyType _t1, AllyType _t2);

	//����t�����˵�CD
	static int getWaveTime(int t);

	//�������Ƿ���ĳ���η�Χ��
	static bool checkMouseInRange(int _x1, int _y1, int _x2, int _y2);

	//����double��С��nλ
	static std::wstring double_reserve_decimal(double d, int n);

	//�����������min��max֮��
	static double random(double min, double max);

	//����0��range�������Ȼ��(������range)
	static unsigned random(unsigned range);

	//��ԭ����boolֵ���и��ǲ���
	static bool boolOverride(bool ori,OverrideOperation operation);

	//���ҽ�ɫ����
	static std::list<Chara*> findCharaIn(AllyType ally, int x, int y);
	//��Χ���ҽ�ɫ����
	static  std::list<Chara*> findCharaInArea(AllyType ally, int x, int y, int w, int h);

	//������ʩ����
	static std::list<Facility*> findFacilityIn(FacilityType type, int x, int y);
	//��Χ������ʩ����
	static  std::list<Facility*> findFacilityInArea(FacilityType type, int x, int y, int w, int h);

	//�����赲״̬����
	static bool findBlockingIn(BlockingType blocking, int x, int y);
	//��Χ�����赲״̬����
	static bool findBlockingInArea(BlockingType blocking, int x, int y, int w, int h);

	//��������������ľ���
	static double getDistance(PhysicsObject* p1, PhysicsObject* p2);

};

