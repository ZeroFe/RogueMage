#include "SelectScene.h"
#include "GameScene.h"
#include "AchieveScene.h"
#include "UIPopup.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Global.h"
#include "data_recources.h"
#include "RMAlgorithm/mapGenerator.h"

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

	SelectLayer = CSLoader::createNode("Scene/SelectScene/SelectSceneLayer.csb");

	addChild(SelectLayer);

	initButton();

	return true;
}

// ��ư ����(������ ����)
void SelectScene::initButton()
{
	// �޴� ��ư�� ã�Ƽ� ������ ����
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

	// ������ ��ư ������ ����
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

// ���콺 ������ ���� Ȯ��
void SelectScene::onMouseDown(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	log("Mouse Down");
}

// Ʃ�丮��
void SelectScene::doTutorialScene(Ref* pSender)
{
	log("Tutorial");

}

// �� ���� ����
void SelectScene::doStartScene(Ref* pSender)
{
	// Call New Game
	log("Start Scene");

	//���� ���� ����� ���´�.

	//0. �ʿ��� �޸� �Ҵ�

	for (int i = 0; i < 10; i++) {
		Global::mapData[i] = new int[10];
		Global::mapTemplate[i] = new int[10];
	}

	//1. 5���� �� ���� (�ʱ�)

	createMap::Map s = createMap::Map::Map();
	s.make(1);
	s.copyMap(Global::mapData);

	//2. ���ø� ����
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (Global::mapData[i][j] != '\0')
				Global::mapTemplate[i][j] = rand() % resData::number_of_template;
		}
	}

	//3. ������ �۷ι� ���� �����ϱ�
	//Global::currentPos = Point(s.startx, s.starty);
	Global::currentPosX = s.startx;
	Global::currentPosY = s.starty;
	log("current Position : %d %d", s.startx, s.starty);
	//4. �� �̸� ����
	strcpy_s(Global::mapName, 256, resData::mapTemplate[Global::mapTemplate[s.startx][s.starty]]); //���� ��

	auto pScene = GameScene::createScene();
	Director::getInstance()->pushScene(pScene);
}

// �ҷ�����
void SelectScene::doContinueScene(Ref* pSender)
{
	log("Continue Scene");
	/*
	auto pScene = TestScene2::createScene();
	Director::getInstance()->pushScene(pScene);
	*/
}

// ����
void SelectScene::doAchieveScene(Ref* pSender)
{
	log("Achieve Scene");
	auto pScene = AchieveScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}

// �����ư
void SelectScene::doExit(Ref* pSender)
{
	// Call Exit Dialog
	log("Exit");

	popup = new UI_Popup();
	popup->setParentLayer(SelectLayer);
	popup->setPopupLayer(CSLoader::createNode("Popup/MenuPopup/MenuPopupLayer.csb"));
	popup->setCallbackFunc(CC_CALLBACK_1(SelectScene::Popup_Callback, this));
	popup->setButton("btn_ok", 1);
	popup->setButton("btn_cancel", 2);
	popup->call();
}

// �˾� ��ư Ŭ���� �ҷ����� �Լ�
void SelectScene::Popup_Callback(Ref* pSender)
{
	pSelect = popup->getBtnTag();

	// ����
	if (pSelect == 1)
	{
		log("1");

		Director::getInstance()->end();
	}
	// ���
	else if (pSelect == 2)
	{
		log("2");
	}

	// �˾� �ݱ�
	popup->close();
}