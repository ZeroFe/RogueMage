#ifndef UI_PopupWindowBase_h
#define UI_PopupWindowBase_h

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

typedef std::function<void(Ref*)> HK_PopupCallback; //�ݹ鿡�� ���ڸ� �ϳ��� ������
typedef std::function<void(Ref*, int)> HK_PopupCallback2;//�ݹ鿡�� ���ڸ� �ΰ� ������

class UI_PopupWindowBase : public cocos2d::Layer
{
public:
	UI_PopupWindowBase(void);
	virtual ~UI_PopupWindowBase(void);

	CREATE_FUNC(UI_PopupWindowBase);    //�⺻ create()�Լ� ����

	virtual bool init()final;   //�ʱ�ȭ �Լ��� �ٽ� �������̵� �����ʰ�  �ʱ�ȭ�ڸ� �����ϰ����Ѵٸ� onInit() �Լ��� �������̵�����
	virtual bool onInit();

	void setCallBackFunc(const HK_PopupCallback& callback); //�ݹ� �Լ���� �Լ�
	void setCallBackFunc2(const HK_PopupCallback2& callback);//�ݹ� �Լ���� �Լ� (���ڸ� �ΰ� �������ִ�)

	virtual void    showPopup(cocos2d::Layer  *pParrentLayer);    //�˾�â�� ����
	virtual void    closePopup();

	int    getResult()const { return m_nResult; }  //�˾� Ŭ�����ۿ����� ����Ʈ����
protected:

	virtual void    onCallBackFunc()final;   //�ݹ� �Լ� ����
protected:
	HK_PopupCallback m_callback; //�ݹ�
	HK_PopupCallback2 m_callback2; //�ݹ�


	int m_nResult;      //��ư�̳� ��� ���ۿ� ���� ������ �����̴� (��: 0= ��ҹ�ư Ŭ����, 1= Ȯ�� ��ư Ŭ����.....)

	cocos2d::Layer *m_ParrentLayer;    //�θ� Layer => �˾��� �׻� Layer�� �θ� �������Ѵ�. ���� �θ� Layer�� �ƴѰ�� �׳� Null�� �����Ұ�

};
#endif
