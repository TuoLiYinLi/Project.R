#pragma once

constexpr int WORLD_WIDTH = 128; //单个的世界的宽度;
constexpr int WORLD_HEIGHT = 128; //单个的世界的高度;

constexpr float DEPTH_PRECISION = 0.0001f;//动画单元的深度的精确度

constexpr int WINDOW_WIDTH = 1600; //窗口的宽度;
constexpr int WINDOW_HEIGHT = 900; //窗口的高度;

constexpr int FONT_PRECISION = 19;	//字体读取精度;

constexpr double PIXEL_RATE = 32;//渲染中像素长度与物理中单元格长度的比例

constexpr double VIEW_SCALE_MIN = 0.5;	 //窗口的最小缩放;
constexpr double VIEW_SCALE_MAX = 4; //窗口的最大缩放;

constexpr double VIEW_SPEED_X_MAX = 10; //窗口的水平方向最大速度;
constexpr double VIEW_SPEED_Y_MAX = 10; //窗口的竖直方向最大速度;
constexpr double VIEW_SPEED_SCALE_MAX = 2; //窗口缩放时的最大速度;

constexpr double VIEW_ACCELERATE_SPEED_X = 100; //窗口水平速度的减速度;
constexpr double VIEW_ACCELERATE_SPEED_Y = 100; //窗口竖直速度的减速度;
constexpr double VIEW_ACCELERATE_SPEED_SCALE = 8; //窗口缩放速度的减速度;

constexpr float DEPTH_WORLD_FACILITY = 1000;//渲染深度设施
constexpr float DEPTH_WORLD_CHARA = 2000;//渲染深度角色
constexpr float DEPTH_WORLD_PROJECTILE = 3000;//渲染深度投射物

constexpr float DEPTH_WORLD_UI = 5000;//渲染深度世界UI
constexpr float DEPTH_FIXED_UI = 6000;//渲染深度固定UI
constexpr float DEPTH_EXTRA = 10000;//额外信息

constexpr double GOLDUST_RECOVERY = 0.01;//默认的金沙能量恢复速度

constexpr double UI_SCALE = 4;//UI放大倍数

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

constexpr double low_speed = 1.0/60;//低速
constexpr double falling_speed = 5.0/60;//坠落速度
constexpr double high_speed = 6.0/60;//高速,一般不可超过这个速度
constexpr double max_speed = 1;//最大速度

constexpr int oxygen_max = 600;//氧气最大值
constexpr double oxygen_damage = 0.2 / 60;//氧气造成的伤害
constexpr double burning_speed = 1.0 / 60;//燃烧速度
constexpr double poisoned_speed = 1.0 / 600;//中毒速度


constexpr auto wchar_multiply = static_cast<wchar_t>(215);

constexpr auto damaged_highlight_length = 10;//受到攻击时高亮时间