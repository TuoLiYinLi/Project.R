#pragma once
#include <list>
#include <iostream>
#include "CountingType.h"

struct countingObject;

class Counting
{
public:
	//����һ�������
	static Counting* createNew();
	//������һ�������
	void destroy();
	//��¼����Щ�������Լ����ǵ�����
	std::list<countingObject> cpList;
	//��ѯһ�ּ����������
	int getNumOf(CountingType ct);
	//����һ�ּ����������
	void addNumOf(CountingType ct, int num);

protected:
	//���б�ɾ��һ�ּ�����
	
	//����һ�ּ�����

	Counting();
	~Counting();
};

struct countingObject
{
	CountingType type;
	int num;
	countingObject(CountingType _type,int _num);
};