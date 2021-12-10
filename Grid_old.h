#pragma once
#include "AnimationSystem.h"
#include <list>
#include <iostream>

class Chara_old;
class Facility_old;

class Grid_old
{
public:

	std::list<Chara_old*>* charaList;//��ɫ���б�
	std::list<Facility_old*>* facilityList;//���е���ʩ

	unsigned int x;//����X
	unsigned int y;//����Y

	int dist_to_king_shortest;//���ƶ�����ħ���ľ������
	int dist_to_king_walk;//�����ߵľ�������ħ���ĸ���

	//����new Grid_old
	static Grid_old* createNew(int _x,int _y);
	//�������Grid
	void destroy();


	//��ȡ��ǰδ�ͷŵ�Grid����
	static int getCurrentGridNum();

protected:
	//���캯��
	Grid_old(int _x, int _y);
	//��������
	~Grid_old();
	static int currentGridNum;
};

