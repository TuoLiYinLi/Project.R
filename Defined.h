#pragma once

constexpr unsigned int WORLD_WIDTH = 128; //单个的世界的宽度;
constexpr unsigned int WORLD_HEIGHT = 128; //单个的世界的高度;

constexpr auto WINDOW_WIDTH = 1600; //窗口的宽度;
constexpr auto WINDOW_HEIGHT = 900; //窗口的高度;

constexpr auto FONT_PRECISION = 72;	//字体读取精度;
constexpr auto FONT_SIZE = 18;	//字体大小比例;

constexpr auto VIEW_SCALE_MIN = 0.5;	 //窗口的最小缩放;
constexpr auto VIEW_SCALE_MAX = 4; //窗口的最大缩放;

constexpr auto VIEW_SPEED_X_MAX = 10; //窗口的水平方向最大速度;
constexpr auto VIEW_SPEED_Y_MAX = 10; //窗口的竖直方向最大速度;
constexpr auto VIEW_SPEED_SCALE_MAX = 2; //窗口缩放时的最大速度;

constexpr auto VIEW_ACCELERATE_SPEED_X = 100; //窗口水平速度的减速度;
constexpr auto VIEW_ACCELERATE_SPEED_Y = 100; //窗口竖直速度的减速度;
constexpr auto VIEW_ACCELERATE_SPEED_SCALE = 32; //窗口缩放速度的减速度;

//#define SHOW_FPS //将每秒帧数输出到窗口
//#define SHOW_KEY //将键盘鼠标等输入信息输出到窗口


//#define WORLD_SYSTEM_DEBUG //世界管理系统查错

//#define CHARA_SYSTEM_DEBUG //角色管理系统查错
//#define CHARA_DEBUG //角色生成查错
//#define CHARA_ACTION_DEBUG//角色行为接口查错

//#define GENE_SYSTEM_DEBUG //基因管理系统查错
//#define GENE_DEBUG //基因生成查错

//#define PROJECTILE_SYSTEM_DEBUG //投射物管理系统查错
//#define PROJECTILE_DEBUG //投射物生成查错

//#define MAP_SYSTEM_DEBUG //地图系统查错
//#define GRID_DEBUG //地图网格生成查错

//#define FACILITY_SYSTEM_DEBUG //设施管理系统查错
//#define FACILITY_DEBUG //设施查错

//#define ANIMATION_SYSTEM_DEBUG //动画系统查错
//#define ANIM_UNIT_DEBUG //动画单元生成查错
//#define TTF_UNIT_DEBUG //字体单元生成查错
//#define ANIMATION_RENDER_DEBUG //动画渲染查错

//#define PARTICLE_SYSTEM_DEBUG //粒子系统查错

//#define COUNTING_DEBUG//计数物查错





//#define STIFLE_DAMAGE 0.0025 //窒息伤害常量

constexpr auto FALLING_SPEED = 0.08;//坠落速度