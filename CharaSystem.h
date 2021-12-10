#pragma once
#include <iostream>
#include <list>

#include "Chara_old.h"
class Chara_old;

class CharaSystem
{
public:
	//��ȡ����ʵ��
	static CharaSystem* getInstance();
	//���ٵ���ʵ��
	void destroyInstance();
	std::list<Chara_old*>* charaList;//��ɫ���б�,���������еĽ�ɫ
	//�Ƴ�ĳ����ɫ
	void removeChara(Chara_old* chara);
	//�Ƴ���index�Ľ�ɫ
	void removeChara(int index);
	//�õ������Ƴ���ɫ�������µĵ�����
	std::list<Chara_old*>::iterator removeChara(std::list<Chara_old*>::iterator it);
	//��ȡ��index��Chara
	Chara_old* charaAt(int index);
	//�����ж��ٸ�Chara��Ȼ��ʹ����
	void reportMemory();
	//�жϽ�ɫ�Ƿ���û
	bool ifSubmersed(Chara_old* chara);
	//�жϽ�ɫ�Ƿ�׹��
	bool ifFalling(Chara_old* chara);
private:
	static CharaSystem* instance;//����ʵ��
	CharaSystem();
	~CharaSystem();
};

