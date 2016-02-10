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

	m_nResult = 0;    //리턴될 예비 맴버변수 팝업에 있는 버튼이나 이벤트에서 어떤 버튼이 클릭됬는지 혹은 다른 인자에 대한 리턴해줄 정보 입니다.
	m_ParrentLayer = NULL; //부모 Node
	onInit();   //초기화 함수

	return true;
}

bool UI_PopupWindowBase::onInit()
{
	return true;
}

void UI_PopupWindowBase::setCallBackFunc(const HK_PopupCallback& callback)
{
	m_callback = callback; //콜백함수에서 인자가 하나인 콜백 인스턴스 설정
}


void UI_PopupWindowBase::setCallBackFunc2(const HK_PopupCallback2& callback)
{
	m_callback2 = callback;//콜백함수에서 인자가 둘인 콜백 인스턴스 설정
}


void UI_PopupWindowBase::showPopup(cocos2d::Layer *pParrentLayer)    //팝업창을 띄운다
{
	//팝업을 생성하고 실제로 화면에 보이개할때 부모 Layer는 이벤트를 못받도록 설정
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
	//팝업창을 닫고자할때 필히 호출할것

	setTouchEnabled(false);

	if (m_ParrentLayer) {
		m_ParrentLayer->setTouchEnabled(true);
	}

	removeAllChildren();
	removeFromParent();
}

void UI_PopupWindowBase::onCallBackFunc()   //콜백 함수 실행
{
	//함수콜백 실행
	if (m_callback)
		m_callback(this);
	if (m_callback2) {
		m_callback2(this, m_nResult);
	}
}