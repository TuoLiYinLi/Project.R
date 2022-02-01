#pragma once
#include <list>

enum class CountingType
{
	food,//ʳ�������
	slimeGlue,//ʷ��ķ����������
	corpse,//ʬ�������
	energy,//����������
	corruption,//����������
	gems,//��ʯ������
	fire,//���������
	icy,//��˪������
};

struct CountingObject
{
	CountingType type;
	int num;
	CountingObject(CountingType _type,int _num);
};

class CountingContainer
{
public:
	//����һ�������
	static CountingContainer* createNew();
	//������һ�������
	void destroy();
	//��¼����Щ�������Լ����ǵ�����
	std::list<CountingObject> cpList;
	//��ѯһ�ּ����������
	int getNumOf(CountingType ct);
	//����һ�ּ����������
	void addNumOf(CountingType ct, int num);

protected:
	//���б�ɾ��һ�ּ�����
	
	//����һ�ּ�����

	CountingContainer();
	~CountingContainer();
};
