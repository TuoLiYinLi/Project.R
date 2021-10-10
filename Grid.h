#pragma once
#include "AnimSystem.h"
#include <list>
#include <iostream>

class Chara;
class Facility;

class Grid
{
public:

	std::list<Chara*>* charaList;//��ɫ���б�
	std::list<Facility*>* facilityList;//���е���ʩ

	unsigned int x;//����X
	unsigned int y;//����Y

	int distToKing;//���ƶ�����ħ���ľ������
	int distToKing_walk;//�����ߵľ�������ħ���ĸ���

	//����new Grid
	static Grid* createNew(int _x,int _y);
	//�������Grid
	void destroy();


	//��ȡ��ǰδ�ͷŵ�Grid����
	static int getCurrentGridNum();

protected:
	//���캯��
	Grid(int _x, int _y);
	//��������
	~Grid();
	static int currentGridNum;
};

