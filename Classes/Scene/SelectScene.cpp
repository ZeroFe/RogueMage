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

// 버튼 설정(리스너 설정)
void SelectScene::initButton()
{
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

	//랜덤 맵을 만들어 놓는다.

	//0. 필요한 메모리 할당

	for (int i = 0; i < 10; i++) {
		Global::mapData[i] = new int[10];
		Global::mapTemplate[i] = new int[10];
	}

	//1. 5층용 맵 생성 (초기)

	createMap::Map s = createMap::Map::Map();
	s.make(1);
	s.copyMap(Global::mapData);

	//2. 템플릿 주입
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (Global::mapData[i][j] != '\0')
				Global::mapTemplate[i][j] = rand() % resData::number_of_template;
		}
	}

	//3. 시작점 글로벌 변수 지정하기
	//Global::currentPos = Point(s.startx, s.starty);
	Global::currentPosX = s.startx;
	Global::currentPosY = s.starty;
	log("current Position : %d %d", s.startx, s.starty);
	//4. 맵 이름 주입
	strcpy_s(Global::mapName, 256, resData::mapTemplate[Global::mapTemplate[s.startx][s.starty]]); //시작 맵

	auto pScene = GameScene::createScene();
	Director::getInstance()->pushScene(pScene);
}

// 불러오기
void SelectScene::doContinueScene(Ref* pSender)
{
	log("Continue Scene");
	/*
	auto pScene = TestScene2::createScene();
	Director::getInstance()->pushScene(pScene);
	*/
}

// 업적
void SelectScene::doAchieveScene(Ref* pSender)
{
	log("Achieve Scene");
	auto pScene = AchieveScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}

// 종료버튼
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

// 팝업 버튼 클릭시 불러오는 함수
void SelectScene::Popup_Callback(Ref* pSender)
{
	pSelect = popup->getBtnTag();

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
	popup->close();
}