#pragma once
#include <iostream>

#include <vector>
#include "Grid.h"
#include "Chara.h"
#include "Facility.h"
class MapSystem
{
public:
	//��ȡ����ʵ��
	static MapSystem* getInstance();
	//���ٵ���ʵ��
	void destroyInstance();

	std::vector<std::vector<Grid*>*>* map;//���������Grid
	//��ȡ�ض�λ�õ�����
	Grid* getGridAt(int x, int y);
	//��ɫ���ǵ�����
	void occupyGrid(Chara* chara);
	//��ʩ���ǵ�����
	void occupyGrid(Facility* facility);
	//�����ڴ�ʹ�����
	void reportMemory();
	
protected:
	//���캯��
	MapSystem();
	//��������
	~MapSystem();
	//����ʵ��ָ��
	static MapSystem* instance;

};

