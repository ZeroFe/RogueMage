#include "SelectScene.h"
#include "HelloWorldScene.h"
#include "AchieveScene.h"
#include "UIPopUP.h"
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
	auto SelectLayer = CSLoader::createNode("Scene/SelectScene/SelectSceneLayer.csb");

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
	auto popup = UIPopup::create(CSLoader::createNode("Popup/MenuPopup/MenuPopupLayer.csb"));
	popup->setCallBackFunc(CC_CALLBACK_1(SelectScene::popupCallback, this));
	popup->setButton("btn_ok", 1);
	popup->setButton("btn_cancel", 2);
	popup->showPopup(this);
}

void SelectScene::doClose(Ref* pSender)
{
	Director::getInstance()->popScene();
	//    Director::getInstance()->popToRootScene();
}

void SelectScene::popupCallback(Ref* pSender)
{
	UIPopup *pPopup = (UIPopup *)pSender; //현재 팝업에 대한 클래스로 캐스팅 

													  // 여기에서 콜백 받을때 어떤 버튼이 클릭됐는지 알수있으면 좋겠죠?
	int nTag = pPopup->getResult();
	//혹은 콜백을 다르게 선업하셔도 됩니다. 그건 여러분 몫으로 콜백2 있으니 참고해서 만드심 됍니다
	if (nTag == 1)
	{
		log("1");
		//닫기 버튼 이다~~
	}
	else if (nTag == 2)
	{
		log("2");
		//헬프 버튼이다~~
	}


	pPopup->closePopup(); //팝업을 닫습니다. !! 팝업을 닫을시 필히 호출해주세요 이거 안해주면 팝업창 안사라집니다.  
}

/*
void SelectScene::doNotification(CCObject *obj)
{
	//노티피케이션 받기
	CCString *pParam = (CCString*)obj;
	log("notification %s", pParam->getCString());

	if (pParam->intValue() == 1) {
		log("noti 11");
		Director::sharedDirector()->resume();			//화면 재시작
		Director::sharedDirector()->startAnimation();	//메뉴 버튼 활성
	}
	else {
		//CCArray* childs = (CCArray*)this->getChildren();
		log("noti 00");
		Director::sharedDirector()->pause();				//화면 정지
		Director::sharedDirector()->stopAnimation();		//메뉴버튼 비활성
	}
}
*/

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