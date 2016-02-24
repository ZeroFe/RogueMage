#include "SelectScene.h"
#include "GameScene.h"
#include "AchieveScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

SelectScene::~SelectScene()
{
	log("SelectScene :: dealloc");
}

Scene* SelectScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SelectScene::create();

	scene->addChild(layer);

	return scene;
}

bool SelectScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	initButton();

	return true;
}

// 버튼 설정(리스너 설정)
void SelectScene::initButton()
{
	SelectLayer = CSLoader::createNode("Scene/SelectScene/SelectSceneLayer.csb");

	addChild(SelectLayer);

	// 메뉴 버튼들 찾아서 리스너 설정
	Button* MenuButton1 = static_cast<Button*>(SelectLayer->getChildByName("MenuButton1"));
	Button* MenuButton2 = static_cast<Button*>(SelectLayer->getChildByName("MenuButton2"));
	Button* MenuButton3 = static_cast<Button*>(SelectLayer->getChildByName("MenuButton3"));
	Button* MenuButton4 = static_cast<Button*>(SelectLayer->getChildByName("MenuButton4"));
	Button* MenuButton5 = static_cast<Button*>(SelectLayer->getChildByName("MenuButton5"));

	MenuButton1->addTouchEventListener(CC_CALLBACK_1(SelectScene::doTutorialScene, this));
	MenuButton2->addTouchEventListener(CC_CALLBACK_1(SelectScene::doStartScene, this));
	//MenuButton3->addTouchEventListener(CC_CALLBACK_1(SelectScene::doContinueScene, this));
	MenuButton4->addTouchEventListener(CC_CALLBACK_1(SelectScene::doAchieveScene, this));
	//MenuButton5->addTouchEventListener(CC_CALLBACK_1(SelectScene::doOptionScene, this));

	// 나가기 버튼 리스너 설정
	Button* exit = static_cast<Button*>(SelectLayer->getChildByName("Exit"));
	exit->addTouchEventListener(CC_CALLBACK_1(SelectScene::doExit, this));
}

void SelectScene::onEnter()
{
	Layer::onEnter();

	log("SelectScene :: onEnter");
}

void SelectScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();

	log("SelectScene :: onEnterTransitionDidFinish");
}

void SelectScene::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();

	log("SelectScene :: onExitTransitionDidStart");
}

void SelectScene::onExit()
{
	Layer::onExit();

	log("SelectScene :: onExit");
}

// 마우스 리스너 동작 확인
void SelectScene::onMouseDown(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	log("Mouse Down");
}

// 튜토리얼
void SelectScene::doTutorialScene(Ref* pSender)
{
	log("Tutorial");

}

// 새 게임 시작
void SelectScene::doStartScene(Ref* pSender)
{
	// Call New Game
	log("Start Scene");

	auto pScene = GameScene::createScene();
	Director::getInstance()->pushScene(pScene);
}

// 불러오기
void SelectScene::doContinueScene(Ref* pSender)
{
	// Call last play
	log("Continue Scene");
	/*
	auto pScene = TestScene2::createScene();
	Director::getInstance()->pushScene(pScene);
	*/
}

// 업적
void SelectScene::doAchieveScene(Ref* pSender)
{
	// Call Acheieve Scene
	log("Achieve Scene");
	auto pScene = AchieveScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}

// 종료버튼
void SelectScene::doExit(Ref* pSender)
{
	// Call Exit Dialog
	log("Exit");

	Popup_Call(CSLoader::createNode("Popup/MenuPopup/MenuPopupLayer.csb"));
	Popup_setButton("btn_ok", 1);
	Popup_setButton("btn_cancel", 2);
}

/*
popupLayer를 불러오고 SelectLayer 정지
popupLayer : 코코스 스튜디오로 만든 팝업 생성용 레이어(노드)
*/
void SelectScene::Popup_Call(Node* popupLayer)
{
	if (!popupLayer) return;
	pLayer = popupLayer;
	Size size = Director::getInstance()->getWinSize();
	pLayer->setPosition(size.width / 2, size.height / 2);
	// Need define popupLayer Zorder variable
	addChild(pLayer, 100);
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(SelectLayer, true);
}

// 팝업 닫기
void SelectScene::Popup_Close()
{
	removeChild(pLayer, true);
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(SelectLayer, true);
}

// 팝업 버튼 정보 설정
void SelectScene::Popup_setButton(const std::string &name, const int tag)
{
	Button* pButton = static_cast<Button*>(pLayer->getChildByName(name));
	pButton->setTag(tag);
	pButton->addTouchEventListener(CC_CALLBACK_2(SelectScene::Popup_onBtnClickCallbackFnc, this));
}


// 팝업 버튼 콜백함수 설정
void SelectScene::Popup_onBtnClickCallbackFnc(Ref *pSender, ui::Widget::TouchEventType touchType)
{
	if (touchType == ui::Widget::TouchEventType::ENDED)
	{
		pSelect = ((cocos2d::ui::Button*)pSender)->getTag();    //어떤 버튼인지 체크를 위해 버튼에 추가된 Tag를 맴버변수에서 가지고있도록 한다.
		CallFuncN *action = CallFuncN::create(CC_CALLBACK_1(SelectScene::Popup_Callback, this));
		auto replace = Sequence::create(action, nullptr);

		this->runAction(replace);
	}
}

// 팝업 버튼 클릭시 불러오는 함수
void SelectScene::Popup_Callback(Ref* pSender)
{
	// 종료
	if (pSelect == 1)
	{
		log("1");

		Director::getInstance()->end();
	}
	// 취소
	else if (pSelect == 2)
	{
		log("2");
	}

	// 팝업 닫기
	Popup_Close();
}