#pragma once
#include <iostream>
#include <string>
#include "Chara_old.h"
#include "Form.h"

#include "GeneSystem.h"
class GeneSystem;

//������
class Gene
{
public:
	std::string name;//���������

	Form form;//�������ֵ��

	//����Ĵ�������

	bool triggerOnBasicSkill;//�ڻ�������ʹ��ʱ����
	bool triggerOnSpecialSkill;//����������ʹ��ʱ����
	bool triggerOnMove;//���ƶ�ʱ����
	bool triggerOnBreed;//�ڷ�ֳʱ����
	bool triggerOnDeath;//������ʱ����
	bool triggerOnAttacked;//������ʱ����s
	bool triggerOnKilling;//�ڻ���Ŀ��ʱ����

	//�����Ľ��

	/*
	virtual void onBasicSkill();//������������
	virtual void onSpecialSkill();//������������
	virtual void onMove();//�ƶ�����
	virtual void onBreed();//�ڷ�ֳʱ����
	virtual void onDeath();//������ʱ����
	virtual void onAttacked();//�ڱ�����ʱ����
	virtual void onKill();//�����ܵ���ʱ����
	*/
	//�����µ�Ĭ�ϻ���
	static Gene* createNew();
	
	//����
	virtual void destroy();

	//��ȡ��ǰռ���ڴ�Ļ�������
	static int getCurrentNum();
protected:
	static int currentGeneNum;
	Gene();
	~Gene();
};

