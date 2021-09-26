#pragma once
#include <list>
#include "Facility.h"
class Facility;

class FacilitySystem
{
public:
	std::list<Facility*>* facilityList_static;//��̬�������ʩ���б�
	std::list<Facility*>* facilityList_dynamic;//��̬�仯����ʩ���б�
	//��ȡ����ʵ��
	static FacilitySystem* getInstance();
	//���ٵ���ʵ��
	void destroyInstance();
	
	//�Ӿ�̬�б��Ƴ�һ����ʩ
	void removeFacility_static(Facility* facility);
	//�õ������Ƴ�һ����̬��ʩ
	std::list<Facility*>::iterator removeFacility_static(std::list<Facility*>::iterator it);

	//�Ӷ�̬�б��Ƴ�һ����ʩ
	void removeFacility_dynamic(Facility* facility);
	//�õ������Ƴ�һ����̬��ʩ
	std::list<Facility*>::iterator removeFacility_dynamic(std::list<Facility*>::iterator it);
	
	//�㱨�ڴ�ʹ��
	void reportMemory();
private:
	static FacilitySystem* instance;//����ʵ��
	FacilitySystem();
	~FacilitySystem();
};

