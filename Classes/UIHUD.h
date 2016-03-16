#pragma once
#include "Player.h"
#include "Global.h"
#include "data_recources.h"

USING_NS_CC;

class UI_HUD {
private:
	// �⺻ ���
	Node	*HUD; //HUD Layer

	// hp, mp, ���� ���൵
	Sprite	*hpGage;
	Sprite	*mpGage;
	Sprite	*stageGage;

	// ĳ���� Ư��, �߰� Ư��
	Sprite	*CharAttr;
	Sprite	*AddAttr1;
	Sprite	*AddAttr2;

	// ����, ����, ������
	Label	*Charm;
	Label	*Key;

	Sprite	*Item1;
	Sprite	*Item2;

	// �̴ϸ�
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