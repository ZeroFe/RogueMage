#include "CharacterScene.h"
#include "SelectScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Global.h"
#include "data_recources.h"
#include "RMAlgorithm/mapGenerator.h"

USING_NS_CC;
using namespace ui;

CharacterScene::~CharacterScene()
{
	log("SelectScene :: dealloc");
}

Scene* CharacterScene::createScene()
{
	auto scene = Scene::create();

	auto layer = CharacterScene::create();

	scene->addChild(layer);

	return scene;
}

bool CharacterScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto CharacterLayer = CSLoader::createNode("Scene/CharacterScene/CharacterLayer.csb");

	addChild(CharacterLayer);

	//add 'Back' Button 
	Button* back = static_cast<Button*>(CharacterLayer->getChildByName("Back"));
	back->addTouchEventListener(CC_CALLBACK_1(CharacterScene::doBackScene, this));

	return true;
}

void CharacterScene::onEnter()
{
	Layer::onEnter();

	log("CharacterScene :: onEnter");
}

void CharacterScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();

	log("CharacterScene :: onEnterTransitionDidFinish");
}

void CharacterScene::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();

	log("CharacterScene :: onExitTransitionDidStart");
}

void CharacterScene::onExit()
{
	Layer::onExit();

	log("CharacterScene :: onExit");
}

// 뒤로 가기
void CharacterScene::doBackScene(Ref* pSender)
{
	auto pScene = SelectScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}