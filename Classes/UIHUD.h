#pragma once
#include "Player.h"
#include "Item.h"
#include "Global.h"
#include "data_recources.h"

USING_NS_CC;

class UI_HUD {
private:
	// �⺻ ���
	Layer	*HUD; //HUD Layer
	Sprite	*HUD_Background;

	// hp, mp, ���� ���൵
	Sprite	*hpGage;
	Sprite	*mpGage;
	Sprite	*stageGage;

	// ĳ���� Ư��, �߰� Ư��
	Sprite	*CharAttr;
	//Sprite	*AddAttr1;
	//Sprite	*AddAttr1;

	// ����, ����, ������
	Label	*Charm;
	Label	*Key;
	Sprite	*Item1;
	Sprite	*Item2;

	Item item[3];

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

	// HP��, MP��, ���������� �ʱ� ����
	void setHpBar();
	void setMpBar();
	void setStageBar();

	// HP��, MP��, ���������� ����
	void fixHpBar();
	void fixMpBar();
	void fixStageBar();

	// �̴ϸ� ����
	void draw_minimap();
	void remove_minimap();

	void hud_update(float dt);
	Layer* getObject(void);
};