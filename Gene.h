#pragma once
//������
class Gene
{
public:
	static Gene* createNew();
	virtual void destroy();	//ͳһ���ٷ�ʽ

	static int getGeneNum();//��ȡ��Ծ��������

	//��ֵ��������

	//�ؼ��ʲ���

	//����Ч������


protected:
	Gene();
	virtual ~Gene();

	static int gene_num;//��Ծ��������
};

