#include "UIPopupBase.h"

UIPopupBase::UIPopupBase(void)
{

}

UIPopupBase::~UIPopupBase(void)
{

}

bool UIPopupBase::init()
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

bool UIPopupBase::onInit()
{
	return true;
}

void UIPopupBase::setCallBackFunc(const PopupCallback& callback)
{
	m_callback = callback; //�ݹ��Լ����� ���ڰ� �ϳ��� �ݹ� �ν��Ͻ� ����
}


void UIPopupBase::setCallBackFunc2(const PopupCallback2& callback)
{
	m_callback2 = callback;//�ݹ��Լ����� ���ڰ� ���� �ݹ� �ν��Ͻ� ����
}


void UIPopupBase::showPopup(cocos2d::Layer *pParrentLayer)    //�˾�â�� ����
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

void UIPopupBase::closePopup()
{
	//�˾�â�� �ݰ����Ҷ� ���� ȣ���Ұ�

	setTouchEnabled(false);

	if (m_ParrentLayer) {
		m_ParrentLayer->setTouchEnabled(true);
	}

	removeAllChildren();
	removeFromParent();
}

void UIPopupBase::onCallBackFunc()   //�ݹ� �Լ� ����
{
	//�Լ��ݹ� ����
	if (m_callback)
		m_callback(this);
	if (m_callback2) {
		m_callback2(this, m_nResult);
	}
}