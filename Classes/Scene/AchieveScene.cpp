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

	initAchieveData();

	auto AchieveLayer = CSLoader::createNode("Scene/AchieveScene/AchieveSceneLayer.csb");
	auto AttributeNode = CSLoader::createNode("Scene/AchieveScene/Node/AttributeNode.csb");
	auto AchieveList = static_cast<ListView*>(AchieveLayer->getChildByName("AchieveList"));
	auto AttributePanel = static_cast<Layout*>(AttributeNode->getChildByName("Panel"));

	addChild(AchieveLayer);
	
	// 
	int nCount = 0;
	for (auto vecData : vecAchieve)
	{
		auto pCloneItem = AttributePanel->clone();

		auto Achieve_Name = static_cast<Text*>(AchieveLayer->getChildByName("Achieve_Name"));
		auto Achieve_Content = static_cast<Text*>(AchieveLayer->getChildByName("Achieve_content"));

		string str_name = vecData->name;
		string str_content = vecData->content;

		Achieve_Name->setString(StringUtils::toString(str_name));
		Achieve_Content->setString(StringUtils::toString(str_content));

		AchieveList->pushBackCustomItem(pCloneItem);

		nCount++;
	}

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
		achieve->name = "1";
		achieve->content = "1";
		vecAchieve.push_back(achieve);
	}

	achieve = new (std::nothrow)Achieve;
	if (achieve)
	{
		achieve->name = "2";
		achieve->content = "2";
		vecAchieve.push_back(achieve);
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