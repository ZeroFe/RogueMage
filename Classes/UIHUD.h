#pragma once
#include "Player.h"
#include "Global.h"
#include "data_recources.h"

USING_NS_CC;

class UI_HUD {
private:
	Layer	*HUD; //HUD Layer
	Sprite	*HUD_Background;

	Sprite	*hpGage;
	Sprite	*mpGage;
	Sprite	*stageGage;

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
	Layer* getObject(void);
};