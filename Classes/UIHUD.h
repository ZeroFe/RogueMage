#pragma once
#include "Player.h"
#include "Global.h"
#include "data_recources.h"

USING_NS_CC;

class UI_HUD {
private:
	// 기본 배경
	Node	*HUD; //HUD Layer

	// hp, mp, 게임 진행도
	Sprite	*hpGage;
	Sprite	*mpGage;
	Sprite	*stageGage;

	// 캐릭터 특성, 추가 특성
	Sprite	*CharAttr;
	Sprite	*AddAttr1;
	Sprite	*AddAttr2;

	// 부적, 열쇠, 아이템
	Label	*Charm;
	Label	*Key;

	Sprite	*Item1;
	Sprite	*Item2;

	// 미니맵
	Node	*minimap_room;
public:
	UI_HUD();
	~UI_HUD();
	Point getPosition(void);
	int getPositionX(void);
	int getPositionY(void);
	void setPosition(Point& position);
	void setPositionX(int xPosition);
	void setPositionY(int yPosition);
	void setAnchorPoint(Point& Anchorposition);

	void setHpBar();
	void setMpBar();
	void setStageBar();

	void draw_minimap();
	void remove_minimap();

	void hud_update(float dt);
	Node* getObject(void);
};