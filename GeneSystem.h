#pragma once
#include <iostream>
#include "Gene.h"

//�������ϵͳ
class GeneSystem
{
public:
	//��ȡ����ʵ��
	static GeneSystem* getInstance();
	//���������
	void destroyInstance();

	//�㱨�ڴ�ʹ��
	void reportMemory();

private:
	static GeneSystem* instance;//����ʵ��
	GeneSystem();
	~GeneSystem();
};

