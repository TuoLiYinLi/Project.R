#pragma once
#include <list>

#include "GameObject.h"
class UIObject :
    public GameObject
{
public:
    static int getUIObjectNum();//获取当前活跃的UIObject数量

    static UIObject* createNew();

    bool checkColliderEnabled()const;

    void update_depth(float _d)const;

    int collider_x;//碰撞箱横坐标
    int collider_y;//碰撞箱纵坐标
    int collider_w;//碰撞箱宽度
    int collider_h;//碰撞箱高度

    void setPosition(int x, int y, int w, int h);

    virtual void onMouseEnter();//当鼠标进入的瞬间
    virtual void onMouseExit();//当鼠标退出的瞬间
    virtual void onMouseDown();//当鼠标按下的瞬间
    virtual void onMouseUp();//当鼠标弹起的瞬间
    virtual void onMousePressing();//当鼠标持续按下 持续触发
    virtual void onMouseHanging();//当鼠标悬浮 持续触发
    virtual void onMouseRoll(bool forward);//当使用滚轮
    
protected:
    UIObject();
    ~UIObject()override;

    static int ui_object_num;//当前活跃的UIObject数量

    int flag_collider_enabled;//碰撞箱是否启用
    
};

