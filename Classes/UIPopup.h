#ifndef __UI_Popup__
#define __UI_Popup__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

/*
Popup Ŭ����
�����

popup = new UI_Popup();
popup->setParentLayer(���� �θ��̾�);
popup->setPopupLayer(���� �˾����̾�);
popup->setCallbackFunc(���� �Լ�);
popup->setButton("�̸�", �±�);
popup->call();

���� �Լ��� ���� ����������
{
pSelect = popup->getBtnTag();

if (pSelect == 1){log("1");} ...

popup->close();
}
������ �Լ� ���� ��
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