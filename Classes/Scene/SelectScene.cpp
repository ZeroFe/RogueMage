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
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255)))
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	initButton();

	popupBoard = Sprite::create("popupBoard");
	popupBackground = Sprite::create("popupBackground");

	//��Ƽ�����̼� ��ī
	//CCNotificationCenter::sharedNotificationCenter()->addObserver(this, SEL_CallFuncO(&SelectScene::doNotification), "notification", NULL);
	//"notification"�̶�� �޽����� ���� �ش� �Լ��� �����Ѵ�.

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
	exit->addTouchEventListener(CC_CALLBACK_2(SelectScene::menuCloseCallback, this));
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

void SelectScene::onMouseUp(Event *event)
{
}

void SelectScene::onMouseMove(Event *event)
{
}

void SelectScene::onMouseScroll(Event *event)
{
}

void SelectScene::doTutorialScene(Ref* pSender)
{
	log("Tutorial");

	auto popup = UIPopupWindow::create(popupBoard, popupBackground);
	popup->showPopup(this);
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
/*
void SelectScene::doExit(Ref* pSender)
{
	// Call Exit Dialog
	log("Exit");
	Scene* pScene = ExitDialog::createScene();
	this->addChild(pScene, 2000, 2000);
}
*/

void SelectScene::doClose(Ref* pSender)
{
	Director::getInstance()->popScene();
	//    Director::getInstance()->popToRootScene();
}

/*
void SelectScene::doNotification(CCObject *obj)
{
	//��Ƽ�����̼� �ޱ�
	CCString *pParam = (CCString*)obj;
	log("notification %s", pParam->getCString());

	if (pParam->intValue() == 1) {
		log("noti 11");
		Director::sharedDirector()->resume();			//ȭ�� �����
		Director::sharedDirector()->startAnimation();	//�޴� ��ư Ȱ��
	}
	else {
		//CCArray* childs = (CCArray*)this->getChildren();
		log("noti 00");
		Director::sharedDirector()->pause();				//ȭ�� ����
		Director::sharedDirector()->stopAnimation();		//�޴���ư ��Ȱ��
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