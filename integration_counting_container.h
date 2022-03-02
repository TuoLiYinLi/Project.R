#pragma once
#include <list>
#include <string>

enum class CountingType
{
	food,//ʳ�������
	slime,//ʷ��ķ����������
	corpse,//ʬ�������
	energy,//����������
	corruption,//����������
	gems,//��ʯ������
	fire,//���������
	icy,//��˪������
	growth,//�ɳ�������
};

//���������
//�������������
struct CountingObject
{
	CountingType type;
	int num;
	CountingObject(CountingType _type,int _num);
};

//����������
//�������Ϳ��Ը��ż�������
class integration_counting_container
{
public:
	integration_counting_container();
	//��ѯһ�ּ����������
	int getNumOf(CountingType ct);
	//����һ�ּ����������
	void addNumOf(CountingType ct, int num);

	void removeNumOf(CountingType ct);//�Ƴ�һ�ּ�����

	std::list<CountingType> getAllTypes();

	static std::wstring getName(CountingType type);

protected:

	//��¼����Щ�������Լ����ǵ�����
	std::list<CountingObject> list_counting_type;
};
