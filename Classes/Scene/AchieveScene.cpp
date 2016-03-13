#include "AchieveScene.h"
#include "SelectScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace std;

AchieveScene::AchieveScene()
{
	vecAchieve.clear();
}

AchieveScene::~AchieveScene()
{
	vecAchieve.clear();
}

Scene* AchieveScene::createScene()
{
	auto scene = Scene::create();

	auto layer = AchieveScene::create();

	scene->addChild(layer);

	return scene;
}

bool AchieveScene::init()
{
	log("AchieveScene");

	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255)))
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	AchieveLayer = CSLoader::createNode("Scene/AchieveScene/AchieveSceneLayer.csb");

	initAchieveData();
	
	initAchieveList();

	//add 'Back' Button 
	Button* back = static_cast<Button*>(AchieveLayer->getChildByName("Back"));
	back->addTouchEventListener(CC_CALLBACK_1(AchieveScene::doBackScene, this));

	return true;
}

// Add Achieve List
void AchieveScene::initAchieveData()
{
	log("set Data");

	Achieve* achieve = nullptr;
	
	achieve = new (std::nothrow)Achieve;
	if (achieve)
	{
		achieve->name = "Achieve";
		achieve->content = "make Achieve";
		vecAchieve.push_back(achieve);
	}

	achieve = new (std::nothrow)Achieve;
	if (achieve)
	{
		achieve->name = "22";
		achieve->content = "222";
		vecAchieve.push_back(achieve);
	}
}

// 
void AchieveScene::initAchieveList()
{
	auto AttributeNode = CSLoader::createNode("Scene/AchieveScene/Node/AttributeNode.csb");
	auto AchieveList = static_cast<ListView*>(AchieveLayer->getChildByName("AchieveList"));
	auto AttributePanel = static_cast<Layout*>(AttributeNode->getChildByName("Panel"));

	addChild(AchieveLayer);
	
	// add Achieve item
	for (auto vecData : vecAchieve)
	{
		auto pCloneItem = AttributePanel->clone();
		
		auto Achieve_Name = static_cast<Text*>(pCloneItem->getChildByName("Achieve_Name"));
		auto Achieve_Content = static_cast<Text*>(pCloneItem->getChildByName("Achieve_content"));

		string str_name = vecData->name;
		string str_content = vecData->content;

		Achieve_Name->setString(StringUtils::toString(str_name));
		Achieve_Content->setString(StringUtils::toString(str_content));
		
		AchieveList->pushBackCustomItem(pCloneItem);
	}
}

void AchieveScene::doBackScene(Ref* pSender)
{
	auto pScene = SelectScene::createScene();
	Director::getInstance()->replaceScene(createTransition(1, pScene));
}

TransitionScene* AchieveScene::createTransition(float t, Scene* s)
{
	Director::getInstance()->setDepthTest(false);
	return TransitionMoveInL::create(t, s);
}