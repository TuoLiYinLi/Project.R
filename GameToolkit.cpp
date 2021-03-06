#include "GameToolkit.h"
#include "Defined.h"

/*
std::string gameToolkit::UnicodeToUTF8(const std::wstring& wstr)
{
    std::string ret;
    try {
        std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
        ret = wcv.to_bytes(wstr);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return ret;
}

std::wstring gameToolkit::UTF8ToUnicode(const std::string& str)
{
    std::wstring ret;
    try {
        std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
        ret = wcv.from_bytes(str);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return ret;
}

std::string gameToolkit::UnicodeToANSI(const std::wstring& wstr)
{
    std::string ret;
    std::mbstate_t state = {};
    const wchar_t* src = wstr.data();
    size_t len = std::wcsrtombs(nullptr, &src, 0, &state);
    if (static_cast<size_t>(-1) != len) {
        std::unique_ptr< char[] > buff(new char[len + 1]);
        len = std::wcsrtombs(buff.get(), &src, len, &state);
        if (static_cast<size_t>(-1) != len) {
            ret.assign(buff.get(), len);
        }
    }
    return ret;
}

std::wstring gameToolkit::ANSIToUnicode(const std::string& str)
{
    std::wstring ret;
    std::mbstate_t state = {};
    const char* src = str.data();
    size_t len = std::mbsrtowcs(nullptr, &src, 0, &state);
    if (static_cast<size_t>(-1) != len) {
        std::unique_ptr< wchar_t[] > buff(new wchar_t[len + 1]);
        len = std::mbsrtowcs(buff.get(), &src, len, &state);
        if (static_cast<size_t>(-1) != len) {
            ret.assign(buff.get(), len);
        }
    }
    return ret;
}

int gameToolkit::multibyteToUnicode(const char* multiByteStr, int multiByteStrLen, UINT multiByteCharsetFlag, char* unicodeStr, int unicodeStrLen)
{
    if (multiByteStr == NULL)//原始字符串为空
    {
        return -1;
    }

    if (multiByteStrLen <= 0)//原始字符串长度小于等于0
    {
        return -2;
    }

    if (multiByteCharsetFlag != CP_ACP && multiByteCharsetFlag != CP_UTF8)//原始字符串字符集标识既不是GBK/GB2312又不是UTF-8
    {
        return -3;
    }

    if (unicodeStr == NULL)//用于存放unicode串的缓存区为空
    {
        return -4;
    }

    if (unicodeStrLen <= 0)//用于存放unicode串的缓存区的长度小于等于0
    {
        return -5;
    }

    int requiredUnicode = MultiByteToWideChar(multiByteCharsetFlag, 0, multiByteStr, multiByteStrLen, NULL, 0);//此种情况用来获取转换所需的wchar_t的个数

    if (sizeof(WCHAR) * requiredUnicode > unicodeStrLen)//接收被转换字符串的缓冲区小于实际需要的字节数
    {
        return -6;
    }

    WCHAR* tmp = new WCHAR[requiredUnicode];//动态分配unicode临时缓存区

    wmemset(tmp, 0, requiredUnicode);//将临时缓存区数据清零

    //执行真实转换，并将转换后的unicode串写到tmp缓存区
    int parsedUnicode = MultiByteToWideChar(multiByteCharsetFlag, 0, multiByteStr, multiByteStrLen, tmp, requiredUnicode);

    if (parsedUnicode != requiredUnicode)//判断真实解析的unicode字符数和分配的字符数是否一致
    {
        delete[]tmp;
        tmp = NULL;
        return -7;
    }

    memset(unicodeStr, 0, unicodeStrLen);//将目标unicode缓存区清零
    memcpy(unicodeStr, tmp, sizeof(WCHAR) * requiredUnicode);//将数据由临时缓存区拷贝到目标unicode缓存区

    delete[] tmp;//释放空间
    tmp = NULL;

    return sizeof(WCHAR) * requiredUnicode;//返回解析好的总字节数
}
*/

double gameToolkit::rectCollisionVolume(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2)
{
    double d_x;
    double d_y;
    if (x1 < x2) {
        d_x = x1 + w1 - x2;
        if (d_x > w2) {
            d_x = w2;
        }
        else if(d_x<0)
        {
            d_x = 0;
        }
    }
    else {
        d_x = x2 + w2 - x1;
        if (d_x<0) {
            d_x = 0;
        }
        else if(d_x>w1)
        {
            d_x = w1;
        }
    }

    if (y1 < y2) {
        d_y = y1 + h1 - y2;
        if (d_y>h2) {
            d_y = h2;
        }
        else if (d_y<0)
        {
            d_y = 0;
        }
    }
    else
    {
        d_y = y2 + h2 - y1;
        if (d_y > h1) {
            d_y = h1;
        }
        else if(d_y<0)
        {
            d_y = 0;
        }
    }
    double s = d_x * d_y;
    std::cout << "\t\tgameToolkit::rectCollisionVolume "<< s <<"\n";
    return s;
}

void gameToolkit::applyForm(Chara* chara, Form* form)
{
    applyForm(&(chara->form), form);
	createText(chara->x, chara->y, std::to_string(form->health).c_str(), { 255,0,0,255 });
}

void gameToolkit::applyForm(Form* form_tar, Form* form)
{
    //std::cout <<"health" << form_tar->health << "\n";

    form_tar->healthMax += form->healthMax;
    form_tar->health += form->health;
    form_tar->recovery += form->recovery;
    form_tar->corruption += form->corruption;
    form_tar->stamina += form->stamina;
    form_tar->staminaMax += form->staminaMax;
    form_tar->staminaRecover += form->staminaRecover;
    
    form_tar->moveTime += form->moveTime;
    form_tar->moveST += form->moveST;
    form_tar->basicSkillTime += form->basicSkillTime;
    form_tar->basicSkillST += form->basicSkillTime;
    form_tar->specialSkillTime += form->specialSkillTime;
    form_tar->specialSkillST += form->specialSkillST;
    form_tar->breedSpeed += form->breedSpeed;
    
    form_tar->breedTime += form->breedTime;
    form_tar->speedupTime += form->speedupTime;
    form_tar->speedupEffect += form->speedupEffect;
    form_tar->beatback += form->beatback;
    form_tar->sealedTime += form->sealedTime;
    form_tar->vigorEffect += form->vigorEffect;
    form_tar->vigorTime += form->vigorTime;
    form_tar->darkTime += form->darkTime;
    form_tar->burnEffect += form->burnEffect;
    form_tar->burnTime += form->burnTime;
    form_tar->poisionedEffect += form->poisionedEffect;
    form_tar->poisionedTime += form->poisionedTime;
    form_tar->defenceTime += form->defenceTime;
    form_tar->stunnedTime += form->stunnedTime;
}

void gameToolkit::summonMap_2_0(unsigned int seed)
{
	//设置随机数
	srand(seed);
	//P1-生成房间位置(大区块)
	std::vector<Vec2>* roomPois;//房间坐标列表
	{
		//房间坐标列表初始化
		roomPois = new std::vector<Vec2>();
		//生成基础路径
		{
			//生成入口房间,范围在2~5
			int inX = (rand() % 6) + 2;
			Vec2 inV = Vec2(inX, 0);
			roomPois->push_back(inV);
			//生成终点口房间位置,范围在2~5
			int finalX = (rand() % 6) + 2;
			//生成拐点位置,范围1~7
			int tp0 = (rand() % 7 + 1);
			//生成的过程
			for (int i = 1; i < tp0; i++) {
				inV = Vec2(inX, i);
				roomPois->push_back(inV);
			}
			for (int i = inX; i < finalX; i++)
			{
				inV = Vec2(i, tp0);
				roomPois->push_back(inV);
			}
			for (int i = inX; i > finalX; i--)
			{
				inV = Vec2(i, tp0);
				roomPois->push_back(inV);
			}
			for (int i = tp0; i <= 7; i++)
			{
				inV = Vec2(finalX, i);
				roomPois->push_back(inV);
			}
		}
		//扭曲基础路径
		{
			//设置扭曲次数
			int twistCount = 0;
			while (twistCount < 12)
			{
				//随机生成扭曲起点
				int r = (rand() % (roomPois->size() - 1)) + 1;
				//随机生成扭曲的方向
				int d = rand() % 2;
				//取得两个房间位置坐标
				Vec2 V1 = roomPois->at(static_cast<__int64>(r) - 1);
				Vec2 V2 = roomPois->at(r);
				//开始扭曲
				if (V1.x == V2.x) {
					//垂直方向
					if (d > 0)
					{
						//左侧
						bool j = true;
						for (auto i = 0; i < roomPois->size(); i++) {
							Vec2 m3 = roomPois->at(i);
							if (V1.x == 0 || m3.x == V1.x - 1 && (m3.y == V1.y || m3.y == V2.y))
							{
								j = false;
								break;
							}
						}
						if (j)
						{
							roomPois->insert(roomPois->begin() + r, Vec2(V1.x - 1, V1.y));
							roomPois->insert(roomPois->begin() + r + 1, Vec2(V2.x - 1, V2.y));
							twistCount++;
						}
					}
					else
					{
						//右侧
						bool j = true;
						for (auto i = 0; i < roomPois->size(); i++) {
							Vec2 m3 = roomPois->at(i);
							if (V1.x == 7 || m3.x == V1.x + 1 && (m3.y == V1.y || m3.y == V2.y))
							{
								j = false;
								break;
							}
						}
						if (j)
						{
							roomPois->insert(roomPois->begin() + r, Vec2(V1.x + 1, V1.y));
							roomPois->insert(roomPois->begin() + r + 1, Vec2(V2.x + 1, V2.y));
							twistCount++;
						}
					}
				}
				else
				{
					if (d > 0)
					{
						//上方
						bool j = true;
						for (auto i = 0; i < roomPois->size(); i++) {
							Vec2 m3 = roomPois->at(i);
							if (V1.y == 0 || m3.y == V1.y - 1 && (m3.x == V1.x || m3.x == V2.x))
							{
								j = false;
								break;
							}
						}
						if (j)
						{
							roomPois->insert(roomPois->begin() + r, Vec2(V1.x, V1.y - 1));
							roomPois->insert(roomPois->begin() + r + 1, Vec2(V2.x, V2.y - 1));
							twistCount++;
						}
					}
					else
					{
						//下方
						bool j = true;
						for (auto i = 0; i < roomPois->size(); i++) {
							Vec2 m3 = roomPois->at(i);
							if (V1.y == 7 || m3.y == V1.y + 1 && (m3.x == V1.x || m3.x == V2.x))
							{
								j = false;
								break;
							}
						}
						if (j)
						{
							roomPois->insert(roomPois->begin() + r, Vec2(V1.x, V1.y + 1));
							roomPois->insert(roomPois->begin() + r + 1, Vec2(V2.x, V2.y + 1));
							twistCount++;
						}
					}
				}
			}
		}
		//将整个房间居中放置
		{
			int x_min = 7;
			int x_max = 0;
			for (int i = 0; i <= roomPois->size() - 1; i++)
			{
				auto v = roomPois->at(i);
				if (v.x < x_min) x_min = v.x;
				if (v.x > x_max) x_max = v.x;
			}
			int map_width = x_max - x_min;
			int delta_x = (4 - floor(double(map_width) / 2)) - x_min;

			for (int i = 0; i <= roomPois->size() - 1; i++)
			{
				roomPois->at(i).x += delta_x;
			}
		}
	}
	//P2-生成房间列表
	std::cout << "gameToolkit::summonMap_2_0:P2-生成房间列表\n";
	std::vector<RoomBody>* roomBodyList;//房间列表
	{
		//房间列表初始化
		roomBodyList = new std::vector<RoomBody>();
		//开始生成
		for (int i = 0; i < roomPois->size(); i++)
		{
			Vec2 rm = roomPois->at(i);
			//生成偏移量dx,dy,w,h
			int w = (rand() % (8 + 1)) + 4;
			int h = (rand() % (8 + 1)) + 4;
			int dx = (rand() % 8)+1;
			int dy = (rand() % 8)+1;
			
			while (w + dx >= 15) {
				dx --;
			}

			while (h + dy >= 15) {
				dy --;
			}

			//生成房间,注意不要超出地图范围
			RoomBody rb = RoomBody(rm.x * 16 + dx, rm.y * 16 + dy, w, h);
			
			while (rb.x + rb.w >= WORLD_WIDTH-1) {
				rb.x--;
				if (rb.w > 4) {
					rb.w--;
				}
			}
			if (rb.y  <= 2) {
				rb.y += 2;
				rb.h -= 2;
			}

			if (rb.y + rb.h >= WORLD_HEIGHT - 3) {
				rb.h -= 2;
			}
			//加入列表
			roomBodyList->push_back(rb);
		}
		
		//调整第一个房间(入口),与最上方相接
		RoomBody* rb = &(roomBodyList->at(0));
		rb->h += rb->y;
		rb->y = 0;

		//调整最后一个房间(出口),与最下方相接
		rb = &(roomBodyList->at(roomBodyList->size()-1));
		rb->h = WORLD_HEIGHT - rb->y - 1 - 1;
		if (rb->w<8) {
			rb->x = (2 * rb->x + rb->w) / 2 - 4;
			rb->w = 8;
		}

		
		//将房间居中放置
		{
			int x_max = 0;
			int x_min = WORLD_WIDTH - 1;
			for (auto it = roomBodyList->begin(); it != roomBodyList->end(); it++)
			{
				if ((*it).x < x_min)x_min = (*it).x;
				if ((*it).x > x_max)x_max = (*it).x;
			}
			double rooms_width = static_cast<__int64>(x_max) - x_min;
			int rooms_dtx = double(WORLD_WIDTH) / 2 - rooms_width / 2 - x_min;

			for (auto it = roomBodyList->begin(); it != roomBodyList->end(); it++)
			{
				(*it).x += rooms_dtx;
			}
		}
		
		//设置王的位置
		RoomBody* kingRoom = &(roomBodyList->at(roomBodyList->size() - 1));
		GlobalData::KingX = kingRoom->x + kingRoom->w / 2;
		GlobalData::KingY = WORLD_HEIGHT - 2;

	}
	
	//P3-生成bool图和通道
	bool** boolMap_1 = new bool* [WORLD_WIDTH];//bool图
	{
		//bool图内存初始化
		for (size_t i = 0; i < WORLD_WIDTH; i++)
		{
			boolMap_1[i] = new bool[WORLD_HEIGHT];
		}
		//赋值初始化
		for (int i = 0; i < WORLD_WIDTH; i++)
		{
			for (int j = 0; j < WORLD_HEIGHT; j++)
			{
				boolMap_1[i][j] = true;
			}
		}
		//填充房间区域
		for (int i = 0; i < roomBodyList->size(); i++)
		{
			RoomBody* rb = &(roomBodyList->at(i));
			for (int t_x = rb->x; t_x <= rb->x + rb->w; t_x++)
			{
				for (int t_y = rb->y; t_y <= rb->y + rb->h; t_y++)
				{
					boolMap_1[t_x][t_y] = false;
				}
			}
		}
		//在bool图创建通道
		for (int i = 0; i < roomBodyList->size() - 1; i++)
		{
			//取得相邻房间的位置关系和形状数据
			Vec2 v1 = roomPois->at(i);
			Vec2 v2 = roomPois->at(static_cast<__int64>(i) + 1);
			RoomBody* rb1 = &(roomBodyList->at(i));
			RoomBody* rb2 = &(roomBodyList->at(static_cast<__int64>(i) + 1));
			int dt1x = 0; int dt1y = 0;//前一个房间的通道起点
			int dt2x = 0; int dt2y = 0;//后一个房间的通道起点

			//随机生成通道的起点与终点
			{
				if (v1.x > v2.x) {
					//向左

					dt1x = rb1->x - 1;
					dt1y = rb1->y + (rand() % (rb1->h - 1));
					dt2x = rb2->x + rb2->w;
					dt2y = rb2->y + (rand() % (rb2->h - 1));
					//防止通道过于接近边界
					if (dt2y>WORLD_HEIGHT-4) {
						dt2y = WORLD_HEIGHT - 4;
					}
					if (dt1y < 4) {
						dt1y = 4;
					}
				}
				else if (v1.x < v2.x)
				{
					//向右

					dt1x = rb1->x + rb1->w;
					dt1y = rb1->y + (rand() % (rb1->h - 1));
					dt2x = rb2->x - 1;
					dt2y = rb2->y + (rand() % (rb2->h - 1));

					//防止通道过于接近边界
					if (dt2y > WORLD_HEIGHT - 4) {
						dt2y = WORLD_HEIGHT - 4;
					}
				}
				else if (v1.y > v2.y)
				{
					//向上
					dt1x = rb1->x + (rand() % (rb1->w));
					dt1y = rb1->y;
					dt2x = rb2->x + (rand() % (rb2->w));
					dt2y = rb2->y + rb2->h;
				}
				else if (v1.y < v2.y)
				{
					//向下
					dt1x = rb1->x + (rand() % (rb1->w));
					dt1y = rb1->y + rb1->h;
					dt2x = rb2->x + (rand() % (rb2->w));
					dt2y = rb2->y;
				}
			}
			//找到目标区域开始生成通道
			int x_start = 0;
			int x_end = 0;
			int y_start = 0;
			int y_end = 0;
			{
				if (dt1x < dt2x) {
					x_start = dt1x;
					x_end = dt2x;
				}
				else
				{
					x_start = dt2x;
					x_end = dt1x;
				}
				if (dt1y < dt2y) {
					y_start = dt1y;
					y_end = dt2y;
				}
				else
				{
					y_start = dt2y;
					y_end = dt1y;
				}
			}
			//T的直线公式 :)
			float A = dt2y - dt1y;
			float B = dt1x - dt2x;
			float C = -A * dt1x - B * dt1y;
			//生成通道随机宽度
			int r = (rand() % (3)) + 1;
			if (r == 3) {
				r = 1;
			}
			//在bool图生成通道
			for (int i = x_start; i <= x_end; i++)
			{
				for (int j = y_start; j <= y_end; j++)
				{
					if (abs(A * i + B * j + C) / sqrt(A * A + B * B) <= r) {
						//用2*2方形填充通道,注意小小超出边界
						if (i < WORLD_WIDTH && j < WORLD_HEIGHT && i >= 0 && j >= 0)
						boolMap_1[i][j] = false;
						if (i + 1 < WORLD_WIDTH && j < WORLD_HEIGHT && i + 1 >= 0 && j >= 0)
						boolMap_1[i + 1][j] = false;
						if (i < WORLD_WIDTH && j + 1 < WORLD_HEIGHT && i >= 0 && j + 1 >= 0)
						boolMap_1[i][j + 1] = false;
						if (i + 1 < WORLD_WIDTH && j + 1 < WORLD_HEIGHT && i + 1 >= 0 && j + 1 >= 0)
						boolMap_1[i + 1][j + 1] = false;
					}
				}
			}
		}
	}
	//清除P1 P2数据
	delete roomPois;
	delete roomBodyList;
	
	//P4-扫描边缘并平滑
	std::cout << "gameToolkit::summonMap_2_0:P4-扫描边缘并平滑\n";
	std::list<Vec2>* marginList;//边缘列表
	{
		//申请内存
		marginList = new std::list<Vec2>();
		
		//从第一排寻找第边缘曲线起点
		int current_x = 0;
		while (true)
		{
			if (!boolMap_1[current_x][0]) {
				break;
			}
			else
			{
				current_x++;
			}
			if (current_x >= WORLD_WIDTH) {
				std::cout << "ERROR:summon map failure no available grid for y=0\n";
				return;
			}
		}
		marginList->push_back(Vec2(current_x, 0));
		
		//设置边缘探针
		MarginProbe mp = MarginProbe(current_x, 0, 6);
		
		//开始探测和生成边缘
		int marginLength = 1;
		while (true)
		{
			//std::cout << "gameToolkit::summonMap_2_0_a:P4 探针位置:" << mp.x << "," << mp.y << "\n";
			int out_x = 0; int out_y = 0;
			//探针返回坐标值
			mp.go(boolMap_1, &out_x, &out_y);
			if (out_x == current_x && out_y == 0) {
				//std::cout <<"gameToolkit::summonMap_2_0_a:P4 边缘总长度:"<<marginLength<< "\n";
				break;
			}
			else
			{
				marginList->push_back(Vec2(out_x, out_y));
				marginLength++;
			}
		}
		//扫描完成:) 开始平滑化

		//测试输出每个点的平滑度
		int index = 0;
		int range = 3;
		for (auto it = marginList->begin(); it != marginList->end(); it++)
		{
			if ((*it).x == 0 || (*it).x == WORLD_WIDTH - 1 || (*it).y == 0 || (*it).y == WORLD_HEIGHT - 1) {
				continue;
			}

			int dx = (it->x - GlobalData::KingX);
			int dy = (it->y - GlobalData::KingY);
			int dist = dx * dx + dy * dy;
			double smoothness;
			if (dist >= 64)
				smoothness = summonMap_curveSmoothAssess(marginList, index - range - 1, index + range);
			else
				smoothness = 0;

			//std::cout << "gameToolkit::summonMap_2_0:平滑度" << (*it).x << "," << (*it).y << " " << smoothness << "\n";
			
			//进行平滑
			if (smoothness < 3 && smoothness>1.5) {
				summonMap_curveFilling(boolMap_1, marginList, index - 1, index + 1);
			}
			if (smoothness < -4) {
				summonMap_crossDig(boolMap_1, marginList, index - 1, index + 1);
			}
			
			index++;
		}

		//简易修补地图空隙
		for (int i = 1; i < WORLD_WIDTH - 1; i++)
		{
			for (int j = 1; j < WORLD_HEIGHT-1; j++)
			{
				if (boolMap_1[i+1][j] == true&& boolMap_1[i-1][j] == true &&
					boolMap_1[i][j+1] == true && boolMap_1[i][j-1] == true)
					boolMap_1[i][j] = true;
				if (boolMap_1[i + 1][j] == false && boolMap_1[i - 1][j] == false &&
					boolMap_1[i][j + 1] == false && boolMap_1[i][j - 1] == false)
					boolMap_1[i][j] = false;
			}
		}
	}
	
	//生成原始地图层
	bool** boolMap_tar = boolMap_1;//目标bool图
	for (int i = 0; i < WORLD_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_HEIGHT; j++)
		{
			Facility* fac;
			if (boolMap_tar[i][j]) {
				fac = FacilityDirtWall::createNew();
			}
			else {
				fac = FacilityDirtBG::createNew();
			}
			fac->x = i;
			fac->y = j;
			fac->renewPosition();
		}
	}
	
	//计算到王距离
	updateDistToKing();
	
	//P5-生成水体
	std::cout << "gameToolkit::summonMap_2_0:P5-生成水体\n";
	bool** waterMap = new bool* [WORLD_WIDTH];//水体bool图
	{
		//bool图内存初始化
		for (size_t i = 0; i < WORLD_WIDTH; i++)
		{
			waterMap[i] = new bool[WORLD_HEIGHT];
		}
		//赋值初始化
		for (int i = 0; i < WORLD_WIDTH; i++)
		{
			for (int j = 0; j < WORLD_HEIGHT; j++)
			{
				waterMap[i][j] = false;
			}
		}

		//扫描法获取水区
		std::cout << "检测可能的水区\n";
		for (int i = WORLD_HEIGHT - 3; i >= 1; i--)
		{
			int current_searching_y = i;
			int start_x = 0;
			while (true)
			{
				auto wp = WaterProbe(current_searching_y);
				if (wp.searchPossibalArea(boolMap_1, start_x)) {
					if (wp.checkUpAndDown(boolMap_1, waterMap)) {
						//一个比较垃圾的随机化填水
						if(rand()%4<=2)
						wp.fillWater(waterMap);
					}
				}
				else
				{
					break;
				}
				start_x = wp.x_end + 1;
			}
		}


	}

	//开始生成水
	for (int i = 0; i < WORLD_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_HEIGHT; j++)
		{
			Facility* fac;
			if (waterMap[i][j]) {
				if (!boolMap_1[i][j-1]&& !waterMap[i][j - 1]) {
					fac = FacilityWaterUpper::createNew();
				}
				else
				{
					fac = FacilityWaterFull::createNew();
				}
				fac->x = i;
				fac->y = j;
				fac->renewPosition();
			}
		}
	}
	
	//P6-生成攀附层
	std::cout << "P6生成攀附层\n";
	std::list<Vec2>* path;
	{
		//使用寻路探针
		int start_x = 0;
		for (int i = 0; i < WORLD_WIDTH; i++)
		{
			if (!boolMap_1[i][0])
			{
				start_x = i;
				break;
			}
		}
		auto pp = PathProbe_2(boolMap_1, start_x, 0);
		path = pp.solve();

		std::cout <<"path length:"<< path->size() << "\n";
	}

	//生成path-测试
	{
		/*
		for (auto it = path->begin(); it != path->end(); it++)
		{
			auto animUnit = AnimationUnit::createNew();

			animUnit->type = AnimType::Default;
			animUnit->depth = 5;
			animUnit->deltaX = 0;
			animUnit->deltaY = 0;
			animUnit->x = it->x;
			animUnit->y = it->y;
			animUnit->angle = 0;
			animUnit->flip = SDL_FLIP_NONE;
			animUnit->height = 32;
			animUnit->width = 32;
		}
		*/
		//生成王的位置

		//生成攀爬物

		std::cout << "生成攀爬物\n";
		summonMap_Climbing(boolMap_1, path);

		//放梯子

		std::cout << "放梯子\n";
		summonMap_summonLadder(boolMap_1, path);
		//放绳子

		std::cout << "放绳子\n";
		summonMap_summonRope(boolMap_1, path);
	}

	std::cout << "成功生成地图\n";

	updateDistWalkToKing();

	delete path;

	//销毁bool图
	for (size_t i = 0; i < WORLD_WIDTH; i++)
	{
		delete[] boolMap_1[i];
	}
	delete[] boolMap_1;

	//销毁水图
	for (size_t i = 0; i < WORLD_WIDTH; i++)
	{
		delete[] waterMap[i];
	}
	delete[] waterMap;

	std::cout << "gameToolkit::summonMap_2_0:生成完成\n";
}

//离散曲线平滑度评估算法
double gameToolkit::summonMap_curveSmoothAssess(std::list<Vec2>* curve, int i_start, int i_end)
{
	//约束输入参数条件
	if (i_start < 0 || i_end < i_start + 3 || i_end >= curve->size())return 0;
	//设置起始与结束的索引
	
	int start = i_start;
	int end = i_end;

	//开始计算和评估
	auto it = curve->begin();
	std::advance(it, start);
	//用列表储存每一个方向值
	auto dList = new std::vector<int>();

	int current = start;
	while (true)
	{
		if (current == end)break;
		else
		{
			auto v1 = (*it);
			it++;
			auto v2 = (*it);
			auto d = _get2GridDirection(v1.x, v1.y, v2.x, v2.y);
			if (d < 0) {
				std::cout << "ERROR::summonMap_curveSmoothAssess 曲线不连续\n";
				return 0;
			}
			dList->push_back(d);
			//std::cout << d << "\n";
			current++;
		}
	}
	//计算方向变化率
	auto ddList = new std::vector<double>();

	for (size_t i = 0; i <= dList->size()-2; i++)
	{
		double dd = static_cast<__int64>(dList->at(i + 1)) - dList->at(i);
		if (dd < 0)dd += 8;
		ddList->push_back(dd);
	}

	//计算方差
	double average = 0;
	double variance = 0;
	for (size_t i = 0; i < ddList->size()-1; i++)
	{
		average += ddList->at(i);
	}
	average = average / ddList->size();

	double mid = floor(ddList->size() / 2);

	int count = 0;
	for (size_t i = 0; i < ddList->size() - 1; i++)
	{
		auto k = ddList->at(i) - average;
		variance += k * k * (ddList->size() - abs(mid - count)) / ddList->size();
		count++;
	}

	//计算凹凸性
	it = curve->begin();
	std::advance(it, start);
	auto p1 = (*it);

	it = curve->begin();
	std::advance(it, end);
	auto p2 = (*it);

	it = curve->begin();
	std::advance(it, round(double(static_cast<__int64>(end) + start) / 2));
	auto p3 = (*it);

	Vec2 vd = Vec2(p1.y - p2.y, p2.x - p1.x);
	Vec2 vj = Vec2(p3.x - p1.x, p3.y - p1.y);

	variance = sqrt(variance);

	if (vd.x * vj.x + vd.y * vj.y < 0) {
		variance = -variance;
	}

	delete dList;
	delete ddList;
	return variance;
}

int gameToolkit::_get2GridDirection(int x1, int y1, int x2, int y2)
{
	if (abs(x1 - x2) >= 2 || abs(y1 - y2) >= 2) {
		return -1;
	}

	if (x2 == x1 + 1) {
		if (y2 == y1 - 1) {
			return 1;
		}
		else if (y2 == y1) {
			return 0;
		}
		else if (y2 == y1 + 1) {
			return 7;
		}
	}
	else if (x2 == x1) {
		if (y2 == y1 - 1) {
			return 2;
		}
		else if (y2 == y1) {
			return -1;
		}
		else if (y2 == y1 + 1) {
			return 6;
		}
	}
	else if (x2 == x1 - 1) {
		if (y2 == y1 - 1) {
			return 3;
		}
		else if (y2 == y1) {
			return 4;
		}
		else if (y2 == y1 + 1) {
			return 5;
		}
	}
	
	return -1;
}

void gameToolkit::summonMap_curveFilling( bool** boolMap,std::list<Vec2>* curve, int i_start, int i_end)
{
	if (i_start < 0 || i_end >= curve->size() || i_start >= i_end)return;

	auto it = curve->begin();
	std::advance(it, i_end);
	auto p2 = (*it);//终点

	it = curve->begin();
	std::advance(it, i_start);
	auto p1 = (*it);//起点

	auto amount = i_end - i_start + 1;//经历了修改的数量
	//分离出需要修改的部分
	for (int i = 0; i < amount; i++)
	{
		it++;
		auto p = (*it);
		if (p.x == WORLD_WIDTH - 1 || p.x == 0 || p.y == WORLD_HEIGHT - 1 || p.y == 0)continue;
		boolMap[p.x][p.y] = true;
	}
}

void gameToolkit::summonMap_crossDig(bool** boolMap, std::list<Vec2>* curve, int i_start, int i_end)
{
	if (i_start < 0 || i_end >= curve->size() || i_start >= i_end)return;

	auto it = curve->begin();
	std::advance(it, i_end);
	auto p2 = (*it);//终点

	it = curve->begin();
	std::advance(it, i_start);
	auto p1 = (*it);//起点

	auto amount = i_end - i_start + 1;//经历了修改的数量

	//分离出需要修改的部分
	for (int i = 0; i < amount; i++)
	{
		it++;
		auto p = (*it);
		if (p.x > 0 && p.x < WORLD_WIDTH - 1 && p.y > 0 && p.y < WORLD_HEIGHT - 1) {
			boolMap[p.x][p.y] = false;

			boolMap[p.x+1][p.y] = false;

			boolMap[p.x][p.y+1] = false;

			boolMap[p.x-1][p.y] = false;

			boolMap[p.x][p.y-1] = false;
		}
	}
}

void gameToolkit::summonMap_summonRope(bool** boolMap, std::list<Vec2>* path)
{
	int rope_x;
	int y_down, y_up;

	bool summon = false;
	bool atLeft = false;

	path->reverse();
	//std::cout << path->size() << "\n";
	auto it = path->begin();
	while (true)
	{
		int currrent_x = it->x;
		int currrent_y = it->y;
		it++;
		if (it == path->end()) {
			break;
		}
		int next_x = it->x;
		int next_y = it->y;
		//std::cout << next_x << " " << next_y << "\n";
		
		if (!summon && next_y < currrent_y) {
			rope_x = currrent_x;
			y_down = currrent_y;
			summon = true;
		}
		if (summon) {
			if (next_x > currrent_x) {
				y_up = currrent_y + 1;
				summonMap_RopeSide(boolMap, rope_x, y_down, y_up, true);
				summon = false;
			}
			else if (next_x < currrent_x) {
				y_up = currrent_y + 1;
				summonMap_RopeSide(boolMap, rope_x, y_down, y_up, false);
				summon = false;
			}
			else if (next_y == 0) {
				y_up = currrent_y - 1;
				summonMap_RopeSide(boolMap, rope_x, y_down, y_up, false);
				summon = false;
			}
		}
	}
}

void gameToolkit::summonMap_RopeSide(bool** boolMap, int x, int y_down, int y_up, bool atRight)
{
	//std::cout << "生成绳子\n";
	if (atRight) {
		bool ifRope = false;
		for (int i = y_up; i <= y_down; i++)
		{
			if (!boolMap[x + 1][i]) {
				ifRope = true;
				break;
			}
		}
		if (!ifRope) {
			//std::cout << "不需要生成绳子\n";
			return;
		}
		for (int i = y_up; i <= y_down; i++)
		{
			Facility* f;
			{
				if (i == y_up)
					f = FacilityRopeHeadR::createNew();
				else if(i ==y_down)
					f = FacilityRopeTailR::createNew();
				else
				{
					int r = rand()%2;
					if (r == 0)
						f = FacilityRope1R::createNew();
					else
						f = FacilityRope2R::createNew();
				}
			}
			f->x = x;
			f->y = i;
			f->renewPosition();
		}
	}
	else
	{
		bool ifLadder = false;
		for (int i = y_up; i <= y_down; i++)
		{
			if (!boolMap[x - 1][i]) {
				ifLadder = true;
				break;
			}
		}
		if (!ifLadder) {
			//std::cout << "不需要生成绳子\n";
			return;
		}
		for (int i = y_up; i <= y_down; i++)
		{
			Facility* f;
			{
				if (i == y_up)
					f = FacilityRopeHeadL::createNew();
				else if (i == y_down)
					f = FacilityRopeTailL::createNew();
				else
				{
					int r = rand() % 2;
					if (r == 0)
						f = FacilityRope1L::createNew();
					else
						f = FacilityRope2L::createNew();
				}
			}
			f->x = x;
			f->y = i;
			f->renewPosition();
		}
	}

	std::cout << "完成生成绳子\n";
}

void gameToolkit::summonMap_summonLadder(bool** boolMap, std::list<Vec2>* path)
{
	int ladder_x;
	int y_down, y_up;

	bool summon = false;

	//std::cout << path->size() << "\n";
	//int count = 0;
	auto it = path->begin();
	while (true)
	{
		//count++;
		//std::cout << count << "\n";
		int currrent_x = it->x;
		int currrent_y = it->y;
		it++;
		if (it == path->end()) {
			break;
		}
		int next_x = it->x;
		int next_y = it->y;

		if (!summon && next_y < currrent_y) {
			ladder_x = currrent_x;
			y_down = currrent_y;
			summon = true;
		}
		if (summon) {
			if (next_x > currrent_x) {
				y_up = currrent_y + 1;
				summonMap_LadderSide(boolMap, ladder_x, y_down, y_up, true);
				summon = false;
			}
			else if (next_x < currrent_x) {
				y_up = currrent_y + 1;
				summonMap_LadderSide(boolMap, ladder_x, y_down, y_up, false);
				summon = false;
			}
		}
	}
}

void gameToolkit::summonMap_LadderSide(bool** boolMap, int x, int y_down, int y_up, bool atRight)
{

	if (atRight) {
		bool ifLadder = false;
		for (int i = y_up; i <=y_down ; i++)
		{
			if (!boolMap[x + 1][i]) {
				ifLadder = true;
				break;
			}
		}
		if (!ifLadder) {
			return;
		}
		for (int i = y_up; i <= y_down; i++)
		{
			auto f = FacilityLadderR::createNew();
			f->x = x;
			f->y = i;
			f->renewPosition();
		}
	}
	else
	{
		bool ifLadder = false;
		for (int i = y_up; i <= y_down; i++)
		{
			if (!boolMap[x -1][i]) {
				ifLadder = true;
				break;
			}
		}
		if (!ifLadder) {
			return;
		}
		for (int i = y_up; i <= y_down; i++)
		{
			auto f = FacilityLadderL::createNew();
			f->x = x;
			f->y = i;
			f->renewPosition();
		}
	}
}

void gameToolkit::summonMap_Climbing(bool** boolMap, std::list<Vec2>* path)
{
	for (int x = 1; x < WORLD_WIDTH - 1; x++)
	{
		for (int y = 1; y < WORLD_HEIGHT - 1; y++)
		{
			if (!boolMap[x][y]) {
				if (boolMap[x][y+1])
				{
					if (boolMap[x - 1][y]&& boolMap[x + 1][y])
					{
						auto f = FacilityDirtStairB::createNew();
						f->x = x;
						f->y = y;
						f->renewPosition();
						continue;
					}

					if (boolMap[x-1][y]) {
						auto f = FacilityDirtStairL::createNew();
						f->x = x;
						f->y = y;
						f->renewPosition();
						continue;
					}
					else if (boolMap[x+1][y]) {
						auto f = FacilityDirtStairR::createNew();
						f->x = x;
						f->y = y;
						f->renewPosition();
						continue;
					}
				}
			}
		}
	}

	for (auto it = path->begin(); it != path->end(); it++)
	{
		bool up, down, left, right;
		if (it->y == 0) up = false; 
		else
		{
			up = boolMap[it->x][it->y-1];
		}
		if (it->y == WORLD_HEIGHT - 1) down = false;
		else
		{
			down = boolMap[it->x][it->y + 1];
		}
		left = boolMap[it->x - 1][it->y];
		right = boolMap[it->x + 1][it->y];

		if (!down)
		{
			if (left)
			{
				auto f = FacilityDirtClimbL_t1::createNew();
				f->x = it->x;
				f->y = it->y;
				f->renewPosition();
			}
			else if (right)
			{
				auto f = FacilityDirtClimbR_t1::createNew();
				f->x = it->x;
				f->y = it->y;
				f->renewPosition();
			}
		}
	}
}

void gameToolkit::updateDistToKing()
{
	auto map = MapSystem::getInstance()->map;

	//刷掉所有原来的数值
	for (auto i = 0; i < WORLD_WIDTH; i++)
	{
		for (auto j = 0; j < WORLD_HEIGHT; j++)
		{
			map->at(i)->at(j)->distToKing=-1;
		}
	}


	//用两个列表交替循环
	auto cur_list = new std::list<Grid*>();
	auto next_list = new std::list<Grid*>();
	//启动点
	next_list->push_back(map->at(GlobalData::KingX)->at(GlobalData::KingY));
	int cur_dist = 0;
	while (true)
	{
		if (next_list->size() == 0)break;
		else
		{
			//交换列表
			auto list = cur_list;
			cur_list = next_list;
			next_list = list;
			//赋值和加入列表
			for (auto it = cur_list->begin(); it != cur_list->end(); it++)
			{
				if ((*it)->distToKing != -1)continue;
				(*it)->distToKing = cur_dist;

				int cur_x = (*it)->x;
				int cur_y = (*it)->y;
				//std::cout << "刷新distToKing" << cur_x << "," << cur_y <<" dist " <<cur_dist << "\n";
				int x, y;

				x = cur_x + 1; y = cur_y;
				if (x >= 0 && x < WORLD_WIDTH && y >= 0 && y < WORLD_HEIGHT && !ifAbsoluteBlocked(x, y) && map->at(x)->at(y)->distToKing == -1) {
					next_list->push_back(map->at(x)->at(y));
				}
				x = cur_x; y = cur_y + 1;
				if (x >= 0 && x < WORLD_WIDTH && y >= 0 && y < WORLD_HEIGHT && !ifAbsoluteBlocked(x, y) && map->at(x)->at(y)->distToKing == -1) {
					next_list->push_back(map->at(x)->at(y));
				}
				x = cur_x - 1; y = cur_y;
				if (x >= 0 && x < WORLD_WIDTH && y >= 0 && y < WORLD_HEIGHT && !ifAbsoluteBlocked(x, y) && map->at(x)->at(y)->distToKing == -1) {
					next_list->push_back(map->at(x)->at(y));
				}
				x = cur_x; y = cur_y - 1;
				if (x >= 0 && x < WORLD_WIDTH && y >= 0 && y < WORLD_HEIGHT && !ifAbsoluteBlocked(x, y) && map->at(x)->at(y)->distToKing == -1) {
					next_list->push_back(map->at(x)->at(y));
				}

			}
			cur_dist += 1;
			cur_list->clear();
		}
	}

	delete next_list;
	delete cur_list;
}

void gameToolkit::updateDistWalkToKing()
{
	auto map = MapSystem::getInstance()->map;

	//刷掉所有原来的数值
	for (auto i = 0; i < WORLD_WIDTH; i++)
	{
		for (auto j = 0; j < WORLD_HEIGHT; j++)
		{
			map->at(i)->at(j)->distToKing_walk = -1;
		}
	}


	//用两个列表交替循环
	auto cur_list = new std::list<Grid*>();
	auto next_list = new std::list<Grid*>();
	//启动点
	next_list->push_back(map->at(GlobalData::KingX)->at(GlobalData::KingY));
	int cur_dist = 0;
	while (true)
	{
		if (next_list->size() == 0)break;
		else
		{
			//交换列表
			auto list = cur_list;
			cur_list = next_list;
			next_list = list;
			//赋值和加入列表
			for (auto it = cur_list->begin(); it != cur_list->end(); it++)
			{
				if ((*it)->distToKing_walk != -1)continue;
				(*it)->distToKing_walk = cur_dist;

				int cur_x = (*it)->x;
				int cur_y = (*it)->y;
				//std::cout << "刷新distToKing" << cur_x << "," << cur_y <<" dist " <<cur_dist << "\n";
				int x, y;

				x = cur_x + 1; y = cur_y;
				if (x >= 0 && x < WORLD_WIDTH && y >= 0 && y < WORLD_HEIGHT && (ifWalkable(x, y) || ifSwimable(x, y)) && map->at(x)->at(y)->distToKing_walk == -1) {
					next_list->push_back(map->at(x)->at(y));
				}
				x = cur_x; y = cur_y + 1;
				if (x >= 0 && x < WORLD_WIDTH && y >= 0 && y < WORLD_HEIGHT && (ifWalkable(x, y) || ifSwimable(x, y)) && map->at(x)->at(y)->distToKing_walk == -1) {
					next_list->push_back(map->at(x)->at(y));
				}
				x = cur_x - 1; y = cur_y;
				if (x >= 0 && x < WORLD_WIDTH && y >= 0 && y < WORLD_HEIGHT && (ifWalkable(x, y) || ifSwimable(x, y)) && map->at(x)->at(y)->distToKing_walk == -1) {
					next_list->push_back(map->at(x)->at(y));
				}
				x = cur_x; y = cur_y - 1;
				if (x >= 0 && x < WORLD_WIDTH && y >= 0 && y < WORLD_HEIGHT && (ifWalkable(x, y) || ifSwimable(x, y)) && map->at(x)->at(y)->distToKing_walk == -1) {
					next_list->push_back(map->at(x)->at(y));
				}

			}
			cur_dist += 1;
			cur_list->clear();
		}
	}

	delete next_list;
	delete cur_list;
}

void gameToolkit::createText(double _x, double _y, const char* msg, SDL_Color color)
{
	TTFParticle* t = TTFParticle::createNew();
	t->fontUnit = TTFUnit::createNew(msg, color);
	t->livingTime = 40;
	t->v_y = -0.01 + double(rand() % 10) / 1000;
	t->v_x = double(rand() % 4) / 1000 - 0.002;
	t->a_x = -(t->v_x) / t->livingTime;
	t->x = _x + double(rand() % 10) / 100 - 0.05;
	t->y = _y + double(rand() % 10) / 100 - 0.05;
}

bool gameToolkit::ifTarget(AllyType proj, AllyType tar)
{
	if (tar == AllyType::peace || proj == AllyType::peace) {
		return false;
	}
	else if (proj!=tar) {
		std::cout << int(proj)<<" "<<int(tar) << "\n";
		return true;
	}
	else
	{
		return false;
	}
}

bool gameToolkit::ifAbsoluteBlocked(double _x, double _y)
{
	/*
	当一个格子里有完全阻挡的设施就认为是绝对阻挡区域
	*/
	int x = round(_x);
	int y = round(_y);
	Grid* grid = MapSystem::getInstance()->map->at(x)->at(y);
	for (auto it = grid->facilityList->begin(); it != grid->facilityList->end(); it++)
	{
		auto f = *it;
		if (f->blockingType == BlockingType::absolute) {
			return true;
		}
	}
	return false;
}

bool gameToolkit::ifWalkable(double _x, double _y)
{
	/*
	当一个格位不是完全阻挡区域
	且下方有支撑性的设施或者完全阻挡设施
	那么就是可行走空间
	*/
	int x = round(_x);
	int y = round(_y);

	if (y < 0 || y >= WORLD_HEIGHT - 1 || ifAbsoluteBlocked(x, y))return false;

	Grid* grid = MapSystem::getInstance()->map->at(x)->at(y);
	for (auto it = grid->facilityList->begin(); it != grid->facilityList->end(); it++)
	{
		auto f = *it;
		if(f->blockingType==BlockingType::supportive)
		{
			return true;
		}
	}
	Grid* grid_under = MapSystem::getInstance()->map->at(x)->at(static_cast<__int64>(y) + 1);
	for (auto it = grid_under->facilityList->begin(); it != grid_under->facilityList->end(); it++)
	{
		auto f = *it;
		if (f->blockingType == BlockingType::supportive|| f->blockingType == BlockingType::absolute)
		{
			return true;
		}
	}
	return false;
}

bool gameToolkit::ifLiquid(double _x, double _y)
{
	/*
	有液体就是液体区
	*/
	int x = round(_x);
	int y = round(_y);
	Grid* grid = MapSystem::getInstance()->map->at(x)->at(y);

	bool liquid = false;
	for (auto it = grid->facilityList->begin(); it != grid->facilityList->end(); it++)
	{
		auto f = *it;
		if (f->blockingType == BlockingType::liquid)
		{
			liquid = true;
		}
	}
	return liquid;
}

bool gameToolkit::ifSubmersed(double _x, double _y)
{
	/*
	上方和下方都被液体淹没就是淹没区
	*/
	int x = round(_x);
	int y = round(_y);
	if (ifAbsoluteBlocked(x, y) || y == 0)return false;
	if (ifLiquid(x, y) && ifLiquid(x, static_cast<__int64>(y) - 1)) {
		return true;
	}
	return false;
}

bool gameToolkit::ifSwimable(double _x, double _y)
{
	int x = round(_x);
	int y = round(_y);
	if (ifLiquid(x, y) && !ifAbsoluteBlocked(x, y)) {
		return true;
	}
	return false;
}

bool gameToolkit::ifFalling(double _x, double _y, int bodyWidth, int bodyHeight)
{
	int x = round(_x);
	int y = round(_y);
	//检测所有身体体积最下方一排的格子
	for (auto i = x; i < x+bodyWidth; i++)
	{
		if (ifAbsoluteBlocked(x, y) || ifLiquid(x, static_cast<__int64>(y) - bodyHeight + 1) || ifWalkable(x, y)) {
			return false;
		}
	}
	return true;
	
}

Vec2::Vec2(int _x, int _y)
{
	x = _x;
	y = _y;
}

RoomBody::RoomBody(int _x, int _y, int _w, int _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
}

MarginProbe::MarginProbe(int _x, int _y, int _direction)
{
	x = _x;
	y = _y;
	direction = _direction;
}

void MarginProbe::turnClockwise(bool reverse)
{
	if (reverse) {
		direction++;
	}
	else
	{
		direction--;
	}
	while (direction >= 8) {
		direction -= 8;
	}
	while (direction < 0) {
		direction += 8;
	}
}

void MarginProbe::go(bool** boolmap, int* out_X, int* out_Y)
{
	int count = 0;
	if (!checkIfSolid(boolmap)) {
		while (true)
		{
			turnClockwise(false);
			if (checkIfSolid(boolmap)) {
				turnClockwise(true);
				break;
			}
			count++;
			if (count >= 8) {
				std::cout << "ERROR:MarginProbe Check infinite times - all empty\n";
				return;
			}
		}
	}
	else
	{
		while (checkIfSolid(boolmap))
		{
			turnClockwise(true);
			count++;
			if (count >= 8) {
				std::cout << "ERROR:MarginProbe Check infinite times - all solid\n";
				return;
			}
		}
	}

	int tar_x = 0;
	int tar_y = 0;
	switch (direction)
	{
	case 0:
		tar_x = x + 1;
		tar_y = y;
		break;
	case 1:
		tar_x = x + 1;
		tar_y = y - 1;
		break;
	case 2:
		tar_x = x;
		tar_y = y - 1;
		break;
	case 3:

		tar_x = x - 1;
		tar_y = y - 1;
		break;
	case 4:
		tar_x = x - 1;
		tar_y = y;
		break;
	case 5:
		tar_x = x - 1;
		tar_y = y + 1;
		break;
	case 6:
		tar_x = x;
		tar_y = y + 1;
		break;
	case 7:
		tar_x = x + 1;
		tar_y = y + 1;
		break;
	default:
		std::cout << "ERROR::MarginProbe direction out of range\n";
		throw direction;
		break;
	}

	*out_X = tar_x;
	*out_Y = tar_y;

	x = tar_x;
	y = tar_y;

}

bool MarginProbe::checkIfSolid(bool** boolmap)
{
	int tar_x = 0;
	int tar_y = 0;
	switch (direction)
	{
	case 0:
		tar_x = x + 1;
		tar_y = y;
		break;
	case 1:
		tar_x = x + 1;
		tar_y = y - 1;
		break;
	case 2:
		tar_x = x;
		tar_y = y - 1;
		break;
	case 3:
		tar_x = x - 1;
		tar_y = y - 1;
		break;
	case 4:
		tar_x = x - 1;
		tar_y = y;
		break;
	case 5:
		tar_x = x - 1;
		tar_y = y + 1;
		break;
	case 6:
		tar_x = x;
		tar_y = y + 1;
		break;
	case 7:
		tar_x = x + 1;
		tar_y = y + 1;
		break;
	default:
		std::cout << "ERROR::MarginProbe direction out of range\n";
		throw direction;
		break;
	}
	if (tar_x < 0 || tar_x >= WORLD_WIDTH || tar_y < 0 || tar_y >= WORLD_HEIGHT) {
		return true;
	}
	return boolmap[tar_x][tar_y];
}

Vec2 MarginProbe::getFront()
{
	auto v = Vec2(0,0);

	switch (direction)
	{
	case 0:
		v.x = x + 1;
		v.y = y;
		break;
	case 1:
		v.x = x + 1;
		v.y = y - 1;
		break;
	case 2:
		v.x = x;
		v.y = y - 1;
		break;
	case 3:
		v.x = x - 1;
		v.y = y - 1;
		break;
	case 4:
		v.x = x - 1;
		v.y = y;
		break;
	case 5:
		v.x = x - 1;
		v.y = y + 1;
		break;
	case 6:
		v.x = x;
		v.y = y + 1;
		break;
	case 7:
		v.x = x + 1;
		v.y = y + 1;
		break;
	default:
		throw direction;
		break;
	}
	return v;
}

bool MarginProbe::checkIfCovered(std::list<Vec2>* tar_curve)
{
	for (auto ir = tar_curve->begin(); ir != tar_curve->end(); ir++)
	{
		auto v = *ir;
		if (v.x == x && v.y == y) {
			return true;
		}
	}
	return false;
}

WaterProbe::WaterProbe(int _y)
{
	x_start = 0;
	x_end = 0;
	y = _y;
}

void WaterProbe::fillWater(bool** waterMap)
{
	for (int i = x_start; i <= x_end; i++)
	{
		waterMap[i][y] = true;
		//std::cout << i<<" " << y << "\n";
	}
}

bool WaterProbe::searchPossibalArea(bool** boolMap,int x)
{
	bool ifExist = false;
	for (int i = x; i < WORLD_WIDTH; i++)
	{
		if (!boolMap[i][y]) {
			x_start = i;
			ifExist = true;
			break;
		}
	}

	if (ifExist) {
		for (int i = x_start; i < WORLD_WIDTH; i++)
		{
			if (boolMap[i][y]) {
				x_end = i-1;
				break;
			}
		}
	}

	return ifExist;
}

bool WaterProbe::checkUpAndDown(bool** boolMap, bool** waterMap)
{
	bool current = true;
	bool last = true;
	int count = 0;
	for (int i = x_start; i <= x_end; i++)
	{
		if (!boolMap[i][y + 1] && !waterMap[i][y + 1])return false;
		
		last = current;
		current = boolMap[i][y - 1];
		if (current == false && last == true) {
			count++;
		}
		if (count >= 2)return false;
	}
	return true;
}

PathProbe_2::PathProbe_2(bool** _boolMap, int _x, int _y)
{
	tar_boolMap = _boolMap;
	x = _x;
	y = _y;
}

std::list<Vec2>* PathProbe_2::solve()
{
	auto shortest = solve_shortest();
	std::cout << "short path length:" << shortest->size() << "\n";
	auto low = solve_low(shortest);
	std::cout << "low path length:" << low->size() << "\n";
	return solve_connect(low);
}

std::list<Vec2>* PathProbe_2::solve_shortest()
{
	std::list<Vec2>* out = new std::list<Vec2>();

	out->push_back(Vec2(x, y));
	while (y < WORLD_HEIGHT - 2 && y >= 0 && x <= WORLD_WIDTH - 1 && x >= 0)
	{
		move(getShortestDirection());
		out->push_back(Vec2(x, y));
	}
	return out;
}

std::list<Vec2>* PathProbe_2::solve_low(std::list<Vec2>* ori_path)
{
	std::list<Vec2>* out = new std::list<Vec2>();

	for (auto it = ori_path->begin(); it != ori_path->end(); it++)
	{
		int my_x = it->x;
		int my_y = it->y;
		while (true)
		{
			if (tar_boolMap[my_x][my_y+1]) {
				bool findCommon = false;

				auto ir = out->end();
				for (int i = 0; i < out->size(); i++)
				{
					ir--;
					auto v = *ir;
					if (v.x==my_x&&v.y==my_y)
					{
						findCommon = true;
						break;
					}
				}

				if (!findCommon && my_y < WORLD_HEIGHT - 1)
					out->push_back(Vec2(my_x, my_y));
				break;
			}
			else
			{
				my_y++;
			}
		}
	}
	delete ori_path;

	/*
	int count = 0;
	for (auto i = out->begin(); i != out->end(); i++)
	{
		count++;
		std::cout << count << "@ " << i->x << " " << i->y << "\n";
	}
	*/

	return out;
}

std::list<Vec2>* PathProbe_2::solve_connect(std::list<Vec2>* ori_path)
{
	std::list<Vec2>* out = new std::list<Vec2>();

	auto it = ori_path->begin();
	auto first = *(it);

	for (int i = 0; i < first.y; i++)
	{
		out->push_back(Vec2(first.x, i));
	}
	out->push_back(first);

	while (true)
	{
		auto v_prev = *it;
		it++;
		if (it == ori_path->end())break;
		auto v_next = *it;

		if (v_next.y > v_prev.y) {
			for (int i = v_prev.y; i < v_next.y; i++)
			{
				out->push_back(Vec2(v_next.x, i));
			}
			out->push_back(v_next);
			continue;
		}
		else if (v_next.y < v_prev.y)
		{
			for (int i = v_prev.y - 1; i >= v_next.y; i--)
			{
				out->push_back(Vec2(v_prev.x, i));
			}
			out->push_back(v_next);
			continue;
		}
		else
		{
			out->push_back(v_next);
			continue;
		}
	}
	delete ori_path;

	/*
	int count = 0;
	for (auto i = out->begin(); i !=out->end(); i++)
	{
		count++;
		std::cout << count << " " << i->x << " " << i->y << "\n";
	}
	*/

	return out;
}

void PathProbe_2::move(DirectionType d)
{
	switch (d)
	{
	case DirectionType::right:
		//std::cout << "right\n";
		this->x++;
		break;
	case DirectionType::up:
		///std::cout << "up\n";
		this->y--;
		break;
	case DirectionType::left:
		//std::cout << "left\n";
		this->x--;
		break;
	case DirectionType::down:
		//std::cout << "down\n";
		this->y++;
		break;
	default:
		throw d;
		break;
	}
}

DirectionType PathProbe_2::getShortestDirection()
{
	int d_down = -1;
	int d_up = -1;

	if (y != 0)
		d_up = MapSystem::getInstance()->map->at(x)->at(static_cast<__int64>(y) - 1)->distToKing;

	if (y != WORLD_HEIGHT - 1)
		d_down = MapSystem::getInstance()->map->at(x)->at(static_cast<__int64>(y) + 1)->distToKing;

	int d_right = MapSystem::getInstance()->map->at(static_cast<__int64>(x) + 1)->at(y)->distToKing;
	int d_center = MapSystem::getInstance()->map->at(x)->at(y)->distToKing;
	int d_left = MapSystem::getInstance()->map->at(static_cast<__int64>(x) - 1)->at(y)->distToKing;

	DirectionType d = DirectionType::down;
	if (d_center > d_up && d_up >= 0) {
		d = DirectionType::up;
		return d;
	}
	else if (d_center > d_down && d_down >= 0) {
		d = DirectionType::down;
		return d;
	}
	else if (d_center > d_left && d_left >= 0) {
		d = DirectionType::left;
		return d;
	}
	else if (d_center > d_right && d_right >= 0) {
		d = DirectionType::right;
		return d;
	}
	else
	{
		std::cout << "Warnning:DirectionType d 初始化错误!\n";
		std::cout << "up:" << d_up << "\n";
		std::cout << "left:" << d_left << "\n";
		std::cout << "right:" << d_right << "\n";
		std::cout << "down:" << d_down << "\n";
		/*
		*/
		throw d;
	}
}

