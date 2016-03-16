#include "UIHUD.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "data_recources.h"

#define HUD_ZORDER 15

UI_HUD::UI_HUD() 
{
	HUD = CSLoader::createNode("Scene/GameScene/UI/UILayer.csb");

	auto HUD_Background = static_cast<Sprite *>(HUD->getChildByName("UI_bg"));
	HUD_Background->setLocalZOrder(HUD_ZORDER);
	auto HUD_Panel = static_cast<Sprite *>(HUD->getChildByName("UI_panel"));
	HUD_Panel->setLocalZOrder(HUD_ZORDER+3);

	setHpBar();
	setMpBar();
	setStageBar();
}
/*
void UI_HUD::setAnchorPoint(Point& position) {
	HUD_Background->setAnchorPoint(position);
}
*/
Node* UI_HUD::getObject(void) {
	return HUD;
}
/*
void UI_HUD::setPosition(Point& position) {
	HUD_Background->setPosition(position);
}
*/
void UI_HUD::setHpBar()
{
	hpGage = static_cast<Sprite *>(HUD->getChildByName("HP"));
	hpGage->setLocalZOrder(HUD_ZORDER+4);
}

void UI_HUD::setMpBar()
{
	mpGage = static_cast<Sprite *>(HUD->getChildByName("MP"));
	mpGage->setLocalZOrder(HUD_ZORDER + 4);
}

void UI_HUD::setStageBar()
{
	stageGage = static_cast<Sprite *>(HUD->getChildByName("Stage"));
	stageGage->setLocalZOrder(HUD_ZORDER + 4);
}

// minimap 그리기
void UI_HUD::draw_minimap()
{
	minimap_room = Node::create();
	//auto minimap_room = SpriteBatchNode::create(resData::hudMinimap[0], 50);
	Point hudPos = Point(1105 - Global::currentPosX * 64, 840 - Global::currentPosY * 36);
	minimap_room->setPosition(hudPos);
	//rootNode->addChild(minimap_room, 0, 1);
	HUD->addChild(minimap_room, HUD_ZORDER+1, 1);

	//auto minimap_room_texture = minimap_room->getTexture();

	Point centerPoint(0, 0); //미니맵을 어디에 표시할 지 결정한다.
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			// 미니맵 그리는 조건
			if (Global::mapData[i][j] == '\0')
				continue;
			if (Global::currentPosX + 2 < i || i < Global::currentPosX - 2)
				continue;
			if (Global::currentPosY + 3 < j || j < Global::currentPosY - 3)
				continue;

			// 미니맵 그리기
			std::string mSpr = resData::hudMinimap[0];
			if (Global::mapData[i][j] == 'B')
			{
				mSpr = resData::hudMinimap[2];
			}
			if (Global::mapData[i][j] == 'T')
			{
				mSpr = resData::hudMinimap[5];
			}
			if(Global::mapData[i][j] == 'C')
			{
				mSpr = resData::hudMinimap[6];
			}
			auto pTemp = Sprite::create(mSpr);
			pTemp->setPosition(Point(centerPoint.x + i * 64, centerPoint.y + j * 36));
			if (i == Global::currentPosX && j == Global::currentPosY)
				pTemp->setColor(Color3B::RED);
			minimap_room->addChild(pTemp);
		}
	}
}

void UI_HUD::remove_minimap()
{
	HUD->removeChild(minimap_room, true);
	minimap_room->release();
}

UI_HUD::~UI_HUD() {

}

/**
//1. HUD 생성
//HUD = Sprite::create("char/hud2.png");
//HUD->setAnchorPoint(Point(0, 1));
//HUD->setPosition(Point(0, 960));
//rootNode->addChild(HUD);
*/