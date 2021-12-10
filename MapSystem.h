#pragma once
#include <iostream>

#include <vector>
#include "Grid_old.h"
#include "Chara_old.h"
#include "Facility_old.h"
class MapSystem
{
public:
	//��ȡ����ʵ��
	static MapSystem* getInstance();
	//���ٵ���ʵ��
	void destroyInstance();

	std::vector<std::vector<Grid_old*>*>* map;//���������Grid
	//��ȡ�ض�λ�õ�����
	Grid_old* getGridAt(double x, double y);
	//��ȡ�ض�λ������ĵ�������
	int getDTK(double x, double y);
	//��ȡ�ض�λ������ĵ�������(�ߺ���)
	int getDWTK(double x, double y);
	//��ɫ���ǵ�����
	void occupyGrid(Chara_old* chara);
	//��ʩ���ǵ�����
	void occupyGrid(Facility_old* facility);
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

