#pragma once
#include <iostream>
#include <list>

#include "Chara.h"
class Chara;

class CharaSystem
{
public:
	//获取单例实例
	static CharaSystem* getInstance();
	//销毁单例实例
	void destroyInstance();
	std::list<Chara*>* charaList;//角色的列表,储存了所有的角色
	//移除某个角色
	void removeChara(Chara* chara);
	//移除在index的角色
	void removeChara(int index);
	//用迭代器移除角色并返回新的迭代器
	std::list<Chara*>::iterator removeChara(std::list<Chara*>::iterator it);
	//获取第index个Chara
	Chara* charaAt(int index);
	//报告有多少个Chara仍然在使用中
	void reportMemory();
	//判断角色是否被淹没
	bool ifSubmersed(Chara* chara);
	//判断角色是否坠落
	bool ifFalling(Chara* chara);
private:
	static CharaSystem* instance;//单例实例
	CharaSystem();
	~CharaSystem();
};

