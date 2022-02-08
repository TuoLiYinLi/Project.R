#pragma once
#include <list>

#include "GameObject.h"
class UIObject :
    public GameObject
{
public:
    static int getUIObjectNum();//��ȡ��ǰ��Ծ��UIObject����

    static UIObject* createNew();

    bool checkColliderEnabled()const;

    void update_depth(float _d)const;

    int collider_x;//��ײ�������
    int collider_y;//��ײ��������
    int collider_w;//��ײ����
    int collider_h;//��ײ��߶�

    void setPosition(int x, int y, int w, int h);

    virtual void onMouseEnter();//���������˲��
    virtual void onMouseExit();//������˳���˲��
    virtual void onMouseDown();//����갴�µ�˲��
    virtual void onMouseUp();//����굯���˲��
    virtual void onMousePressing();//������������ ��������
    virtual void onMouseHanging();//��������� ��������
    virtual void onMouseRoll(bool forward);//��ʹ�ù���
    
protected:
    UIObject();
    ~UIObject()override;

    static int ui_object_num;//��ǰ��Ծ��UIObject����

    int flag_collider_enabled;//��ײ���Ƿ�����
    
};

