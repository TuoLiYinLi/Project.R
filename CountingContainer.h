#pragma once
#include <list>
#include <string>

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
	void destroy()const;
	//��ѯһ�ּ����������
	int getNumOf(CountingType ct);
	//����һ�ּ����������
	void addNumOf(CountingType ct, int num);

	void removeNumOf(CountingType ct);//�Ƴ�һ�ּ�����

	std::list<CountingType> getAllTypes();

	static std::wstring get_name(CountingType type);

protected:
	CountingContainer();
	~CountingContainer();

	//��¼����Щ�������Լ����ǵ�����
	std::list<CountingObject> list_counting_type;
};
