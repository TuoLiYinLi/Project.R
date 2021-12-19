#pragma once

constexpr unsigned int WORLD_WIDTH = 128; //����������Ŀ��;
constexpr unsigned int WORLD_HEIGHT = 128; //����������ĸ߶�;

constexpr auto WINDOW_WIDTH = 1600; //���ڵĿ��;
constexpr auto WINDOW_HEIGHT = 900; //���ڵĸ߶�;

constexpr auto FONT_PRECISION = 72;	//�����ȡ����;
constexpr auto FONT_SIZE = 18;	//�����С����;

constexpr auto VIEW_SCALE_MIN = 0.5;	 //���ڵ���С����;
constexpr auto VIEW_SCALE_MAX = 4; //���ڵ��������;

constexpr auto VIEW_SPEED_X_MAX = 10; //���ڵ�ˮƽ��������ٶ�;
constexpr auto VIEW_SPEED_Y_MAX = 10; //���ڵ���ֱ��������ٶ�;
constexpr auto VIEW_SPEED_SCALE_MAX = 2; //��������ʱ������ٶ�;

constexpr auto VIEW_ACCELERATE_SPEED_X = 100; //����ˮƽ�ٶȵļ��ٶ�;
constexpr auto VIEW_ACCELERATE_SPEED_Y = 100; //������ֱ�ٶȵļ��ٶ�;
constexpr auto VIEW_ACCELERATE_SPEED_SCALE = 32; //���������ٶȵļ��ٶ�;

//#define SHOW_FPS //��ÿ��֡�����������
//#define SHOW_KEY //����������������Ϣ���������


//#define WORLD_SYSTEM_DEBUG //�������ϵͳ���

//#define CHARA_SYSTEM_DEBUG //��ɫ����ϵͳ���
//#define CHARA_DEBUG //��ɫ���ɲ��
//#define CHARA_ACTION_DEBUG//��ɫ��Ϊ�ӿڲ��

//#define GENE_SYSTEM_DEBUG //�������ϵͳ���
//#define GENE_DEBUG //�������ɲ��

//#define PROJECTILE_SYSTEM_DEBUG //Ͷ�������ϵͳ���
//#define PROJECTILE_DEBUG //Ͷ�������ɲ��

//#define MAP_SYSTEM_DEBUG //��ͼϵͳ���
//#define GRID_DEBUG //��ͼ�������ɲ��

//#define FACILITY_SYSTEM_DEBUG //��ʩ����ϵͳ���
//#define FACILITY_DEBUG //��ʩ���

//#define ANIMATION_SYSTEM_DEBUG //����ϵͳ���
//#define ANIM_UNIT_DEBUG //������Ԫ���ɲ��
//#define TTF_UNIT_DEBUG //���嵥Ԫ���ɲ��
//#define ANIMATION_RENDER_DEBUG //������Ⱦ���

//#define PARTICLE_SYSTEM_DEBUG //����ϵͳ���

//#define COUNTING_DEBUG//��������





//#define STIFLE_DAMAGE 0.0025 //��Ϣ�˺�����

constexpr auto FALLING_SPEED = 0.08;//׹���ٶ�