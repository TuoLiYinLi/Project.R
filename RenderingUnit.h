#pragma once
#include "SDL.h"

//ö�� ��Ⱦ�ο�ϵ
enum class RenderingReference
{
	window,//���ڲο�ϵ
	world,//����ο�ϵ
};

//��Ⱦ��Ԫ ������Ԫ
class RenderingUnit
{
public:
	//�����µĶ���Ԫ��
	static class RenderingUnit* createNew();
	//�������Ԫ��
	virtual void destroy() const;

	RenderingReference reference;	//���Ԫ����λ�òο�ϵ

	bool flag_enable;//�Ƿ���Ⱦ
	SDL_Rect* clipping_rect;//���þ���

	float depth;//�����ȾԪ�������,����Ⱦʱ������Ⱦ��С��ȵ�ͼ��

	double x;//��Ⱦ����������λ��
	double y;//��Ⱦ����������λ��

	double deltaX;//��Ⱦʱ��ƫ��λ��Y,��1/16������Ϊ��λ
	double deltaY;//��Ⱦʱ��ƫ��λ��Y,��1/16������Ϊ��λ

	double width;//Ԫ����ʾ�Ŀ��
	double height;//Ԫ����ʾ�ĸ߶�

	void setFlip(bool _val);	//�����Ƿ�ת
	SDL_RendererFlip getFlip() const;	//ȡ���Ƿ�ת

	void setTexture(SDL_Texture* _texture);
	SDL_Texture* getTexture() const; //ȡ�ö�Ӧ����

	static int getRenderingUnitNum();	//��ȡ����ʹ���ڴ����ȾԪ������

	void setClipping(int _x, int _y, int _w, int _h);//���ü���

protected:

	RenderingUnit();
	virtual ~RenderingUnit();

	bool flip;//�Ƿ����ת,һ�㲻��תʱ,��ɫ�泯�ұ�

	SDL_Texture* texture;//���еĲ���

private:
	static int rendering_unit_num;//��¼һ���ж��ٵ���ȾԪ��ռ���ڴ�
};

