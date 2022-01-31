#include <string>
#include "Defined.h"
#include "GlobalData.h"

#include "RenderingSystem.h"

#include "PhysicsObject.h"
#include "PhysicsChara.h"
#include "PhysicsFacility.h"
#include "PhysicsProjectile.h"

#include "WorldSystem.h"

RenderingSystem* RenderingSystem::getInstance()
{
    if (instance == nullptr) {
        auto a = new RenderingSystem();
        if (a == nullptr) {
#ifdef _DEBUG
            SDL_Log(u8"���� RenderingSystem::new RenderingSystem()�����ڴ�ʧ�ܣ�ֵΪnullptr");
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

    //��Ⱦ��Դ�б�
    list_animation_texture = new std::vector<std::vector<SDL_Texture*>*>();
    if (list_animation_texture == nullptr) {
#ifdef _DEBUG
        SDL_Log(u8" ERROR:new std::vector<SDL_Texture*>()�����ڴ�ʧ�ܣ�ֵΪnullptr");
#endif // _DEBUG
    }
    loadAllAnimation();

    //��Ⱦ��Ԫ�б�
    list_rendering_units = new std::list<RenderingUnit*>();
    if (list_rendering_units == nullptr) {
#ifdef _DEBUG
        SDL_Log(u8"ERROR:new std::vector<RenderingAnimation*>()�����ڴ�ʧ�ܣ�ֵΪnullptr");
#endif // _DEBUG
    }


}

RenderingSystem::~RenderingSystem()
{
#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << "RenderingSystem::~RenderingSystem()\n";
#endif // ANIMATION_SYSTEM_DEBUG

#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << " ��Ծ��TTFUnit����:" << TTFUnit::getRenderingUnitNum()
        << "\n ��Ծ��AnimationUnit����:" << RenderingAnimation::getRenderingUnitNum() << "\n";
#endif // ANIMATION_SYSTEM_DEBUG

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
    double s1 = 1 / viewScale;
    viewX += GlobalData::getTimeDelta() * vx / 1000 * s1;
    viewY += GlobalData::getTimeDelta() * vy / 1000 * s1;
    viewScale += GlobalData::getTimeDelta() * vs * viewScale / 1000;

    if (viewScale > VIEW_SCALE_MAX) viewScale = VIEW_SCALE_MAX;
    if (viewScale < VIEW_SCALE_MIN)viewScale = VIEW_SCALE_MIN;

    const double axt = GlobalData::getTimeDelta() * double(VIEW_ACCELERATE_SPEED_X) / 1000;
    const double ayt = GlobalData::getTimeDelta() * double(VIEW_ACCELERATE_SPEED_Y) / 1000;
    const double ast = GlobalData::getTimeDelta() * double(VIEW_ACCELERATE_SPEED_SCALE) / 1000;

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
        //std::cout << " ����һ��������Χ����ȾĿ��\n";
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
        //std::cout << " ����һ��������Χ����ȾĿ��\n";
#endif // ANIMATION_SYSTEM_DEBUG
        return;
    }

    SDL_RenderCopyEx(GlobalData::sdl_renderer, texture, nullptr, &rect, 0, nullptr, au->getFlip());
}

void RenderingSystem::sortRenderingUnits() const
{
    list_rendering_units->sort(compareDepth);
}

void RenderingSystem::renderAll() const {
    for (auto i = list_rendering_units->begin(); i != list_rendering_units->end(); i++)
    {
        if((*i)->flag_enable)
        renderOneUnit(*i);
    }
}


void RenderingSystem::loadAllAnimation() {
#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << "RenderingSystem::loadAllAnimation()\n";
#endif // ANIMATION_SYSTEM_DEBUG
    for (auto i = 0; i<int(AnimationType::size); i++)
    {
        loadAnimation(AnimationType(i));
    }
}

void RenderingSystem::unloadAllAnimation() {
    for (auto i = 0; i<int(AnimationType::size); i++)
    {
        if (list_animation_texture->at(i) != nullptr) {
            unloadAnimation(AnimationType(i));
        }
    }
}

void RenderingSystem::loadAnimation(AnimationType antp) {
#ifdef ANIMATION_SYSTEM_DEBUG
    SDL_Log(u8"RenderingSystem::loadAnimation(AnimationType antp)");
#endif // ANIMATION_SYSTEM_DEBUG

    if (int(antp) >= int(AnimationType::size)) {
#ifdef _DEBUG
        SDL_Log(u8"ERROR:int(AnimationType)����AnimType��Χ");
#endif // _DEBUG
        return;
    }

    if (list_animation_texture->size() == unsigned(antp)) {
#ifdef ANIMATION_SYSTEM_DEBUG
        std::cout << " ���ض���:" << int(antp) << "\n";
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
        case AnimationType::physics_debug_layer_facility:
            file = "./Resource/texture/physics_debug_layer_facility";
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

        //��ɫ����
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
            SDL_Log(u8"���� ���ܼ���size");
            break;
        }
#ifdef ANIMATION_SYSTEM_DEBUG
        std::cout << " ��������:" << num << "\n";
#endif // ANIMATION_SYSTEM_DEBUG
        auto innerList = new std::vector<SDL_Texture*>();
        if (innerList == nullptr) {
            SDL_Log(u8" ERROR:���ز����ڴ治��");
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
#ifdef _DEBUG
            if (texture) {
                SDL_Log(u8" �ɹ�����%s", c_fullFile);
            }
            else
            {
                SDL_Log(u8" �޷�����%s", c_fullFile);
            }
#endif

            innerList->push_back(texture);
        }
    }
#ifdef ANIMATION_SYSTEM_DEBUG
    else
    {
        std::cout << " ERROR:�Ѿ������˶���" << int(antp) << "�������ظ�����\n";
        return;
    }
#endif // ANIMATION_SYSTEM_DEBUG
}


SDL_Texture* RenderingSystem::getAnimation(AnimationType _animation_type,unsigned long long num) const
{
    auto L = list_animation_texture->at((int)_animation_type);
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
    return list_animation_texture->at((int)_animation_type)->size();
}



void RenderingSystem::unloadAnimation(AnimationType antp) const {
#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << "unloadAnimation(AnimationType antp)\n";
    std::cout << " ж�ض���:" << int(antp) << "\n";
#endif // ANIMATION_SYSTEM_DEBUG
    std::vector<SDL_Texture*>* ap = list_animation_texture->at(int(antp));
    if (list_animation_texture->at(int(antp)) == nullptr) {
#ifdef ANIMATION_SYSTEM_DEBUG
        std::cout << " ERROR:����" << int(antp) << "��û�б����أ�����ж��\n";
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
                std::cout << " ERROR:��������ĵ�" << textureCount << "��SDL_Texture*Ϊnullptr,������ع���\n";
#endif // ANIMATION_SYSTEM_DEBUG
            }
            else
            {
                SDL_DestroyTexture(*it);
                (*it) = nullptr;
#ifdef ANIMATION_SYSTEM_DEBUG
                std::cout << " ���ж�ص�" << textureCount << "��SDL_Texture\n";
#endif // ANIMATION_SYSTEM_DEBUG
            }

        }
        delete list_animation_texture->at(int(antp));
        list_animation_texture->at(int(antp)) = nullptr;
    }
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
