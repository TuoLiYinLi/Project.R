#include "RenderingSystem.h"
#include "Defined.h"
#include "GlobalData.h"
#include <string>

#include "PhysicsChara.h"
#include "PhysicsObject.h"
#include "PhysicsFacility.h"
#include "PhysicsProjectile.h"
#include "WorldSystem.h"

RenderingSystem* RenderingSystem::getInstance()
{
    if (instance == nullptr) {
        auto a = new RenderingSystem();
        if (a == nullptr) {
#ifdef _DEBUG
            SDL_Log(u8"警告 RenderingSystem::new RenderingSystem()申请内存失败，值为nullptr");
#endif // _DEBUG
        }
        instance = a;
    }
    return instance;
}

void RenderingSystem::destroyInstance()
{
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

RenderingSystem::RenderingSystem()
{
    SDL_Log(u8"RenderingSystem construct");

    window_height = WINDOW_HEIGHT;
    window_width = WINDOW_WIDTH;

    viewX = 0;
    viewY = 0;
    viewScale = 1;

    vy = 0;
    vx = 0;
    vs = 0;

    font_zpix = TTF_OpenFont("./Resource/ttf/Zpix.ttf", FONT_PRECISION);

    //渲染资源列表
    list_animation_texture = new std::vector<std::vector<SDL_Texture*>*>();
    if (list_animation_texture == nullptr) {
#ifdef _DEBUG
        SDL_Log(u8" ERROR:new std::vector<SDL_Texture*>()申请内存失败，值为nullptr");
#endif // _DEBUG
    }
    loadAllAnim();

    //渲染单元列表
    list_rendering_units = new std::list<RenderingUnit*>();
    if (list_rendering_units == nullptr) {
#ifdef _DEBUG
        SDL_Log(u8"ERROR:new std::vector<RenderingAnimation*>()申请内存失败，值为nullptr");
#endif // _DEBUG
    }


}

RenderingSystem::~RenderingSystem()
{
#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << "RenderingSystem::~RenderingSystem()\n";
#endif // ANIMATION_SYSTEM_DEBUG

#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << " 活跃的TTFUnit数量:" << TTFUnit::getCurrentNum()
        << "\n 活跃的AnimationUnit数量:" << RenderingAnimation::getCurrentNum() << "\n";
#endif // ANIMATION_SYSTEM_DEBUG

    int count = 0;

    while (!list_rendering_units->empty())
    {

        list_rendering_units->front()->destroy();
        count++;
    }
    delete list_rendering_units;

    unloadAllAnim();
    list_animation_texture = nullptr;
    delete list_animation_texture;

    SDL_Log(u8"RenderingSystem destruct");
}

void RenderingSystem::renewViewPosition()
{
    double s1 = 1 / viewScale;
    viewX += GlobalData::delta_time * vx / 1000 * s1;
    viewY += GlobalData::delta_time * vy / 1000 * s1;
    viewScale += GlobalData::delta_time * vs * viewScale / 1000;

    if (viewScale > VIEW_SCALE_MAX) viewScale = VIEW_SCALE_MAX;
    if (viewScale < VIEW_SCALE_MIN)viewScale = VIEW_SCALE_MIN;

    const double axt = GlobalData::delta_time * double(VIEW_ACCELERATE_SPEED_X) / 1000;
    const double ayt = GlobalData::delta_time * double(VIEW_ACCELERATE_SPEED_Y) / 1000;
    const double ast = GlobalData::delta_time * double(VIEW_ACCELERATE_SPEED_SCALE) / 1000;

    if (vx > 0) {
        vx -= axt;
        if (vx < 0) vx = 0;
    }
    else
    {
        vx += axt;
        if (vx > 0) vx = 0;
    }

    if (vy > 0) {
        vy -= ayt;
        if (vy < 0) vy = 0;
    }
    else
    {
        vy += ayt;
        if (vy > 0) vy = 0;
    }

    if (vs > 0) {
        vs -= ast;
        if (vs < 0) vs = 0;
    }
    else
    {
        vs += ast;
        if (vs > 0) vs = 0;
    }


}

void RenderingSystem::renderTexture(SDL_Texture* texture, double x, double deltaX, double y, double deltaY, double w, double h, SDL_RendererFlip flip) const
{
    SDL_Rect rect;

    rect.x = (int)round(((x - viewX) * 32 + deltaX * 2) * viewScale - (viewScale - 1) * window_width * 0.5);
    rect.y = (int)round(((y - viewY) * 32 + deltaY * 2) * viewScale - (viewScale - 1) * window_height * 0.5);
    rect.w = (int)ceil(w * viewScale);
    rect.h = (int)ceil(h * viewScale);

    if (rect.x<-rect.w || rect.x>WINDOW_WIDTH + rect.w ||
        rect.y<-rect.h || rect.y>WINDOW_HEIGHT + rect.h)
    {
#ifdef ANIMATION_RENDER_DEBUG
        //std::cout << " 跳过一个超出范围的渲染目标\n";
#endif // ANIMATION_SYSTEM_DEBUG
        return;
    }

    SDL_RenderCopyEx(GlobalData::sdl_renderer, texture, nullptr, &rect, 0, nullptr, flip);
}

void RenderingSystem::renderOneUnit(const RenderingUnit* au) const {
    SDL_Texture* texture = au->getTexture();

    if (!texture)return;

    SDL_Rect rect = { 0,0,0,0 };

    switch (au->reference)
    {
    case RenderingReference::world:
        rect.x = (int)round(((au->x - viewX) * 32 + au->deltaX * 2) * viewScale - (viewScale - 1) * window_width * 0.5);
        rect.y = (int)round(((au->y - viewY) * 32 + au->deltaY * 2) * viewScale - (viewScale - 1) * window_height * 0.5);
        rect.w = (int)ceil(au->width * viewScale);
        rect.h = (int)ceil(au->height * viewScale);

        break;
    case RenderingReference::window:
        rect.x = (int)round(au->x);
        rect.y = (int)round(au->y);
        rect.w = (int)round(au->width);
        rect.h = (int)round(au->height);
        break;
    }

    if (rect.x<-rect.w || rect.x>WINDOW_WIDTH + rect.w ||
        rect.y<-rect.h || rect.y>WINDOW_HEIGHT + rect.h)
    {
#ifdef ANIMATION_RENDER_DEBUG
        //std::cout << " 跳过一个超出范围的渲染目标\n";
#endif // ANIMATION_SYSTEM_DEBUG
        return;
    }

    SDL_RenderCopyEx(GlobalData::sdl_renderer, texture, nullptr, &rect, 0, nullptr, au->getFlip());
}

void RenderingSystem::renderAll() const {
#ifdef ANIMATION_RENDER_DEBUG
    std::cout << "RenderingSystem::renderAll()\n";
#endif // ANIMATION_SYSTEM_DEBUG
    float currentDepth = 0;
    float maxDepth = 0;
    float nextDepth = FLT_MAX;

    int auNum = 0;

    for (auto i = list_rendering_units->begin(); i != list_rendering_units->end(); i++)
    {
        const float targetDepth = (*i)->depth;

        if (abs(targetDepth - currentDepth)<=DEPTH_PRECISION)
        {
            renderOneUnit(*i);
#ifdef ANIMATION_RENDER_DEBUG
            //std::cout << " 渲染第"<< auNum <<"个animationUnit\n";
#endif // ANIMATION_SYSTEM_DEBUG
        }
        if (targetDepth > currentDepth)
        {
            if (targetDepth > maxDepth)
            {
                maxDepth = targetDepth;
            }
            if (targetDepth < nextDepth)
            {
                nextDepth = targetDepth;
            }
        }

        auNum++;
    }

    while (true)
    {
        currentDepth = nextDepth;
        nextDepth = maxDepth;
        auNum = 0;

        for (auto i = list_rendering_units->begin(); i != list_rendering_units->end(); ++i)
        {
            const float targetDepth = (*i)->depth;

            if (abs(targetDepth - currentDepth)<=DEPTH_PRECISION)
            {
                renderOneUnit(*i);
#ifdef ANIMATION_RENDER_DEBUG
                //std::cout << " animUnit@" << auNum << "\n";
#endif // ANIMATION_SYSTEM_DEBUG
            }
            if (targetDepth > currentDepth)
            {

                if (targetDepth < nextDepth)
                {
                    nextDepth = targetDepth;
                }
            }
            auNum++;
        }


        if (abs(currentDepth - maxDepth)<=DEPTH_PRECISION) {
            break;
        }
    }
}

void RenderingSystem::renderOnePhysicsObject(PhysicsObject* physics_object) const
{
    SDL_Rect rect;

    rect.x = (int)round((physics_object->X - viewX) * 32 * viewScale - (viewScale - 1) * window_width * 0.5);
    rect.y = (int)round((physics_object->Y - viewY) * 32 * viewScale - (viewScale - 1) * window_height * 0.5);
    rect.w = (int)ceil(physics_object->bodyX * 32 * viewScale);
    rect.h = (int)ceil(physics_object->bodyY * 32 * viewScale);

    SDL_Color color = { 255,255,255,127 };

    switch (physics_object->getPhysicsType())
    {
    case PhysicsType::facility:
    {
        const auto facility_type = ((PhysicsFacility*)physics_object)->getFacilityType();
        switch (facility_type)
        {
        case BlockingType::support:
            color = { 180,80,30 ,127 };//橙色
            break;
        case BlockingType::air:
            color = { 226,176,251 ,23 };//淡紫色
            break;
        case BlockingType::solid:
            color = { 102,56,49 ,127 };//褐色
            break;
        case BlockingType::liquid:
            color = { 99,155,255 ,63 };//蓝色
            break;
        }
    }
    break;
    case PhysicsType::projectile:
        color = { 255,237,80 ,127 };//黄色

        break;
    case PhysicsType::chara:
        color = { 55,232,55 ,127 };//绿色
        break;
    case PhysicsType::none:
        color = { 0,0,0 ,127 };//黑色
        break;
    }

    SDL_SetRenderDrawColor(GlobalData::sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(GlobalData::sdl_renderer, &rect);
}

void RenderingSystem::renderALLPhysicsObjects() const
{
    for (auto i = WorldSystem::getInstance()->list_physics_facility->begin();
        i != WorldSystem::getInstance()->list_physics_facility->end(); ++i)
    {
        if ((*i)->getFacilityType() != BlockingType::liquid && (*i)->getFacilityType() != BlockingType::air)
            renderOnePhysicsObject(*i);
    }
    for (auto i = WorldSystem::getInstance()->list_physics_chara->begin();
        i != WorldSystem::getInstance()->list_physics_chara->end(); ++i)
    {
        renderOnePhysicsObject(*i);
    }
    for (auto i = WorldSystem::getInstance()->list_physics_facility->begin();
        i != WorldSystem::getInstance()->list_physics_facility->end(); ++i)
    {
        if ((*i)->getFacilityType() == BlockingType::liquid || (*i)->getFacilityType() == BlockingType::air)
            renderOnePhysicsObject(*i);
    }
    for (auto i = WorldSystem::getInstance()->list_physics_projectile->begin();
        i != WorldSystem::getInstance()->list_physics_projectile->end(); ++i)
    {
        renderOnePhysicsObject(*i);
    }
}



void RenderingSystem::loadAllAnim() {
#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << "RenderingSystem::loadAllAnim()\n";
#endif // ANIMATION_SYSTEM_DEBUG
    for (auto i = 0; i<int(AnimationType::size); i++)
    {
        loadAnim(AnimationType(i));
    }
}

void RenderingSystem::unloadAllAnim() {
    for (auto i = 0; i<int(AnimationType::size); i++)
    {
        if (list_animation_texture->at(i) != nullptr) {
            unloadAnim(AnimationType(i));
        }
    }
}

void RenderingSystem::loadAnim(AnimationType antp) {
#ifdef ANIMATION_SYSTEM_DEBUG
    SDL_Log(u8"RenderingSystem::loadAnim(AnimationType antp)");
#endif // ANIMATION_SYSTEM_DEBUG

    if (int(antp) >= int(AnimationType::size)) {
#ifdef _DEBUG
        SDL_Log(u8"ERROR:int(AnimationType)超出AnimType范围");
#endif // _DEBUG
        return;
    }

    if (list_animation_texture->size() == unsigned(antp)) {
#ifdef ANIMATION_SYSTEM_DEBUG
        std::cout << " 加载动画:" << int(antp) << "\n";
#endif // ANIMATION_SYSTEM_DEBUG
        std::string file = "";
        int num = 0;
        switch (antp)
        {
        case AnimationType::default_banned:
            file = "./Resource/texture/default_banned";
            num = 1;
            break;
        case AnimationType::default_b:
            file = "./Resource/texture/default_b";
            num = 1;
            break;
        case AnimationType::default_r:
            file = "./Resource/texture/default_r";
            num = 1;
            break;
        case AnimationType::default_g:
            file = "./Resource/texture/default_g";
            num = 1;
            break;
        case AnimationType::physics_facility_air:
            file = "./Resource/texture/physics_facility_air";
            num = 1;
            break;
        case AnimationType::physics_facility_liquid:
            file = "./Resource/texture/physics_facility_liquid";
            num = 1;
            break;
        case AnimationType::physics_facility_support:
            file = "./Resource/texture/physics_facility_support";
            num = 1;
            break;
        case AnimationType::physics_facility_solid:
            file = "./Resource/texture/physics_facility_solid";
            num = 1;
            break;
        case AnimationType::physics_chara:
            file = "./Resource/texture/physics_chara";
            num = 1;
            break;
        case AnimationType::physics_projectile:
            file = "./Resource/texture/physics_projectile";
            num = 1;
            break;
        case AnimationType::charaSlimeIdle:
            file = "./Resource/texture/SlimeIdle";
            num = 4;
            break;
        case AnimationType::charaSlimeMove:
            file = "./Resource/texture/SlimeMove";
            num = 4;
            break;
        case AnimationType::charaSlimeBasic:
            file = "./Resource/texture/SlimeEject";
            num = 4;
            break;
        case AnimationType::charaSlimeSpecial:
            file = "./Resource/texture/SlimeAbsorb";
            num = 7;
            break;
        case AnimationType::charaSlimeDeath:
            file = "./Resource/texture/SlimeDeath";
            num = 9;
            break;
        case AnimationType::charaWarriorMiner1_idle:
            file = "./Resource/texture/miner1-idle";
            num = 4;
            break;
        case AnimationType::charaWarriorMiner1_walk:
            file = "./Resource/texture/miner1-walk";
            num = 8;
            break;
        case AnimationType::charaWarriorMiner1_dig:
            file = "./Resource/texture/miner1-dig";
            num = 4;
            break;
        case AnimationType::charaWarriorMiner1_death:
            file = "./Resource/texture/miner1-death";
            num = 9;
            break;
        case AnimationType::gridDirt_1a:
            file = "./Resource/texture/Dirt_a_t1";
            num = 1;
            break;
        case AnimationType::gridDirt_1n:
            file = "./Resource/texture/Dirt_n_t1";
            num = 1;
            break;
        case AnimationType::gridDirdCracked:
            file = "./Resource/texture/Dirt_Cracked";
            num = 1;
            break;
        case AnimationType::gridDirtStair_1L:
            file = "./Resource/texture/Dirt_stairL_t1";
            num = 1;
            break;
        case AnimationType::gridDirtStair_1R:
            file = "./Resource/texture/Dirt_stairR_t1";
            num = 1;
            break;
        case AnimationType::gridDirtStair_1B:
            file = "./Resource/texture/Dirt_stairB_t1";
            num = 1;
            break;
        case AnimationType::gridDirtClimb_L_t1:
            file = "./Resource/texture/DirtClimb_Lt1";
            num = 1;
            break;
        case AnimationType::gridDirtClimb_L_t2:
            file = "./Resource/texture/DirtClimb_Lt2";
            num = 1;
            break;
        case AnimationType::gridGrass_h4:
            file = "./Resource/texture/Grass_h4";
            num = 1;
            break;
        case AnimationType::gridDirtButton_1:
            file = "./Resource/texture/Dirt_a_button_t1";
            num = 1;
            break;
        case AnimationType::gridWater_1full:
            file = "./Resource/texture/Water_full_t1";
            num = 1;
            break;
        case AnimationType::gridWater_1upper:
            file = "./Resource/texture/Water_upper_t1";
            num = 1;
            break;
        case AnimationType::ladder:
            file = "./Resource/texture/Ladder_L";
            num = 1;
            break;
        case AnimationType::ropeHead:
            file = "./Resource/texture/RopeHeadR";
            num = 1;
            break;
        case AnimationType::rope1:
            file = "./Resource/texture/Rope1R";
            num = 1;
            break;
        case AnimationType::rope2:
            file = "./Resource/texture/Rope2R";
            num = 1;
            break;
        case AnimationType::ropeTail:
            file = "./Resource/texture/RopeTailR";
            num = 1;
            break;
        case AnimationType::faciSlimeGlue_L1:
            file = "./Resource/texture/SlimeGlue_L1";
            num = 1;
            break;
        case AnimationType::chopDown:
            file = "./Resource/texture/chopDown";
            num = 5;
            break;
        case AnimationType::slimeBall:
            file = "./Resource/texture/slimeBall";
            num = 2;
            break;
        case AnimationType::particle_goldust:
            file = "./Resource/texture/goldust";
            num = 5;
            break;
        case AnimationType::size:
            SDL_Log(u8"错误 不能加载size");
            break;
        }
#ifdef ANIMATION_SYSTEM_DEBUG
        std::cout << " 材质数量:" << num << "\n";
#endif // ANIMATION_SYSTEM_DEBUG
        auto innerList = new std::vector<SDL_Texture*>();
        if (innerList == nullptr) {
            SDL_Log(u8" ERROR:加载材质内存不足");
            return;
        }
        list_animation_texture->push_back(innerList);



        for (auto i = 1; i <= num; i++)
        {
            std::string fullFile;
            if (num > 1) {
                fullFile = file + std::to_string(i) + std::string(".png");
            }
            else
            {
                fullFile = file + std::string(".png");
            }
            auto c_fullFile = fullFile.c_str();
            SDL_Texture* texture = IMG_LoadTexture(GlobalData::sdl_renderer, c_fullFile);
#ifdef ANIMATION_SYSTEM_DEBUG
            if (texture) {
                SDL_Log(u8" 成功加载%s", c_fullFile);
            }
            else
            {
                SDL_Log(u8" 无法加载%s", c_fullFile);
            }
#endif // ANIMATION_SYSTEM_DEBUG

            innerList->push_back(texture);
        }
    }
#ifdef ANIMATION_SYSTEM_DEBUG
    else
    {
        std::cout << " ERROR:已经加载了动画" << int(antp) << "，不能重复加载\n";
        return;
    }
#endif // ANIMATION_SYSTEM_DEBUG
}

void RenderingSystem::getLengthUTF8(char const* str, int* cnt)
{
    while (*str != '\0') {
        if (*str & 1 << 7) {
            if (*str & (1 << 6)) {
                if (*str & (1 << 5)) {
                    if (*str & (1 << 4)) {
                        cnt[4]++; cnt[0]++; str += 4;
                        continue;
                    }
                    cnt[3]++; cnt[0]++; str += 3;
                    continue;
                }
                cnt[2]++; cnt[0]++; str += 2;
                continue;
            }
        }
        cnt[1]++; cnt[0]++; str += 1;
        continue;
    }
}

void RenderingSystem::renderText_UTF8(const char* utf8_msg, int x, int y) const
{
    int count_str[4] = { 0,0,0,0 };
    getLengthUTF8(utf8_msg, count_str);

    SDL_Surface* surface = TTF_RenderUTF8_Blended(font_zpix, utf8_msg, { 255,255,255,255 });

    SDL_Texture* texture = SDL_CreateTextureFromSurface(GlobalData::sdl_renderer, surface);


    SDL_Rect rect;

    rect.x = x;
    rect.y = y;

    TTF_SizeUTF8(font_zpix, utf8_msg, &rect.w, &rect.h);

    SDL_RenderCopy(GlobalData::sdl_renderer, texture, nullptr, &rect);

    //别忘了清理
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


void RenderingSystem::unloadAnim(AnimationType antp) const {
#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << "unloadAnim(AnimationType antp)\n";
    std::cout << " 卸载动画:" << int(antp) << "\n";
#endif // ANIMATION_SYSTEM_DEBUG
    std::vector<SDL_Texture*>* ap = list_animation_texture->at(int(antp));
    if (list_animation_texture->at(int(antp)) == nullptr) {
#ifdef ANIMATION_SYSTEM_DEBUG
        std::cout << " ERROR:动画" << int(antp) << "并没有被加载，不能卸载\n";
#endif // ANIMATION_SYSTEM_DEBUG
        return;
    }
    else
    {
        int textureCount = 0;
        for (auto it = ap->begin(); it != ap->end(); ++it)
        {
            textureCount++;
            if ((*it) == nullptr) {
#ifdef ANIMATION_SYSTEM_DEBUG
                std::cout << " ERROR:这个动画的第" << textureCount << "个SDL_Texture*为nullptr,请检查加载过程\n";
#endif // ANIMATION_SYSTEM_DEBUG
            }
            else
            {
                SDL_DestroyTexture(*it);
                (*it) = nullptr;
#ifdef ANIMATION_SYSTEM_DEBUG
                std::cout << " 完成卸载第" << textureCount << "个SDL_Texture\n";
#endif // ANIMATION_SYSTEM_DEBUG
            }

        }
        delete list_animation_texture->at(int(antp));
        list_animation_texture->at(int(antp)) = nullptr;
    }
}

RenderingSystem* RenderingSystem::instance = nullptr;

