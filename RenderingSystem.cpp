#include <string>
#include "Defined.h"
#include "GlobalData.h"

#include "RenderingSystem.h"

#include "WorldSystem.h"

RenderingSystem* RenderingSystem::getInstance()
{
    if (instance == nullptr) {
        const auto a = new RenderingSystem();
#ifdef _DEBUG
        if (a == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"RenderingSystem* RenderingSystem::getInstance()申请内存失败，值为nullptr");
        }
#endif // _DEBUG
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
    loadAllAnimation();

    //渲染单元列表
    list_rendering_units = new std::list<RenderingUnit*>();
}

RenderingSystem::~RenderingSystem()
{

    int count = 0;

    while (!list_rendering_units->empty())
    {

        list_rendering_units->front()->destroy();
        count++;
    }
    delete list_rendering_units;

    unloadAllAnimation();
    list_animation_texture = nullptr;
    delete list_animation_texture;

    SDL_Log(u8"RenderingSystem destruct");
}

void RenderingSystem::renewViewPosition()
{
    const double s1 = 1 / viewScale;
    viewX += GlobalData::getTimeDelta() * vx / 1000 * s1;
    viewY += GlobalData::getTimeDelta() * vy / 1000 * s1;
    viewScale += GlobalData::getTimeDelta() * vs * viewScale / 1000;

    if (viewScale > VIEW_SCALE_MAX) viewScale = VIEW_SCALE_MAX;
    if (viewScale < VIEW_SCALE_MIN)viewScale = VIEW_SCALE_MIN;

    const double axt = GlobalData::getTimeDelta() * static_cast<double>(VIEW_ACCELERATE_SPEED_X) / 1000;
    const double ayt = GlobalData::getTimeDelta() * static_cast<double>(VIEW_ACCELERATE_SPEED_Y) / 1000;
    const double ast = GlobalData::getTimeDelta() * static_cast<double>(VIEW_ACCELERATE_SPEED_SCALE) / 1000;

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

void RenderingSystem::renderOneUnit(const RenderingUnit* au) const {
    SDL_Texture* texture = au->getTexture();

    if (!texture)return;

    SDL_Rect rect = { 0,0,0,0 };

    switch (au->reference)
    {
    case RenderingReference::world:
        rect.x = static_cast<int>(round(((au->x - viewX) * 32 + au->deltaX * 2) * viewScale - (viewScale - 1) * window_width * 0.5));
        rect.y = static_cast<int>(round(((au->y - viewY) * 32 + au->deltaY * 2) * viewScale - (viewScale - 1) * window_height * 0.5));
        rect.w = static_cast<int>(ceil(au->width * viewScale));
        rect.h = static_cast<int>(ceil(au->height * viewScale));

        break;
    case RenderingReference::window:
        rect.x = static_cast<int>(round(au->x));
        rect.y = static_cast<int>(round(au->y));
        rect.w = static_cast<int>(round(au->width));
        rect.h = static_cast<int>(round(au->height));
        break;
    }

    if (rect.x<-rect.w || rect.x>WINDOW_WIDTH + rect.w ||
        rect.y<-rect.h || rect.y>WINDOW_HEIGHT + rect.h)
    {
        return;
    }

    SDL_RenderCopyEx(GlobalData::sdl_renderer, texture, nullptr, &rect, 0, nullptr, au->getFlip());
}

void RenderingSystem::sortRenderingUnits() const
{
    list_rendering_units->sort(compareDepth);
}

void RenderingSystem::renderAll() const {
    for (auto i = list_rendering_units->begin(); i != list_rendering_units->end(); ++i)
    {
        if((*i)->flag_enable)
        renderOneUnit(*i);
    }
}


void RenderingSystem::loadAllAnimation()const{
    for (auto i = 0; i<static_cast<int>(AnimationType::size); ++i)
    {
        loadAnimation(static_cast<AnimationType>(i));
    }
}

void RenderingSystem::unloadAllAnimation()const {
    for (auto i = 0; i<static_cast<int>(AnimationType::size); ++i)
    {
        if (list_animation_texture->at(i) != nullptr) {
            unloadAnimation(static_cast<AnimationType>(i));
        }
    }
}

void RenderingSystem::loadAnimation(AnimationType antp)const {

#ifdef _DEBUG
    if (static_cast<int>(antp) >= static_cast<int>(AnimationType::size)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,u8"int(AnimationType)超出AnimType范围");
    }
#endif

    if (list_animation_texture->size() == static_cast<unsigned>(antp)) {
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

        case AnimationType::physics_debug_layer_outside:
            file = "./Resource/texture/physics_debug_layer_outside";
            num = 1;
            break;
        case AnimationType::physics_debug_layer_air:
            file = "./Resource/texture/physics_debug_layer_air";
            num = 1;
            break;
        case AnimationType::physics_debug_layer_support:
            file = "./Resource/texture/physics_debug_layer_support";
            num = 1;
            break;
        case AnimationType::physics_debug_layer_liquid:
            file = "./Resource/texture/physics_debug_layer_liquid";
            num = 1;
            break;
        case AnimationType::physics_debug_layer_absolute:
            file = "./Resource/texture/physics_debug_layer_absolute";
            num = 1;
            break;
        case AnimationType::physics_debug_layer_chara:
            file = "./Resource/texture/physics_debug_layer_chara";
            num = 1;
            break;
        case AnimationType::physics_debug_layer_projectile:
            file = "./Resource/texture/physics_debug_layer_projectile";
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

        case AnimationType::ui_exit_button_default:
            file = "./Resource/texture/exit_button_default";
            num = 1;
            break;
        case AnimationType::ui_exit_button_highlight:
            file = "./Resource/texture/exit_button_highlight";
            num = 1;
            break;
        case AnimationType::ui_exit_button_pressed:
            file = "./Resource/texture/exit_button_pressed";
            num = 1;
            break;

        //角色材质
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
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"不能加载AnimationType::size");
        }
        auto innerList = new std::vector<SDL_Texture*>();

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
#ifdef _DEBUG
            texture == nullptr ? SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"加载错误%s", c_fullFile) : SDL_Log(u8"成功加载%s", c_fullFile);
#endif
            innerList->push_back(texture);
        }
    }
#ifdef _DEBUG
    else
    {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"已经加载了动画%d，不能重复加载", static_cast<int>(antp));
    }
#endif 
}


SDL_Texture* RenderingSystem::getAnimation(AnimationType _animation_type,unsigned long long num) const
{
    const auto L = list_animation_texture->at(static_cast<int>(_animation_type));
    if(num>=L->size())
    {
        return nullptr;
    }else
    {
        return L->at(num);
    }
}

unsigned long long RenderingSystem::getAnimationSize(AnimationType _animation_type) const
{
    return list_animation_texture->at(static_cast<int>(_animation_type))->size();
}



void RenderingSystem::unloadAnimation(AnimationType antp) const {
    std::vector<SDL_Texture*>* ap = list_animation_texture->at(static_cast<int>(antp));
#ifdef _DEBUG
	if (ap == nullptr) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,u8"动画%d的材质列表为nullptr，不能卸载",static_cast<int>(antp));
    }
    int count = 0;
#endif

    for (auto it = ap->begin(); it != ap->end(); ++it)
    {
#ifdef _DEBUG
        count++;
#endif
        if ((*it) != nullptr) {
            SDL_DestroyTexture(*it);
            (*it) = nullptr;
        }
#ifdef _DEBUG
        else
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"动画%d的第%d个材质是nullptr，不能卸载", static_cast<int>(antp), count);
        }
#endif
    }
    delete list_animation_texture->at(static_cast<int>(antp));
    list_animation_texture->at(static_cast<int>(antp)) = nullptr;
    
}

RenderingSystem* RenderingSystem::instance = nullptr;

void RenderingSystem::add(RenderingUnit* ru) const
{
    list_rendering_units->push_back(ru);
}

void RenderingSystem::remove(RenderingUnit* ru) const
{
    list_rendering_units->remove(ru);
}

bool RenderingSystem::compareDepth(const RenderingUnit* ru1, const RenderingUnit* ru2)
{
    return ru1->depth < ru2->depth;
}
