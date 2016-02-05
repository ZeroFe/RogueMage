#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	log("map change? : %s", Global::mapName);
	auto rootNode = CSLoader::createNode(Global::mapName);
	addChild(rootNode);
	return true;
}

TransitionScene* HelloWorld::transition(float t, Scene * s)
{
	Director::getInstance()->setDepthTest(false);
	return TransitionPageTurn::create(t, s, false);
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	//키보드 입력으로 캐릭터 움직이기
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);
}

void HelloWorld::onExit()
{
	//_eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);
	Layer::onExit();
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{

}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	log("change map");

	auto nextScene = HelloWorld::createScene();
	//auto trans = TransitionTurnOffTiles::create(0.5, nextScene);
	srand(time(NULL));
	if (rand() % 2)
		strcpy_s(Global::mapName, 256, "Scene/GameScene/Scene2.csb");
	else
		strcpy_s(Global::mapName, 256, "Scene/GameScene/MainScene.csb");
	Director::getInstance()->replaceScene(transition(0.5, nextScene));
}
