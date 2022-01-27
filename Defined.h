#pragma once

constexpr int WORLD_WIDTH = 128; //����������Ŀ��;
constexpr int WORLD_HEIGHT = 128; //����������ĸ߶�;

constexpr float DEPTH_PRECISION = 0.0001f;//������Ԫ����ȵľ�ȷ��

constexpr int WINDOW_WIDTH = 1600; //���ڵĿ��;
constexpr int WINDOW_HEIGHT = 900; //���ڵĸ߶�;

constexpr int FONT_PRECISION = 24;	//�����ȡ����;
constexpr int FONT_SIZE = 24;	//�����С����;

constexpr double PIXEL_RATE = 32;//��Ⱦ�����س����������е�Ԫ�񳤶ȵı���

constexpr double VIEW_SCALE_MIN = 0.5;	 //���ڵ���С����;
constexpr double VIEW_SCALE_MAX = 4; //���ڵ��������;

constexpr double VIEW_SPEED_X_MAX = 10; //���ڵ�ˮƽ��������ٶ�;
constexpr double VIEW_SPEED_Y_MAX = 10; //���ڵ���ֱ��������ٶ�;
constexpr double VIEW_SPEED_SCALE_MAX = 2; //��������ʱ������ٶ�;

constexpr double VIEW_ACCELERATE_SPEED_X = 100; //����ˮƽ�ٶȵļ��ٶ�;
constexpr double VIEW_ACCELERATE_SPEED_Y = 100; //������ֱ�ٶȵļ��ٶ�;
constexpr double VIEW_ACCELERATE_SPEED_SCALE = 8; //���������ٶȵļ��ٶ�;

constexpr float RENDERING_DEPTH_WORLD_FACILITY = 1000;//��Ⱦ�����ʩ
constexpr float RENDERING_DEPTH_WORLD_CHARA = 2000;//��Ⱦ��Ƚ�ɫ
constexpr float RENDERING_DEPTH_WORLD_PARTICLE = 3000;//��Ⱦ�������

constexpr float RENDERING_DEPTH_WORLD_UI = 5000;//��Ⱦ�������UI
constexpr float RENDERING_DEPTH_UI = 6000;//��Ⱦ��ȹ̶�UI
constexpr float RENDERING_DEPTH_EXTRA = 10000;//������Ϣ


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

constexpr double LOW_SPEED = 1.0/60;//����
constexpr double FALLING_SPEED = 5.0/60;//׹���ٶ�
constexpr double HIGH_SPEED = 6.0/60;//����,һ�㲻�ɳ�������ٶ�
constexpr double MAX_SPEED = 1;//����ٶ�

constexpr int OXYGEN_MAX = 600;//�������ֵ
constexpr double OXYGEN_DAMAGE = 0.2 / 60;//������ɵ��˺�
constexpr double BURNING_SPEED = 1.0 / 60;//ȼ���ٶ�
constexpr double POISONED_SPEED = 1.0 / 600;//�ж��ٶ�