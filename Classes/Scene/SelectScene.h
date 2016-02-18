#ifndef __SceneTrans__SelectScene__
#define __SceneTrans__SelectScene__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class SelectScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void initButton();

	CREATE_FUNC(SelectScene);

	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
	virtual void onExit();
	~SelectScene(void);

	// 마우스 리스너 설정
	void onMouseDown(cocos2d::Event *e);
	void onMouseUp(cocos2d::Event *e) {};
	void onMouseMove(cocos2d::Event *e) {};
	void onMouseScroll(cocos2d::Event *e) {};

	// 각 버튼별 기능 설정(장면전환 및 종료)
	void doTutorialScene(Ref* pSender);
	void doStartScene(cocos2d::Ref* pSender);
	void doContinueScene(cocos2d::Ref* pSender);
	void doAchieveScene(cocos2d::Ref* pSender);
	void doExit(cocos2d::Ref* pSender);

	// 팝업 관련 함수
	void Popup_Call(Node* popupLayer);
	void Popup_Close();
	void Popup_setButton(const std::string &name, const int tag);
	void Popup_onBtnClickCallbackFnc(Ref *pSender, ui::Widget::TouchEventType touchType);
	void Popup_Callback(Ref* pSender);

private:
	Node *SelectLayer;
	Node *pLayer;
	int pSelect;
};

#endif /* defined(__SceneTrans__SelectScene__) */