#include "UIHUD.h"
#include "data_recources.h"

UI_HUD::UI_HUD() {
	HUD = Layer::create();
	HUD->setContentSize(CCSizeMake(1280,240));

	HUD_Background = Sprite::create("char/hud/background.png");
	this->setAnchorPoint(Point(0, 1)); //�ʱ� Anchor Point ����
	HUD->setPosition(Point(0, 0));
	HUD->addChild(HUD_Background, -1);

	auto HUD_Panel = Sprite::create("char/hud/panel.png");
	HUD_Panel->setAnchorPoint(Point(0, 1));
	HUD_Panel->setPosition(Point(0, 960));
	HUD->addChild(HUD_Panel, 1);
}

void UI_HUD::setAnchorPoint(Point& position) {
	HUD_Background->setAnchorPoint(position);
}

Layer* UI_HUD::getObject(void) {
	return HUD;
}

void UI_HUD::setPosition(Point& position) {
	HUD_Background->setPosition(position);
}

// minimap �׸���
void UI_HUD::draw_minimap()
{
	auto minimap_room = SpriteBatchNode::create(resData::hudMinimap[0], 50);
	Point hudPos = Point(1105 - Global::currentPosX * 64, 840 - Global::currentPosY * 36);
	minimap_room->setPosition(hudPos);
	//rootNode->addChild(minimap_room, 0, 1);
	HUD->addChild(minimap_room, 0, 1);

	auto minimap_room_texture = minimap_room->getTexture();

	Point centerPoint(0, 0); //�̴ϸ��� ��� ǥ���� �� �����Ѵ�.
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			// �̴ϸ� �׸��� ����
			if (Global::mapData[i][j] == '\0')
				continue;
			if (Global::currentPosX + 2 < i || i < Global::currentPosX - 2)
				continue;
			if (Global::currentPosY + 3 < j || j < Global::currentPosY - 3)
				continue;

			// �̴ϸ� �׸���
			auto pTemp = Sprite::createWithTexture(minimap_room_texture);
			pTemp->setPosition(Point(centerPoint.x + i * 64, centerPoint.y + j * 36));
			if (i == Global::currentPosX && j == Global::currentPosY)
				pTemp->setColor(Color3B::RED);
			minimap_room->addChild(pTemp);
		}
	}
}

UI_HUD::~UI_HUD() {

}

/**
//1. HUD ����
//HUD = Sprite::create("char/hud2.png");
//HUD->setAnchorPoint(Point(0, 1));
//HUD->setPosition(Point(0, 960));
//rootNode->addChild(HUD);
*/