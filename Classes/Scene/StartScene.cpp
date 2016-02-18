#include "StartScene.h"
#include "SelectScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* StartScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	// 코코스 스튜디오로부터 노드 부르고 추가
	auto StartLayer = CSLoader::createNode("Scene/StartScene/StartSceneLayer.csb");
	addChild(StartLayer);

	credit = static_cast<Label*>(StartLayer->getChildByName("Credit"));
	credit->setOpacity(0);

	return true;
}

void StartScene::onEnter()
{
	Layer::onEnter();

	log("onEnter");

	// 마우스 리스너 설정
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(StartScene::onMouseMove, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(StartScene::onMouseUp, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(StartScene::onMouseDown, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(StartScene::onMouseScroll, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	// fade in & fade out animation
	auto fade = Sequence::create(FadeIn::create(1.5), FadeOut::create(1.5), nullptr);

	credit->runAction(fade);

	// 3초 후 자동 장면 전환
	CallFuncN *action = CallFuncN::create(CC_CALLBACK_1(StartScene::doPushScene, this));
	auto replace = Sequence::create(DelayTime::create(3), action, nullptr);

	this->runAction(replace);
}

void StartScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();

	log("StartScene :: onEnterTransitionDidFinish");
}

void StartScene::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();

	log("StartScene :: onExitTransitionDidStart");
}

void StartScene::onExit()
{
	log("StartScene :: onExit");
	//_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}

void StartScene::onMouseDown(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	log("Mouse Down");

	// 다음 장면으로 이동
	auto pScene = SelectScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}

void StartScene::doPushScene(Ref* pSender)
{
	// 두번째 장면
	auto pScene = SelectScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}

StartScene::~StartScene()
{
	log("StartScene end");
}