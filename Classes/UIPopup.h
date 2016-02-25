#ifndef __UI_Popup__
#define __UI_Popup__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

/*
Popup 클래스
사용방법

popup = new UI_Popup();
popup->setParentLayer(넣을 부모레이어);
popup->setPopupLayer(넣을 팝업레이어);
popup->setCallbackFunc(넣을 함수);
popup->setButton("이름", 태그);
popup->call();

넣을 함수는 따로 만들어줘야함
{
pSelect = popup->getBtnTag();

if (pSelect == 1){log("1");} ...

popup->close();
}
식으로 함수 만들 것
*/

typedef std::function<void(Ref*)> popupCallback;

class UI_Popup {
public:
	UI_Popup();
	~UI_Popup();

	void setParentLayer(Node* pLayer);
	void setPopupLayer(Node* pLayer);
	void setButton(const std::string &name, const int tag);
	void setCallbackFunc(const popupCallback &callback);

	int getBtnTag();

	void onBtnCallbackFunc(Ref *pSender, ui::Widget::TouchEventType touchType);

	void call();
	void close();
private:
	virtual void onCallbackFunc();
private:
	Node* parentLayer;
	Node* popupLayer;

	int btnTag;

	popupCallback pCallback;
};

#endif 