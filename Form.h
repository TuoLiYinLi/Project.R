#pragma once

#include <list>

//��ֵ��
class Form
{
public:
	//��ֵ����
	int healthMax;//�������ֵ
	int health;//����ֵ
	double recovery;//�����ָ���,ÿ֡����
	
	int corruption;//�����̶�,�ﵽ100ʱֱ������
	
	int stamina;//����ֵ
	int staminaMax;//�������ֵ
	double staminaRecover;//�����ָ���,ÿ֡����
	
	//�ж�����ֵ
	int moveTime;//�ƶ������Ĳ���ʱ��
	int moveST;//�ƶ�֮�����ĵ�����
	
	int basicSkillTime;//�������������Ĳ���ʱ��
	int basicSkillST;//ʹ�û����������ĵ�����
	
	int specialSkillTime;//����������������ʱ��
	int specialSkillST;//�����������ĵ�����

	int breedSpeed;//��ֳ������ʱ��
	
	//Ч������
	int breedTime;//��ֳЧ��ʱ��
	int speedupTime;//����ʱ��
	double speedupEffect;//���ٺ���ٵĽ�ɫ����ʱ��ٷֱ�
	int sealedTime;//����ӡ��ʱ��
	int vigorTime;//�����ָ���ʱ��
	double vigorEffect;//�����ڻ���״̬,��ö���Ļ����ָ��ٷֱ�
	int defenceTime;// �񵲵�Ч��ʱ��
	int burnTime;//ȼ��Ч��ʱ��
	double burnEffect;//ÿ֡�ܵ���ȼ���˺�(��ֵ��ʾ�ܵ����˺���ֵ)
	int stunnedTime;//ѣ��Ч��ʱ��
	double beatback;//����Ч����ֵ
	int darkTime;//	�ڰ�Ч��ʱ��
	int poisionedTime;//�ж�Ч��ʱ��
	double poisionedEffect;//�ж�ʱÿ֡�ܵ��İٷֱ��˺�

	//���캯��
	Form();
	//��������
	~Form();
	//���û�����ֵ
	void setBasicPart(
		int _healthMax = 0,
		int _health = 0,
		double _recovery = 0,
		int _staminaMax = 0,
		int _stamina = 0,
		double _staminaRecover = 0,
		int _corruption = 0);
	//�����ж���ֵ
	void setActionPart(
		int _moveTime = 0,
		int _moveST = 0,
		int _basicSkillTime = 0,
		int _basicSkillST = 0,
		int _specialSkillTime = 0,
		int _specialSkillST = 0,
		int _breedSpeed = 0);
	//����Ч����ֵ
	void setEffectPart(
		double _speedupEffect = 0,
		double _vigorEffect = 0,
		double _beatback = 0,
		double _poisionedEffect = 0,
		double _burnEffect = 0,
		int _breedTime = 0,
		int _speedupTime = 0,
		int _sealedTime = 0,
		int _vigorTime = 0,
		int _defenceTime = 0,
		int _burnTime = 0,
		int _stunnedTime = 0,
		int _darkTime = 0,
		int _poisionedTime = 0);
};

