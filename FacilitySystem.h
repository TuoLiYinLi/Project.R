#pragma once
#include <list>
#include "Facility_old.h"
class Facility_old;

class FacilitySystem
{
public:
	std::list<Facility_old*>* facilityList_static;//��̬�������ʩ���б�
	std::list<Facility_old*>* facilityList_dynamic;//��̬�仯����ʩ���б�
	//��ȡ����ʵ��
	static FacilitySystem* getInstance();
	//���ٵ���ʵ��
	void destroyInstance();
	
	//�Ӿ�̬�б��Ƴ�һ����ʩ
	void removeFacility_static(Facility_old* facility);
	//�õ������Ƴ�һ����̬��ʩ
	std::list<Facility_old*>::iterator removeFacility_static(std::list<Facility_old*>::iterator it);

	//�Ӷ�̬�б��Ƴ�һ����ʩ
	void removeFacility_dynamic(Facility_old* facility);
	//�õ������Ƴ�һ����̬��ʩ
	std::list<Facility_old*>::iterator removeFacility_dynamic(std::list<Facility_old*>::iterator it);
	
	//�㱨�ڴ�ʹ��
	void reportMemory();
private:
	static FacilitySystem* instance;//����ʵ��
	FacilitySystem();
	~FacilitySystem();
};

