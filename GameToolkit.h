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


    //计算两个矩形的重叠面积(已测试)
    double rectCollisionVolume(double x1, double y1, double w1, double h1,
        double x2, double y2, double w2, double h2);

    //对角色数值施加影响
    void applyForm(Chara_old* chara, Form* form);
    void applyForm(Form* form_tar,Form* form);

    //生成全部地图2.0b
    void summonMap_2_0(unsigned int seed);

    //离散曲线平滑度评估
    double summonMap_curveSmoothAssess(std::list<Vec2>* curve, int i_start, int i_end);

    //求两网格间方向值
    int _get2GridDirection(int x1, int y1, int x2, int y2);

    //简易曲线填充
    void summonMap_curveFilling( bool** boolMap,std::list<Vec2>* curve, int i_start, int i_end);

    //简易十字挖去
    void summonMap_crossDig(bool** boolMap, std::list<Vec2>* curve, int i_start, int i_end);

    void summonMap_summonRope(bool** boolMap, std::list<Vec2>* path);

    void summonMap_RopeSide(bool** boolMap, int x, int y_down, int y_up, bool atRight);

    void summonMap_summonLadder(bool** boolMap, std::list<Vec2>* path);

    void summonMap_LadderSide(bool** boolMap, int x, int y_down, int y_up, bool atRight);

    void summonMap_Climbing(bool** boolMap, std::list<Vec2>* path);

    //刷新每个格子到魔王的距离
    void updateDistToKing();

    //刷新每个格子到魔王走动的距离
    void updateDistWalkToKing();

    //产生一个提示性的文字
    void createText(double _x,double _y,const char* msg,SDL_Color color);
    
    //判断是否是投射物攻击的目标
    bool ifTarget(AllyType proj,AllyType tar);
    //判断目标处对移动的影响

    //判断一个区域是否是完全阻挡区
    bool ifAbsoluteBlocked(double x, double y);
  
    //判断一个区域是否是行走支撑区
    bool ifWalkable(double x, double y);

    //判断一个区域是否有液体(仍然可能有其它设施)
    bool ifLiquid(double x, double y);

    //判断一个区域是否是液体淹没区
    bool ifSubmersed(double x, double y);

    //判断一个区域是否是游泳区
    bool ifSwimable(double x, double y);

    //判断一个角色是否是坠落
    bool ifFalling(Chara_old* chara);

    
}


struct Vec2
{
    int x;
    int y;
    Vec2(int _x, int _y);
};

//用于生成地图,房间具体生成
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
    //顺时针旋转
    void turnClockwise(bool reverse);
    //前进
    void go(bool** boolmap, int* out_X, int* out_Y);
    //确认目标处是否是可通行的
    bool checkIfSolid(bool** boolmap);
    //返回前方坐标
    Vec2 getFront();

    //检查前方坐标是否被包含在曲线中
    bool checkIfCovered(std::list<Vec2>* curve);
};

//水体探测探针
struct WaterProbe
{
    //一行水体的起点与终点
    int x_start, x_end;
    int y;
    WaterProbe(int _y);
    //开始标记和填充水体
    void fillWater(bool** waterMap);
    //在这一横条中搜寻空隙空间
    bool searchPossibalArea(bool** boolMap, int x);
    //对这一行的水体进行检查,防止露出的水和封顶的水
    bool checkUpAndDown(bool** boolMap, bool** waterMap);
};

//攀附寻路探针 - 一个惨痛的教训
/*
struct PathProbe {
    bool** tar_boolMap;//目标的布尔地图
    std::list<Vec2>* path;//储存的路径
    DirectionType direction;//现在的方向
    int dtk;//最新记录的到王距离
    bool ifGoUp;//是否要上升
    bool ifGoLeft;//是否向右
    int x, y;//当前的位置
    PathProbe(int x, int y,bool** _boolMap, std::list<Vec2>* _path);
    //移动自己的位置
    void move(DirectionType d);
    //将当前位置添加到路线中
    void savePathPoint();
    //向下垂直寻找可切割的点
    void verticleCut();
    //垂直向下切掉繁复的路径
    //bool verticleCut();
    //重复调用的自动寻路步骤
    void go();

    void leftGo();

    void rightGo();

    void go_2_0();

    void tellDirection();

    //顺时针旋转
    void turnRight();
    //逆时针旋转
    void turnLeft();
    //
    Vec2 getFront();
};
*/


struct PathProbe_2
{
    bool** tar_boolMap;//目标的布尔地图
    int x, y;//当前的位置
    PathProbe_2(bool** _boolMap, int _x ,int _y);

    //计算出结果路径
    std::list<Vec2>* solve();

    //计算出最短路线
    std::list<Vec2>* solve_shortest();

    //计算出落地点路线
    std::list<Vec2>* solve_low(std::list<Vec2>* ori_path);

    //连接落地点路线,得出最终结果
    std::list<Vec2>* solve_connect(std::list<Vec2>* ori_path);

    //向某个方向移动
    void move(DirectionType d);

    //算出最短路径的方向
    DirectionType getShortestDirection();
};
