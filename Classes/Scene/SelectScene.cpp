#include "SelectScene.h"
#include "HelloWorldScene.h"
#include "AchieveScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

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

	//노티피케이션 추카
	//CCNotificationCenter::sharedNotificationCenter()->addObserver(this, SEL_CallFuncO(&SelectScene::doNotification), "notification", NULL);
	//"notification"이라는 메시지가 오면 해당 함수를 실행한다.

	return true;
}

void SelectScene::initButton()
{
	SelectLayer = CSLoader::createNode("Scene/SelectScene/SelectSceneLayer.csb");

	addChild(SelectLayer);

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

SelectScene::~SelectScene()
{
	log("SelectScene :: dealloc");
}

void SelectScene::onMouseDown(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	log("Mouse Down");
}

void SelectScene::doTutorialScene(Ref* pSender)
{
	log("Tutorial");

}

void SelectScene::doStartScene(Ref* pSender)
{
	// Call New Game
	log("Start Scene");

	auto pScene = HelloWorld::createScene();
	Director::getInstance()->pushScene(pScene);
	
}

void SelectScene::doContinueScene(Ref* pSender)
{
	// Call last play
	log("Continue Scene");
	/*
	auto pScene = TestScene2::createScene();
	Director::getInstance()->pushScene(pScene);
	*/
}

void SelectScene::doAchieveScene(Ref* pSender)
{
	// Call Acheieve Scene
	log("Achieve Scene");
	auto pScene = AchieveScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}

void SelectScene::doExit(Ref* pSender)
{
	// Call Exit Dialog
	log("Exit");

	Popup_Call(CSLoader::createNode("Popup/MenuPopup/MenuPopupLayer.csb"));
	Popup_setButton("btn_ok", 1);
	Popup_setButton("btn_cancel", 2);
}

/*
Call popupLayer and pause SelectLayer
popupLayer : popupLayer which made Cocos Studio
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

// Close Popup
void SelectScene::Popup_Close()
{
	removeChild(pLayer, true);
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(SelectLayer, true);
}

void SelectScene::Popup_setButton(const std::string &name, const int tag)
{
	Button* pButton = static_cast<Button*>(pLayer->getChildByName(name));
	pButton->setTag(tag);
	pButton->addTouchEventListener(CC_CALLBACK_2(SelectScene::Popup_onBtnClickCallbackFnc, this));
}

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

void SelectScene::Popup_Callback(Ref* pSender)
{
	if (pSelect == 1)
	{
		log("1");
		//닫기 버튼 이다~~
	}
	else if (pSelect == 2)
	{
		log("2");
		//헬프 버튼이다~~
	}

	Popup_Close();
}

void SelectScene::doClose(Ref* pSender)
{
	Director::getInstance()->popScene();
	//    Director::getInstance()->popToRootScene();
}

void SelectScene::menuCloseCallback(Ref *pSender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		Director::getInstance()->end();
		break;
	case ui::Widget::TouchEventType::MOVED:
		// TODO
		break;
	case ui::Widget::TouchEventType::ENDED:
		// TODO
		break;
	case ui::Widget::TouchEventType::CANCELED:
		// TODO
		break;
	default:
		// TODO
		break;
	}
}