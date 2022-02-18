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

    //打开字体
    font_grey = TTF_OpenFont("./Resource/ttf/Grey.ttf", 19);
#ifdef _DEBUG
    if(font_grey==nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"字体文件错误无法打开");
    }
#endif
    TTF_SetFontKerning(font_grey, true);

	//渲染资源列表
    list_animation_texture = new std::vector<std::vector<SDL_Texture*>*>();
    loadAllAnimation();

    //渲染单元列表
    list_rendering_units = new std::list<RenderingUnit*>();
}

RenderingSystem::~RenderingSystem()
{
    //释放文字资源
#ifdef _DEBUG
    if (font_grey == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"关闭字体时出错 font_silver = nullptr");
    }
#endif
    TTF_CloseFont(font_grey);


    //释放图像材质资源
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

    const SDL_Rect* clipping_rect= au->clipping_rect;

    SDL_Rect rect = { 0,0,0,0 };

    switch (au->reference)
    {
    case RenderingReference::world:
        rect.x = static_cast<int>(round(((au->x - viewX) * 32 + au->deltaX) * viewScale - (viewScale - 1) * window_width * 0.5));
        rect.y = static_cast<int>(round(((au->y - viewY) * 32 + au->deltaY) * viewScale - (viewScale - 1) * window_height * 0.5));
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
    SDL_SetTextureAlphaMod(texture, au->blend_color.a);
    SDL_SetTextureColorMod(texture, au->blend_color.r, au->blend_color.g, au->blend_color.b);

    SDL_RenderCopyEx(GlobalData::sdl_renderer, texture, clipping_rect, &rect, 0, nullptr, au->getFlip());
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
        std::string file;
        int num = 0;
        switch (antp)
        {
			//debug
        case AnimationType::debug_banned:
            file = "./Resource/texture/debug_banned";
            num = 1;
            break;
            //
        case AnimationType::debug_physics_outside:
            file = "./Resource/texture/debug_physics_outside";
            num = 1;
            break;
        case AnimationType::debug_physics_air:
            file = "./Resource/texture/debug_physics_air";
            num = 1;
            break;
        case AnimationType::debug_physics_support:
            file = "./Resource/texture/debug_physics_support";
            num = 1;
            break;
        case AnimationType::debug_physics_liquid:
            file = "./Resource/texture/debug_physics_liquid";
            num = 1;
            break;
        case AnimationType::debug_physics_solid:
            file = "./Resource/texture/debug_physics_solid";
            num = 1;
            break;
        case AnimationType::debug_physics_chara:
            file = "./Resource/texture/debug_physics_chara";
            num = 1;
            break;
        case AnimationType::debug_physics_projectile:
            file = "./Resource/texture/debug_physics_projectile";
            num = 1;
            break;
            //
        case AnimationType::debug_sequence_white:
            file = "./Resource/texture/debug_sequence_white";
            num = 4;
            break;
        case AnimationType::debug_sequence_red:
            file = "./Resource/texture/debug_sequence_red";
            num = 4;
            break;
        case AnimationType::debug_sequence_yellow:
            file = "./Resource/texture/debug_sequence_yellow";
            num = 4;
            break;
        case AnimationType::debug_sequence_green:
            file = "./Resource/texture/debug_sequence_green";
            num = 4;
            break;
        case AnimationType::debug_sequence_blue:
            file = "./Resource/texture/debug_sequence_blue";
            num = 4;
            break;
        case AnimationType::debug_sequence_black:
            file = "./Resource/texture/debug_sequence_black";
            num = 4;
            break;

            //UI
        case AnimationType::ui_button_exit_default:
            file = "./Resource/texture/ui_button_exit_default";
            num = 1;
            break;
        case AnimationType::ui_button_exit_highlight:
            file = "./Resource/texture/ui_button_exit_highlight";
            num = 1;
            break;
        case AnimationType::ui_button_exit_pressed:
            file = "./Resource/texture/ui_button_exit_pressed";
            num = 1;
            break;

        case AnimationType::ui_inspector_panel:
            file = "./Resource/texture/ui_inspector_panel";
            num = 1;
            break;

        case AnimationType::ui_button_menu_default:
            file = "./Resource/texture/ui_button_menu_default";
            num = 1;
            break;
        case AnimationType::ui_button_menu_highlight:
            file = "./Resource/texture/ui_button_menu_highlight";
            num = 1;
            break;
        case AnimationType::ui_button_menu_pressed:
            file = "./Resource/texture/ui_button_menu_pressed";
            num = 1;
            break;


        case AnimationType::ui_button_grid_default:
            file = "./Resource/texture/ui_button_grid_default";
            num = 1;
            break;
        case AnimationType::ui_button_grid_highlight:
            file = "./Resource/texture/ui_button_grid_highlight";
            num = 1;
            break;
        case AnimationType::ui_button_grid_pressed:
            file = "./Resource/texture/ui_button_grid_pressed";
            num = 1;
            break;
        case AnimationType::ui_button_grid_banned:
            file = "./Resource/texture/ui_button_grid_banned";
            num = 1;
            break;


        case AnimationType::ui_button_controller_mask:
            file = "./Resource/texture/ui_button_controller_mask";
            num = 1;
            break;

        case AnimationType::ui_energy_bar:
            file = "./Resource/texture/ui_energy_bar";
            num = 1;
            break;

        	//monster
        case AnimationType::monster_slime_idle:
            file = "./Resource/texture/monster_slime_idle";
            num = 4;
            break;
        case AnimationType::monster_slime_moving:
            file = "./Resource/texture/monster_slime_moving";
            num = 4;
            break;
        case AnimationType::monster_slime_dead:
            file = "./Resource/texture/monster_slime_dead";
            num = 9;
            break;
        case AnimationType::monster_slime_absorb:
            file = "./Resource/texture/monster_slime_absorb";
            num = 7;
            break;
        case AnimationType::monster_slime_eject:
            file = "./Resource/texture/monster_slime_eject";
            num = 4;
            break;

            //warrior
        case AnimationType::warrior_miner_pickaxe_idle:
            file = "./Resource/texture/warrior_miner_pickaxe_idle";
            num = 4;
            break;
        case AnimationType::warrior_miner_pickaxe_moving:
            file = "./Resource/texture/warrior_miner_pickaxe_moving";
            num = 8;
            break;
        case AnimationType::warrior_miner_pickaxe_dead:
            file = "./Resource/texture/warrior_miner_pickaxe_dead";
            num = 9;
            break;
        case AnimationType::warrior_miner_pickaxe_dig:
            file = "./Resource/texture/warrior_miner_pickaxe_dig";
            num = 4;
            break;

            //facility
        case AnimationType::facility_dirt_background_1:
            file = "./Resource/texture/facility_dirt_background_1";
            num = 1;
            break;
        case AnimationType::facility_dirt_background_2:
            file = "./Resource/texture/facility_dirt_background_2";
            num = 1;
            break;
        case AnimationType::facility_dirt_background_3:
            file = "./Resource/texture/facility_dirt_background_3";
            num = 1;
            break;
        case AnimationType::facility_dirt_background_4:
            file = "./Resource/texture/facility_dirt_background_4";
            num = 1;
            break;
        case AnimationType::facility_dirt_background_5:
            file = "./Resource/texture/facility_dirt_background_5";
            num = 1;
            break;
        case AnimationType::facility_dirt_background_6:
            file = "./Resource/texture/facility_dirt_background_6";
            num = 1;
            break;
        case AnimationType::facility_dirt_background_7:
            file = "./Resource/texture/facility_dirt_background_7";
            num = 1;
            break;
        case AnimationType::facility_dirt_background_8:
            file = "./Resource/texture/facility_dirt_background_8";
            num = 1;
            break;

        case AnimationType::facility_dirt_solid_1:
            file = "./Resource/texture/facility_dirt_solid_1";
            num = 1;
            break;
        case AnimationType::facility_dirt_solid_2:
            file = "./Resource/texture/facility_dirt_solid_2";
            num = 1;
            break;
        case AnimationType::facility_dirt_solid_3:
            file = "./Resource/texture/facility_dirt_solid_3";
            num = 1;
            break;

        case AnimationType::facility_soil_cracked_1:
            file = "./Resource/texture/facility_soil_cracked_1";
            num = 1;
            break;
        case AnimationType::facility_soil_cracked_2:
            file = "./Resource/texture/facility_soil_cracked_2";
            num = 1;
            break;
        case AnimationType::facility_soil_cracked_3:
            file = "./Resource/texture/facility_soil_cracked_3";
            num = 1;
            break;
        case AnimationType::facility_soil_cracked_4:
            file = "./Resource/texture/facility_soil_cracked_4";
            num = 1;
            break;

        case AnimationType::facility_water_clean:
            file = "./Resource/texture/facility_water_clean";
            num = 1;
            break;
        case AnimationType::facility_water_clean_top:
            file = "./Resource/texture/facility_water_clean_top";
            num = 1;
            break;
        case AnimationType::facility_water_blood:
            file = "./Resource/texture/facility_water_blood";
            num = 1;
        case AnimationType::facility_water_blood_top:
            file = "./Resource/texture/facility_water_blood_top";
            num = 1;
            break;
        case AnimationType::facility_water_swamp:
            file = "./Resource/texture/facility_water_swamp";
            num = 1;
            break;
        case AnimationType::facility_water_swamp_top:
            file = "./Resource/texture/facility_water_swamp_top";
            num = 1;
            break;

        case AnimationType::facility_ladder_wooden_1:
            file = "./Resource/texture/facility_ladder_wooden_1";
            num = 1;
            break;
        case AnimationType::facility_ladder_wooden_2:
            file = "./Resource/texture/facility_ladder_wooden_2";
            num = 1;
            break;
        case AnimationType::facility_ladder_wooden_3:
            file = "./Resource/texture/facility_ladder_wooden_3";
            num = 1;
            break;
        case AnimationType::facility_ladder_wooden_4:
            file = "./Resource/texture/facility_ladder_wooden_4";
            num = 1;
            break;
        case AnimationType::facility_ladder_wooden_5:
            file = "./Resource/texture/facility_ladder_wooden_5";
            num = 1;
            break;
        case AnimationType::facility_ladder_wooden_6:
            file = "./Resource/texture/facility_ladder_wooden_6";
            num = 1;
            break;


            //projectile
        case AnimationType::projectile_chop:
            file = "./Resource/texture/projectile_chop";
            num = 5;
            break;
        case AnimationType::projectile_little_magic_ball:
            file = "./Resource/texture/projectile_little_magic_ball";
            num = 4;
            break;
        case AnimationType::projectile_little_slime_ball:
            file = "./Resource/texture/projectile_little_slime_ball";
            num = 2;
            break;

            //particle
        case AnimationType::particle_goldust:
            file = "./Resource/texture/particle_goldust";
            num = 5;
            break;
        case AnimationType::particle_poisoned:
            file = "./Resource/texture/particle_poisoned";
            num = 6;
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
            //SDL_BlendMode a;
            //SDL_GetTextureBlendMode(texture, &a);
            //SDL_Log("BlendMode %d", a);

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
#ifdef _DEBUG
	if(num>=L->size())
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"RenderingSystem::getAnimation超出范围");
        return nullptr;
    }
#endif
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