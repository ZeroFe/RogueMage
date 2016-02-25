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

// �θ��̾� ����
void UI_Popup::setParentLayer(Node* pLayer)
{
	if (!pLayer) return;
	parentLayer = pLayer;
}

// �˾����̾� ����
void UI_Popup::setPopupLayer(Node* pLayer)
{
	if (!pLayer) return;
	popupLayer = pLayer;
}

/*
��ư ���� ����
name : ���ڽ� ��Ʃ������� ������ ��ư�� �̸�
tag : �����ϰ� ���� ��ư�� �±�
*/
void UI_Popup::setButton(const std::string &name, const int tag)
{
	Button* pButton = static_cast<Button*>(popupLayer->getChildByName(name));
	pButton->setTag(tag);
	pButton->addTouchEventListener(CC_CALLBACK_2(UI_Popup::onBtnCallbackFunc, this));
}

// Ŭ�������� �θ� �Լ� ����
void UI_Popup::setCallbackFunc(const popupCallback &callback)
{
	pCallback = callback;
}

// �˾� �±� �ҷ�����(��ư �±� �������� if�� © ��)
int UI_Popup::getBtnTag()
{
	return btnTag;
}

// �˾����̾ �ҷ����� �θ��̾� ����
void UI_Popup::call()
{
	popupLayer->setAnchorPoint(Vec2(0.5, 0.5));
	popupLayer->setPosition(Global::screenSizeX / 2, Global::screenSizeY / 2);
	// Need define popupLayer Zorder variable
	parentLayer->addChild(popupLayer, POPUP_ZORDER);
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(parentLayer, true);
}

// �˾� �ݱ�
void UI_Popup::close()
{
	parentLayer->removeChild(popupLayer, true);
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(parentLayer, true);
}

// �˾� ��ư �ݹ��Լ� ����
void UI_Popup::onBtnCallbackFunc(Ref *pSender, ui::Widget::TouchEventType touchType)
{
	if (touchType == ui::Widget::TouchEventType::ENDED)
	{
		btnTag = ((Button*)pSender)->getTag();
		onCallbackFunc();
	}
}

// �Լ� �θ���
void UI_Popup::onCallbackFunc()
{
	if (pCallback)
		pCallback(parentLayer);
}