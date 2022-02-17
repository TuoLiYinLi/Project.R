#pragma once
//基因类
class Gene
{
public:
	static Gene* createNew();
	virtual void destroy();	//统一销毁方式

	static int getGeneNum();//获取活跃基因数量

	//数值修正部分

	//关键词部分

	//触发效果部分


protected:
	Gene();
	virtual ~Gene();

	static int gene_num;//活跃基因数量
};

