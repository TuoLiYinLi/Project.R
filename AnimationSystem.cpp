#include "AnimationSystem.h"
#include "Defined.h"
#include "GlobalData.h"
AnimationSystem* AnimationSystem::getInstance()
{
    if (instance == nullptr) {
        auto a = new AnimationSystem();
        if (a==nullptr) {
#ifdef _DEBUG
            std::cout << "\t\tERROR:AnimationSystem::new AnimationSystem()�����ڴ�ʧ�ܣ�ֵΪnullptr\n";
#endif // _DEBUG
        }
        instance = a;
    }
    return instance;
}

void AnimationSystem::destroyInstance()
{
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
    return;
}

/*
AnimationUnit* AnimationSystem::addAnimUnit()
{
    AnimationUnit* au = AnimationUnit::createNew();
    animUnitList->push_back(au);
    
    return au;
}
*/

void AnimationSystem::removeAnimUnit(AnimationUnit* _animUnit)
{
    animUnitList->remove(_animUnit);
    _animUnit->destroy();
}

/*
TTFUnit* AnimationSystem::addTTFUnit(const char* msg, SDL_Color color)
{
    TTFUnit* tu = TTFUnit::createNew(msg, color);
    fontUnitList->push_back(tu);
    return tu;
}
*/

void AnimationSystem::removeTTFUnit(TTFUnit* _TTFUnit)
{
    fontUnitList->remove(_TTFUnit);
    _TTFUnit->destroy();
}

AnimationSystem::AnimationSystem()
{
#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << "AnimationSystem::AnimationSystem()\n";
#endif // ANIMATION_SYSTEM_DEBUG

    windowHeight = WINDOW_HEIGHT;
    windowWidth = WINDOW_WIDTH;

    viewX = 0;
    viewY = 0;
    viewScale = 1;

    vy = 0;
    vx = 0;
    vs = 0;
    
    //��Ⱦ��Դ�б�
    animList = new std::vector<std::vector<SDL_Texture*>*>();
    if (animList == nullptr) {
#ifdef _DEBUG
        std::cout << "\t\tERROR:new std::vector<SDL_Texture*>()�����ڴ�ʧ�ܣ�ֵΪnullptr\n";
#endif // _DEBUG
    }
    loadAllAnim();

    //��Ⱦ��Ԫ�б�
    animUnitList = new std::list<AnimationUnit*>();
    if (animUnitList == nullptr) {
#ifdef _DEBUG
        std::cout << "\t\tERROR:new std::vector<AnimationUnit*>()�����ڴ�ʧ�ܣ�ֵΪnullptr\n";
#endif // _DEBUG
    }
    //���嵥Ԫ�б�
    fontUnitList = new std::list<TTFUnit*>();
    //GlobalData::font = TTF_OpenFont("./Resource/ttf/Zpix.ttf",FONT_PRECISION);
}

AnimationSystem::~AnimationSystem()
{
#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << "AnimationSystem::~AnimationSystem()\n";
#endif // ANIMATION_SYSTEM_DEBUG

#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << "\t\t��Ծ��TTFUnit����:"<< TTFUnit::getCurrentNum() 
        <<"\n\t\t��Ծ��AnimationUnit����:"<< AnimationUnit::getCurrentNum() <<"\n";
#endif // ANIMATION_SYSTEM_DEBUG

    int count = 0;
    for (auto it = animUnitList->begin(); it != animUnitList->end(); it++)
    {
        if ((*it) != nullptr) {
            (*it)->destroy();
            (*it) = nullptr;
            count++;
        }
    }
#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << "\t\t�Ѿ��ͷ�" << count << "��AnimationUnit\n";
#endif // ANIMATION_SYSTEM_DEBUG
    delete animUnitList;
    animUnitList = nullptr;
    count = 0;
    for (auto it = fontUnitList->begin(); it != fontUnitList->end(); it++)
    {
        if ((*it) != nullptr) {
            (*it)->destroy();
            (*it) = nullptr;
            count++;
        }
    }
#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << "\t\t�Ѿ��ͷ�" << count << "��TTFUnit\n";
#endif // ANIMATION_SYSTEM_DEBUG
    delete fontUnitList;
    fontUnitList = nullptr;

    unloadAllAnim();
    delete animList;
    animList = nullptr;
    
    //TTF_CloseFont(GlobalData::font);
}

void AnimationSystem::updateWindow()
{
    //std::cout << vx << "," << vy << "\n";
    
    double s1 = 1 / viewScale;
    viewX += GlobalData::delta_time * vx / 1000 * s1;
    viewY += GlobalData::delta_time * vy / 1000 * s1;
    viewScale += GlobalData::delta_time * vs / 1000;
    
    if (viewScale > MAX_VIEW_SCALE) viewScale = MAX_VIEW_SCALE;
    if (viewScale < MIN_VIEW_SCALE)viewScale = MIN_VIEW_SCALE;

    double axt = GlobalData::delta_time * double(VIEW_ACCELERATE_SPEED_X) / 1000;
    double ayt = GlobalData::delta_time * double(VIEW_ACCELERATE_SPEED_Y) / 1000;
    double ast = GlobalData::delta_time * double(VIEW_ACCELERATE_SPEED_SCALE) / 1000;
    
    if (vx>0) {
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
    
    if (vs>0) {
        vs -= ast;
        if (vs < 0) vs = 0;
    }
    else
    {
        vs += ast;
        if (vs > 0) vs = 0;
    }
    

}

void AnimationSystem::renderOneUnit(AnimationUnit* au) {
    SDL_Texture* texture= getTextureFromAU(au);

    SDL_Rect rect;


    rect.x = round(((au->x - viewX) * 32 + au->deltaX * 2) * viewScale - (viewScale - 1) * windowWidth * 0.5);
    rect.y = round(((au->y - viewY) * 32 + au->deltaY * 2) * viewScale - (viewScale - 1) * windowHeight * 0.5);
    rect.w = ceil(au->width * viewScale);
    rect.h = ceil(au->height * viewScale);

    if (rect.x<-rect.w * 1.21 || rect.x>WINDOW_WIDTH + rect.w * 0.21 ||
        rect.y<-rect.h * 1.211 || rect.y>WINDOW_HEIGHT + rect.h * 0.21) {
#ifdef ANIMATION_RENDER_DEBUG
        //std::cout << "\t\t����һ��������Χ����ȾĿ��\n";
#endif // ANIMATION_SYSTEM_DEBUG
        return;
    }

    SDL_RenderCopyEx(GlobalData::sdl_renderer, texture, NULL, &rect, au->angle, NULL, au->flip);
}

void AnimationSystem::renderOneUnit(TTFUnit* tu)
{
    SDL_Rect rect;
    rect.x = round((tu->world_x - viewX) * 32  * viewScale - (viewScale - 1) * windowWidth * 0.5);
    rect.y = round((tu->world_y - viewY) * 32  * viewScale - (viewScale - 1) * windowHeight * 0.5);
    rect.w = ceil(double(tu->w) / FONT_PRECISION * FONT_SIZE * viewScale * tu->scale);
    rect.h = ceil(double(tu->h) / FONT_PRECISION * FONT_SIZE * viewScale * tu->scale);
    //std::cout <<"Text Size " << tu->w<< "," << tu->h << "\n";
    SDL_RenderCopy(GlobalData::sdl_renderer, tu->texture, NULL, &rect);
}

void AnimationSystem::renderAll() {
#ifdef ANIMATION_RENDER_DEBUG
    std::cout << "AnimationSystem::renderAll()\n";
#endif // ANIMATION_SYSTEM_DEBUG
    unsigned short currentDeepth = 0;
    unsigned short maxDeepth = 0;
    unsigned short nextDeepth = 65535;
    
    int auNum = 0;
    int tuNum = 0;

    for (auto i = animUnitList->begin(); i !=animUnitList->end(); i++)
    {
        int targetDeepth=(*i)->depth;

        if (targetDeepth == currentDeepth) 
        {
            renderOneUnit(*i);
#ifdef ANIMATION_RENDER_DEBUG
            //std::cout << "\t\t��Ⱦ��"<< auNum <<"��animationUnit\n";
#endif // ANIMATION_SYSTEM_DEBUG
        }
        if (targetDeepth > currentDeepth) 
        {
            if (targetDeepth > maxDeepth) 
            { 
                maxDeepth = targetDeepth; 
            }
            if (targetDeepth < nextDeepth) 
            {
                nextDeepth = targetDeepth;
            }
        }

        auNum++;
    }
    for (auto i = fontUnitList->begin(); i != fontUnitList->end(); i++)
    {
        int targetDeepth = (*i)->depth;

        if (targetDeepth == currentDeepth)
        {
            renderOneUnit(*i);
#ifdef ANIMATION_RENDER_DEBUG
            //std::cout << "\t\t��Ⱦ��" << tuNum << "��animationUnit\n";
#endif // ANIMATION_SYSTEM_DEBUG
        }
        if (targetDeepth > currentDeepth)
        {
            if (targetDeepth > maxDeepth)
            {
                maxDeepth = targetDeepth;
            }
            if (targetDeepth < nextDeepth)
            {
                nextDeepth = targetDeepth;
            }
        }

        tuNum++;
}
#ifdef ANIMATION_RENDER_DEBUG
    std::cout << "\t\tmaxDeepth:" << maxDeepth << "\n";
#endif // ANIMATION_SYSTEM_DEBUG
    while (true)
    {
        currentDeepth = nextDeepth;
        nextDeepth = maxDeepth;
        auNum = 0;

        for (auto i = animUnitList->begin(); i != animUnitList->end(); i++)
        {
            int targetDeepth = (*i)->depth;

            if (targetDeepth == currentDeepth)
            {
                renderOneUnit(*i);
#ifdef ANIMATION_RENDER_DEBUG
                //std::cout << "\t\tanimUnit@" << auNum << "\n";
#endif // ANIMATION_SYSTEM_DEBUG
            }
            if (targetDeepth > currentDeepth)
            {
                    
                if (targetDeepth < nextDeepth)
                {
                    nextDeepth = targetDeepth;
                }
            }
            auNum++;
        }
        tuNum = 0;
        for (auto i = fontUnitList->begin(); i != fontUnitList->end(); i++)
        {
            int targetDeepth = (*i)->depth;

            if (targetDeepth == currentDeepth)
            {
                renderOneUnit(*i);
#ifdef ANIMATION_RENDER_DEBUG
                //std::cout << "\t\tttfUnit@" << tuNum << "\n";
#endif // ANIMATION_SYSTEM_DEBUG
            }
            if (targetDeepth > currentDeepth)
            {

                if (targetDeepth < nextDeepth)
                {
                    nextDeepth = targetDeepth;
                }
            }
            tuNum++;
        }

        if (currentDeepth == maxDeepth) {
            break;
        }
    }
}

void AnimationSystem::loadAllAnim() {
#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << "AnimationSystem::loadAllAnim()\n";
#endif // ANIMATION_SYSTEM_DEBUG
    for (auto i = 0; i<int(AnimType::size); i++)
    {
        loadAnim(AnimType(i));
    }
}

void AnimationSystem::unloadAllAnim() {
    for (auto i = 0; i<int(AnimType::size); i++)
    {
        if (animList->at(i)!=nullptr) {
            unloadAnim(AnimType(i));
        }
    }
}

SDL_Texture* AnimationSystem::getTextureFromAU(AnimationUnit* au) {
#ifdef ANIMATION_RENDER_DEBUG
    //std::cout << "AnimationSystem::getTextureFromAU(AnimationUnit* au)\n";
#endif // ANIMATION_RENDER_DEBUG
    if (au->animProgress >= animList->at(int(au->type))->size()) {
        std::cout << "\t\tERROR:AnimationSystem::getTextureFromAU ������Χ\n";
    }

    return animList->at(int(au->type))->at(au->animProgress);
}

void AnimationSystem::loadAnim(AnimType antp) {
#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << "AnimationSystem::loadAnim(AnimType antp)\n";
#endif // ANIMATION_SYSTEM_DEBUG
    if (int(antp) >= int(AnimType::size)) {
#ifdef _DEBUG
        std::cout << "\t\tERROR:int(AnimType)����AnimType��Χ\n";
#endif // _DEBUG
        return;
    }


    if (animList->size()==int(antp)) {
#ifdef ANIMATION_SYSTEM_DEBUG
        std::cout << "\t\t���ض���:" << int(antp) << "\n";
#endif // ANIMATION_SYSTEM_DEBUG
        std::string file = "";
        int num = 0;
        switch (antp)
        {
        case AnimType::Default:
            file = "./Resource/texture/Default";
            num = 1;
            break;
        case AnimType::charaSlimeIdle:
            file = "./Resource/texture/SlimeIdle";
            num = 4;
            break;
        case AnimType::charaSlimeMove:
            file = "./Resource/texture/SlimeMove";
            num = 4;
            break;
        case AnimType::charaSlimeBasic:
            file = "./Resource/texture/SlimeEject";
            num = 4;
            break;
        case AnimType::charaSlimeSpecial:
            file = "./Resource/texture/SlimeAbsorb";
            num = 7;
            break;
        case AnimType::charaSlimeDeath:
            file = "./Resource/texture/SlimeDeath";
            num = 9;
            break;
        case AnimType::charaWarriorMiner1_idle:
            file = "./Resource/texture/miner1-idle";
            num = 4;
            break;
        case AnimType::charaWarriorMiner1_walk:
            file = "./Resource/texture/miner1-walk";
            num = 8;
            break;
        case AnimType::charaWarriorMiner1_dig:
            file = "./Resource/texture/miner1-dig";
            num = 4;
            break;
        case AnimType::charaWarriorMiner1_death:
            file = "./Resource/texture/miner1-death";
            num = 9;
            break;
        case AnimType::gridDirt_1a:
            file = "./Resource/texture/Dirt_a_t1";
            num = 1;
            break;
        case AnimType::gridDirt_1n:
            file = "./Resource/texture/Dirt_n_t1";
            num = 1;
            break;
        case AnimType::gridDirdCracked:
            file = "./Resource/texture/Dirt_Cracked";
            num = 1;
            break;
        case AnimType::gridDirtStair_1L:
            file = "./Resource/texture/Dirt_stairL_t1";
            num = 1;
            break;
        case AnimType::gridDirtStair_1R:
            file = "./Resource/texture/Dirt_stairR_t1";
            num = 1;
            break;
        case AnimType::gridDirtStair_1B:
            file = "./Resource/texture/Dirt_stairB_t1";
            num = 1;
            break;
        case AnimType::gridDirtClimb_L_t1:
            file = "./Resource/texture/DirtClimb_Lt1";
            num = 1;
            break;
        case AnimType::gridDirtClimb_L_t2:
            file = "./Resource/texture/DirtClimb_Lt2";
            num = 1;
            break;
        case AnimType::gridGrass_h4:
            file = "./Resource/texture/Grass_h4";
            num = 1;
            break;
        case AnimType::gridDirtButton_1:
            file = "./Resource/texture/Dirt_a_button_t1";
            num = 1;
            break;
        case AnimType::gridWater_1full:
            file = "./Resource/texture/Water_full_t1";
            num = 1;
            break;
        case AnimType::gridWater_1upper:
            file = "./Resource/texture/Water_upper_t1";
            num = 1;
            break;
        case AnimType::ladder:
            file = "./Resource/texture/Ladder_L";
            num = 1;
            break;
        case AnimType::ropeHead:
            file = "./Resource/texture/RopeHeadR";
            num = 1;
            break;
        case AnimType::rope1:
            file = "./Resource/texture/Rope1R";
            num = 1;
            break;
        case AnimType::rope2:
            file = "./Resource/texture/Rope2R";
            num = 1;
            break;
        case AnimType::ropeTail:
            file = "./Resource/texture/RopeTailR";
            num = 1;
            break;
        case AnimType::faciSlimeGlue_L1:
            file = "./Resource/texture/SlimeGlue_L1";
            num = 1;
            break;
        case AnimType::chopDown:
            file = "./Resource/texture/chopDown";
            num = 5;
            break;
        case AnimType::slimeBall:
            file = "./Resource/texture/slimeBall";
            num = 2;
            break;
        case AnimType::particle_goldust:
            file = "./Resource/texture/goldust";
            num = 5;
            break;
        default:
#ifdef ANIMATION_SYSTEM_DEBUG
            std::cout << "\t\tERROR:����AnimType����\n";
#endif // ANIMATION_SYSTEM_DEBUG
            throw antp;
            break;
        }
#ifdef ANIMATION_SYSTEM_DEBUG
        std::cout << "\t\t��������:"<<num<<"\n";
#endif // ANIMATION_SYSTEM_DEBUG
        auto innerList = new std::vector<SDL_Texture*>();
        if (innerList == nullptr) {
            std::cout << "\t\tERROR:���ز����ڴ治��\n";
            return;
        }
        animList->push_back(innerList);

        

        for (auto i = 1; i <= num; i++)
        {
            std::string fullFile;
            if (num>1) {
                fullFile = file + std::to_string(i) + std::string(".png");
            }
            else
            {
                fullFile = file + std::string(".png");
            }
            auto c_fullFile = fullFile.c_str();
            SDL_Texture* texture= IMG_LoadTexture(GlobalData::sdl_renderer, c_fullFile);
            if (texture != nullptr) {
#ifdef ANIMATION_SYSTEM_DEBUG
                std::cout << "\t\t�ɹ�����"<<c_fullFile<<"\n";
#endif // ANIMATION_SYSTEM_DEBUG
            }
            else
            {
#ifdef ANIMATION_SYSTEM_DEBUG
                std::cout << "\t\tERROR:�޷�����" << c_fullFile << "\n";
#endif // ANIMATION_SYSTEM_DEBUG
            }

            innerList->push_back(texture);
        }
    }
    else
    {
#ifdef ANIMATION_SYSTEM_DEBUG
        std::cout << "\t\tERROR:�Ѿ������˶���"<< int(antp) <<"�������ظ�����\n";
#endif // ANIMATION_SYSTEM_DEBUG
        return;
    }
}

void AnimationSystem::unloadAnim(AnimType antp) {
#ifdef ANIMATION_SYSTEM_DEBUG
    std::cout << "unloadAnim(AnimType antp)\n";
    std::cout << "\t\tж�ض���:" << int(antp) << "\n";
#endif // ANIMATION_SYSTEM_DEBUG
    std::vector<SDL_Texture*>* ap=animList->at(int(antp));
    if (animList->at(int(antp)) == nullptr) {
#ifdef ANIMATION_SYSTEM_DEBUG
        std::cout << "\t\tERROR:����" << int(antp) << "��û�б����أ�����ж��\n";
#endif // ANIMATION_SYSTEM_DEBUG
        return;
    }
    else
    {
        int textureCount = 0;
        for (auto it = ap->begin(); it!=ap->end() ; it++)
        {
            textureCount++;
            if ((*it) == nullptr) {
#ifdef ANIMATION_SYSTEM_DEBUG
                std::cout << "\t\tERROR:��������ĵ�"<<textureCount<<"��SDL_Texture*Ϊnullptr,������ع���\n";
#endif // ANIMATION_SYSTEM_DEBUG
            }
            else 
            {
                SDL_DestroyTexture(*it);
                (*it) = nullptr;
#ifdef ANIMATION_SYSTEM_DEBUG
                std::cout << "\t\t���ж�ص�"<< textureCount <<"��SDL_Texture\n";
#endif // ANIMATION_SYSTEM_DEBUG
            }

        }
        delete animList->at(int(antp));
        animList->at(int(antp)) = nullptr;
    }
}

AnimationSystem* AnimationSystem::instance = nullptr;
