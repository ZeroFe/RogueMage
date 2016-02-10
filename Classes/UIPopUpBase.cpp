#include "UIPopupBase.h"

UI_PopupWindowBase::UI_PopupWindowBase(void)
{

}

UI_PopupWindowBase::~UI_PopupWindowBase(void)
{

}

bool UI_PopupWindowBase::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//m_callback = NULL;
	//m_callback2 = NULL;

	m_nResult = 0;    //���ϵ� ���� �ɹ����� �˾��� �ִ� ��ư�̳� �̺�Ʈ���� � ��ư�� Ŭ������� Ȥ�� �ٸ� ���ڿ� ���� �������� ���� �Դϴ�.
	m_ParrentLayer = NULL; //�θ� Node
	onInit();   //�ʱ�ȭ �Լ�

	return true;
}

bool UI_PopupWindowBase::onInit()
{
	return true;
}

void UI_PopupWindowBase::setCallBackFunc(const HK_PopupCallback& callback)
{
	m_callback = callback; //�ݹ��Լ����� ���ڰ� �ϳ��� �ݹ� �ν��Ͻ� ����
}


void UI_PopupWindowBase::setCallBackFunc2(const HK_PopupCallback2& callback)
{
	m_callback2 = callback;//�ݹ��Լ����� ���ڰ� ���� �ݹ� �ν��Ͻ� ����
}


void UI_PopupWindowBase::showPopup(cocos2d::Layer *pParrentLayer)    //�˾�â�� ����
{
	//�˾��� �����ϰ� ������ ȭ�鿡 ���̰��Ҷ� �θ� Layer�� �̺�Ʈ�� ���޵��� ����
	m_ParrentLayer = pParrentLayer;
	if (m_ParrentLayer) 
	{
		m_ParrentLayer->setTouchEnabled(false);
		m_ParrentLayer->addChild(this, INT_MAX);
	}
	else
	{
		Director::getInstance()->getRunningScene()->addChild(this, INT_MAX);
	}
	_touchMode = Touch::DispatchMode::ONE_BY_ONE;
	_swallowsTouches = true;

	setTouchEnabled(true);
}

void UI_PopupWindowBase::closePopup()
{
	//�˾�â�� �ݰ����Ҷ� ���� ȣ���Ұ�

	setTouchEnabled(false);

	if (m_ParrentLayer) {
		m_ParrentLayer->setTouchEnabled(true);
	}

	removeAllChildren();
	removeFromParent();
}

void UI_PopupWindowBase::onCallBackFunc()   //�ݹ� �Լ� ����
{
	//�Լ��ݹ� ����
	if (m_callback)
		m_callback(this);
	if (m_callback2) {
		m_callback2(this, m_nResult);
	}
}