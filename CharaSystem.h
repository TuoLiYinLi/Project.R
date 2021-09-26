#pragma once
#include <iostream>
#include <list>

#include "Chara.h"
class Chara;

class CharaSystem
{
public:
	//��ȡ����ʵ��
	static CharaSystem* getInstance();
	//���ٵ���ʵ��
	void destroyInstance();
	std::list<Chara*>* charaList;//��ɫ���б�,���������еĽ�ɫ
	//�Ƴ�ĳ����ɫ
	void removeChara(Chara* chara);
	//�Ƴ���index�Ľ�ɫ
	void removeChara(int index);
	//�õ������Ƴ���ɫ�������µĵ�����
	std::list<Chara*>::iterator removeChara(std::list<Chara*>::iterator it);
	//��ȡ��index��Chara
	Chara* charaAt(int index);
	//�����ж��ٸ�Chara��Ȼ��ʹ����
	void reportMemory();
	//�жϽ�ɫ�Ƿ���û
	bool ifSubmersed(Chara* chara);
	//�жϽ�ɫ�Ƿ�׹��
	bool ifFalling(Chara* chara);
private:
	static CharaSystem* instance;//����ʵ��
	CharaSystem();
	~CharaSystem();
};

