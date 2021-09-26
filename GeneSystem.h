#pragma once
#include <iostream>
#include "Gene.h"

//基因管理系统
class GeneSystem
{
public:
	//获取单例实例
	static GeneSystem* getInstance();
	//将单例清除
	void destroyInstance();

	//汇报内存使用
	void reportMemory();

private:
	static GeneSystem* instance;//单例实例
	GeneSystem();
	~GeneSystem();
};

