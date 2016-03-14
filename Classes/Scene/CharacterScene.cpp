#include "CharacterScene.h"
#include "SelectScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Global.h"
#include "data_recources.h"
#include "RMAlgorithm/mapGenerator.h"
#include "XML/pugixml.hpp"

USING_NS_CC;
using namespace ui;
using namespace pugi;

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

	initCharacter();

	auto CharacterLayer = CSLoader::createNode("Scene/CharacterScene/CharacterLayer.csb");
	auto CharacterNode = CSLoader::createNode("Scene/CharacterScene/Node/CharacterNode.csb");
	auto CharacterList = static_cast<ListView *>(CharacterLayer->getChildByName("CharacterList"));
	auto CharacterPanel = static_cast<Layout *>(CharacterNode->getChildByName("Panel"));
	addChild(CharacterLayer);

	//CharacterList->removeLastItem();

	for (auto vecData : vecChar)
	{
		auto pCloneItem = CharacterPanel->clone();

		// 캐릭터 아이콘 추가
		auto Clone_bg = static_cast<Text *>(pCloneItem->getChildByName("bg"));
		auto Character_Icon = Sprite::create(resData::CharacterIcon[0]);
		Character_Icon->setAnchorPoint(Vec2(0, 1));
		Character_Icon->setPosition(0, 144);
		Clone_bg->addChild(Character_Icon);

		auto Character_Select = static_cast<Button *>(pCloneItem->getChildByName("Select"));
		auto Character_Name = static_cast<Text *>(pCloneItem->getChildByName("Name"));
		auto Character_Path = static_cast<Text *>(pCloneItem->getChildByName("Path"));
		auto Character_HP = static_cast<Text *>(pCloneItem->getChildByName("HP"));


		//데이터는 짜피 다 읽어오고 그걸 표시하도록 바꿔야하는데 굳이 캐선창에서 표시
		//안해도 될것같고 다른 거 먼저 작업을
		//숫자도 출력되는 것만 확인

		Character_Name->setString(StringUtils::toString(vecData.name));
		Character_Path->setString(StringUtils::toString(vecData.path));
		Character_HP->setString(StringUtils::toString(vecData.stat[0]));
		Character_Select->addTouchEventListener([this, vecData](cocos2d::Ref* pSender, Widget::TouchEventType touchType) {
			if (touchType == Widget::TouchEventType::ENDED)
			{
				goGameScene(pSender, vecData);
			}
		});
		CharacterList->pushBackCustomItem(pCloneItem);
	}

	//add 'Back' Button 
	Button* back = static_cast<Button*>(CharacterLayer->getChildByName("btn_back"));
	back->addTouchEventListener(CC_CALLBACK_1(CharacterScene::doBackScene, this));

	return true;
}

void CharacterScene::initCharacter()
{
	xml_document xmlDoc;

	xml_parse_result result = xmlDoc.load_file("../Resources/Data/Character.xml");

	log("Test");

	Data data;

	if (!result)
	{
		log("Error description : %s",result.description());
		log("Error offset : %d",result.offset);
	}

	xml_node nodeChars = xmlDoc.child("CHARS");
	xml_node stat;
	xml_attribute num;

	for (xml_node nodeChar = nodeChars.child("CHAR"); nodeChar; nodeChar = nodeChar.next_sibling("CHAR"))
	{
		data.name = nodeChar.child("NAME").text().get();
		data.path = nodeChar.child("SPRITE").text().get();
		stat = nodeChar.child("STAT");

		num = stat.first_attribute();
		data.stat[0] = num.as_int();
		num = num.next_attribute();
		data.stat[1] = num.as_int();
		num = num.next_attribute();
		data.stat[2] = num.as_int();

		stat=stat.next_sibling();
		num = stat.first_attribute();
		data.stat[3] = num.as_int();
		num = num.next_attribute();
		data.stat[4] = num.as_int();
		num = num.next_attribute();
		data.stat[5] = num.as_int();
		num = num.next_attribute();
		data.stat[6] = num.as_int();

		vecChar.push_back(data);

	}
}

// 캐릭터 정보를 받고 게임으로 넘어가는 함수
void CharacterScene::goGameScene(cocos2d::Ref* pSender, Data data)
{
	log(data.name.c_str());
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