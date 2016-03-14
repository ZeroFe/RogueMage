#pragma once
#include "Player.h"
#include "Item.h"
#include "Global.h"
#include "data_recources.h"

USING_NS_CC;

class UI_HUD {
private:
	// 기본 배경
	Layer	*HUD; //HUD Layer
	Sprite	*HUD_Background;

	// hp, mp, 게임 진행도
	Sprite	*hpGage;
	Sprite	*mpGage;
	Sprite	*stageGage;

	// 캐릭터 특성, 추가 특성
	Sprite	*CharAttr;
	//Sprite	*AddAttr1;
	//Sprite	*AddAttr1;

	// 부적, 열쇠, 아이템
	Label	*Charm;
	Label	*Key;
	Sprite	*Item1;
	Sprite	*Item2;

	Item item[3];

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

	// HP바, MP바, 스테이지바 초기 설정
	void setHpBar();
	void setMpBar();
	void setStageBar();

	// HP바, MP바, 스테이지바 변경
	void fixHpBar();
	void fixMpBar();
	void fixStageBar();

	// 미니맵 관련
	void draw_minimap();
	void remove_minimap();

	void hud_update(float dt);
	Layer* getObject(void);
};