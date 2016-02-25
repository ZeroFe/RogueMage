#include "UIPopup.h"
#include "Global.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#define POPUP_ZORDER 1000

USING_NS_CC;
using namespace ui;

UI_Popup::UI_Popup()
{
	parentLayer = NULL;
	popupLayer = NULL;
	btnTag = 0;
}

UI_Popup::~UI_Popup()
{
	parentLayer = NULL;
	popupLayer = NULL;
}

// 부모레이어 설정
void UI_Popup::setParentLayer(Node* pLayer)
{
	if (!pLayer) return;
	parentLayer = pLayer;
}

// 팝업레이어 설정
void UI_Popup::setPopupLayer(Node* pLayer)
{
	if (!pLayer) return;
	popupLayer = pLayer;
}

/*
버튼 정보 설정
name : 코코스 스튜디오에서 설정한 버튼의 이름
tag : 설정하고 싶은 버튼의 태그
*/
void UI_Popup::setButton(const std::string &name, const int tag)
{
	Button* pButton = static_cast<Button*>(popupLayer->getChildByName(name));
	pButton->setTag(tag);
	pButton->addTouchEventListener(CC_CALLBACK_2(UI_Popup::onBtnCallbackFunc, this));
}

// 클래스에서 부를 함수 설정
void UI_Popup::setCallbackFunc(const popupCallback &callback)
{
	pCallback = callback;
}

// 팝업 태그 불러오기(버튼 태그 기준으로 if문 짤 것)
int UI_Popup::getBtnTag()
{
	return btnTag;
}

// 팝업레이어를 불러오고 부모레이어 정지
void UI_Popup::call()
{
	popupLayer->setAnchorPoint(Vec2(0.5, 0.5));
	popupLayer->setPosition(Global::screenSizeX / 2, Global::screenSizeY / 2);
	// Need define popupLayer Zorder variable
	parentLayer->addChild(popupLayer, POPUP_ZORDER);
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(parentLayer, true);
}

// 팝업 닫기
void UI_Popup::close()
{
	parentLayer->removeChild(popupLayer, true);
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(parentLayer, true);
}

// 팝업 버튼 콜백함수 설정
void UI_Popup::onBtnCallbackFunc(Ref *pSender, ui::Widget::TouchEventType touchType)
{
	if (touchType == ui::Widget::TouchEventType::ENDED)
	{
		btnTag = ((Button*)pSender)->getTag();
		onCallbackFunc();
	}
}

// 함수 부르기
void UI_Popup::onCallbackFunc()
{
	if (pCallback)
		pCallback(parentLayer);
}