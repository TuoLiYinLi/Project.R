#pragma once

enum class AnimationType
{
	default_banned,//Ĭ����ͼ_����
	default_b,//Ĭ����ͼ_��
	default_r,//Ĭ����ͼ_��
	default_g,//Ĭ����ͼ_��

	physics_facility_air,//����ģ��_��ʩ_���赲
	physics_facility_liquid,//����ģ��_��ʩ_Һ���赲
	physics_facility_support,//����ģ��_��ʩ_֧��
	physics_facility_solid,//����ģ��_��ʩ_��ȫ
	physics_chara,//����ģ��_��ɫ
	physics_projectile,//����ģ��_Ͷ����



	charaSlimeIdle,//ʷ��ķ_ͣ��
	charaSlimeMove,//ʷ��ķ_�ƶ�
	charaSlimeBasic,//ʷ��ķ_��ͨ����
	charaSlimeSpecial,//ʷ��ķ_��������
	charaSlimeDeath,//ʷ��ķ_����
	charaWarriorMiner1_idle,//��1_����
	charaWarriorMiner1_walk,//��1_����
	charaWarriorMiner1_dig,//��1_�ھ�
	charaWarriorMiner1_death,//��1_����
	gridDirt_1a,//��������/�赲/����1
	gridDirt_1n,//��������/���赲/����1
	gridDirdCracked,//��������/֧��/���ƻ�
	gridDirtStair_1L,//������������/֧��/��/����1
	gridDirtStair_1R,//������������/֧��/��/����1
	gridDirtStair_1B,//������������/֧��/˫/����1
	gridDirtClimb_L_t1,//������������/֧��/��/����1
	gridDirtClimb_L_t2,//������������/֧��/��/����2
	gridGrass_h4,//�����/h4
	gridDirtButton_1,//��������/���赲/�ײ�/����1
	gridWater_1full,//����ˮ/����
	gridWater_1upper,//����ˮ/δ����
	ladder,//����/Ĭ�������
	ropeHead,//����ͷ��/Ĭ�����Ҳ�
	rope1,//��������1/Ĭ�����Ҳ�
	rope2,//��������2/Ĭ�����Ҳ�
	ropeTail,//����β��/Ĭ�����Ҳ�
	faciSlimeGlue_L1,//ʷ��ķճҺ/1
	chopDown,//Ͷ����/����/��ը��
	slimeBall,//ʷ��ķճҺ��
	particle_goldust,//����_��ɳ/
	size,//ĩβ��������������
};
