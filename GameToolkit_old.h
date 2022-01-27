#pragma once
#include <string>
#include <vector>
#include <codecvt>
#include <windows.h>

#include "AnimationSystem.h"
#include "GeneSystem.h"
#include "CharaSystem.h"
#include "FacilitySystem.h"
#include "MapSystem.h"
#include "ProjectileSystem.h"
#include "ParticleSystem.h"
//#include "GlobalData.h"

#include "FacilityStatic.h"
#include "idea_facility_dirt_wall.h"
#include "idea_facility_dirt_background.h"
#include "idea_facility_dirt_stair_left.h"
#include "idea_facility_dirt_stair_right.h"
#include "idea_facility_dirt_stair_both.h"
#include "idea_facility_water_full.h"
#include "idea_facility_water_upper.h"
#include "idea_facility_ladder_left.h"
#include "idea_facility_ladder_right.h"
#include "idea_facility_dirt_climb_type1_left.h"
#include "idea_facility_dirt_climb_type1_right.h"

#include "idea_facility_rope_head_left.h"
#include "idea_facility_rope_type1_left.h"
#include "idea_facility_rope_type2_left.h"
#include "idea_facility_rope_tail_left.h"

#include "idea_facility_rope_head_right.h"
#include "idea_facility_rope_type1_right.h"
#include "idea_facility_rope_type2_right.h"
#include "idea_facility_rope_tail_right.h"

#include "idea_particle_goldust.h"

struct Vec2;
struct RoomBody;
struct MarginProbe;

namespace gameToolkit {


    //�����������ε��ص����(�Ѳ���)
    double rectCollisionVolume(double x1, double y1, double w1, double h1,
        double x2, double y2, double w2, double h2);

    //�Խ�ɫ��ֵʩ��Ӱ��
    void applyForm(Chara_old* chara, Form* form);
    void applyForm(Form* form_tar,Form* form);

    //����ȫ����ͼ2.0b
    void summonMap_2_0(unsigned int seed);

    //��ɢ����ƽ��������
    double summonMap_curveSmoothAssess(std::list<Vec2>* curve, int i_start, int i_end);

    //��������䷽��ֵ
    int _get2GridDirection(int x1, int y1, int x2, int y2);

    //�����������
    void summonMap_curveFilling( bool** boolMap,std::list<Vec2>* curve, int i_start, int i_end);

    //����ʮ����ȥ
    void summonMap_crossDig(bool** boolMap, std::list<Vec2>* curve, int i_start, int i_end);

    void summonMap_summonRope(bool** boolMap, std::list<Vec2>* path);

    void summonMap_RopeSide(bool** boolMap, int x, int y_down, int y_up, bool atRight);

    void summonMap_summonLadder(bool** boolMap, std::list<Vec2>* path);

    void summonMap_LadderSide(bool** boolMap, int x, int y_down, int y_up, bool atRight);

    void summonMap_Climbing(bool** boolMap, std::list<Vec2>* path);

    //ˢ��ÿ�����ӵ�ħ���ľ���
    void updateDistToKing();

    //ˢ��ÿ�����ӵ�ħ���߶��ľ���
    void updateDistWalkToKing();

    //����һ����ʾ�Ե�����
    void createText(double _x,double _y,const char* msg,SDL_Color color);
    
    //�ж��Ƿ���Ͷ���﹥����Ŀ��
    bool ifTarget(AllyType proj,AllyType tar);
    //�ж�Ŀ�괦���ƶ���Ӱ��

    //�ж�һ�������Ƿ�����ȫ�赲��
    bool ifAbsoluteBlocked(double x, double y);
  
    //�ж�һ�������Ƿ�������֧����
    bool ifWalkable(double x, double y);

    //�ж�һ�������Ƿ���Һ��(��Ȼ������������ʩ)
    bool ifLiquid(double x, double y);

    //�ж�һ�������Ƿ���Һ����û��
    bool ifSubmersed(double x, double y);

    //�ж�һ�������Ƿ�����Ӿ��
    bool ifSwimable(double x, double y);

    //�ж�һ����ɫ�Ƿ���׹��
    bool ifFalling(Chara_old* chara);

    
}


struct Vec2
{
    int x;
    int y;
    Vec2(int _x, int _y);
};

//�������ɵ�ͼ,�����������
struct RoomBody
{
    int x;
    int y;
    int w;
    int h;
    RoomBody(int _x, int _y, int _w, int _h);
};

struct MarginProbe {
    int x;
    int y;
    int direction;
    MarginProbe(int _x,int _y,int _direction);
    //˳ʱ����ת
    void turnClockwise(bool reverse);
    //ǰ��
    void go(bool** boolmap, int* out_X, int* out_Y);
    //ȷ��Ŀ�괦�Ƿ��ǿ�ͨ�е�
    bool checkIfSolid(bool** boolmap);
    //����ǰ������
    Vec2 getFront();

    //���ǰ�������Ƿ񱻰�����������
    bool checkIfCovered(std::list<Vec2>* curve);
};

//ˮ��̽��̽��
struct WaterProbe
{
    //һ��ˮ���������յ�
    int x_start, x_end;
    int y;
    WaterProbe(int _y);
    //��ʼ��Ǻ����ˮ��
    void fillWater(bool** waterMap);
    //����һ��������Ѱ��϶�ռ�
    bool searchPossibalArea(bool** boolMap, int x);
    //����һ�е�ˮ����м��,��ֹ¶����ˮ�ͷⶥ��ˮ
    bool checkUpAndDown(bool** boolMap, bool** waterMap);
};

//�ʸ�Ѱ·̽�� - һ����ʹ�Ľ�ѵ
/*
struct PathProbe {
    bool** tar_boolMap;//Ŀ��Ĳ�����ͼ
    std::list<Vec2>* path;//�����·��
    DirectionType direction;//���ڵķ���
    int dtk;//���¼�¼�ĵ�������
    bool ifGoUp;//�Ƿ�Ҫ����
    bool ifGoLeft;//�Ƿ�����
    int x, y;//��ǰ��λ��
    PathProbe(int x, int y,bool** _boolMap, std::list<Vec2>* _path);
    //�ƶ��Լ���λ��
    void move(DirectionType d);
    //����ǰλ����ӵ�·����
    void savePathPoint();
    //���´�ֱѰ�ҿ��и�ĵ�
    void verticleCut();
    //��ֱ�����е�������·��
    //bool verticleCut();
    //�ظ����õ��Զ�Ѱ·����
    void go();

    void leftGo();

    void rightGo();

    void go_2_0();

    void tellDirection();

    //˳ʱ����ת
    void turnRight();
    //��ʱ����ת
    void turnLeft();
    //
    Vec2 getFront();
};
*/


struct PathProbe_2
{
    bool** tar_boolMap;//Ŀ��Ĳ�����ͼ
    int x, y;//��ǰ��λ��
    PathProbe_2(bool** _boolMap, int _x ,int _y);

    //��������·��
    std::list<Vec2>* solve();

    //��������·��
    std::list<Vec2>* solve_shortest();

    //�������ص�·��
    std::list<Vec2>* solve_low(std::list<Vec2>* ori_path);

    //������ص�·��,�ó����ս��
    std::list<Vec2>* solve_connect(std::list<Vec2>* ori_path);

    //��ĳ�������ƶ�
    void move(DirectionType d);

    //������·���ķ���
    DirectionType getShortestDirection();
};
