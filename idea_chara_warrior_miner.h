#pragma once
#include "Chara_old.h"
class idea_chara_warrior_miner :
    public Chara_old
{
public:

	static idea_chara_warrior_miner* createNew();

	virtual void destroy();

	//����ʱ(��������)����
	virtual void onDeath();
	//���ϴ���(�κ����ÿ֡)����
	virtual void onAnytime();
	//ʹ�û�������ʱ����
	virtual void onBasicSkill();
	//��ʹ����������ʱ����
	virtual void onSpecialSkill();
	//�ƶ�״̬(����/׹��/�ƶ�)ʱ(ÿ֡)����
	virtual void onMove();
	//����״̬ʱ(ÿ֡)����
	virtual void onIdle();
	//����ײ��(����ײǽ/ǿ���)ʱ����
	virtual void onImpact();
	//ȼ��ʱ(ÿ֡)����
	virtual void onBurning();
	//��Ͷ�������ʱ����
	virtual void onHit(Form* form);
	//��ֳ���ʱ����
	virtual void onBreed();

	//��ȡ��ǰ������Ӧ�Ķ�������
	virtual AnimType getAnimType();
protected:
	int dtk;

	idea_chara_warrior_miner();
	~idea_chara_warrior_miner();
};

