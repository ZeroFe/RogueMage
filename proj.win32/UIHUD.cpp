#include "UIHUD.h"

UI_HUD::UI_HUD() {
	HUD = Layer::create();
	HUD_Background = Sprite::create("char/hud2.png");
	this->setAnchorPoint(Point(0, 1)); //초기 Anchor Point 설정
	HUD->setPosition(Point(0, 0));
	HUD->addChild(HUD_Background);
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

UI_HUD::~UI_HUD() {

}

/**
//1. HUD 생성
//HUD = Sprite::create("char/hud2.png");
//HUD->setAnchorPoint(Point(0, 1));
//HUD->setPosition(Point(0, 960));
//rootNode->addChild(HUD);
*/