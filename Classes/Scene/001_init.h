#pragma once
#include "cocos2d.h"
#include "../Player.h"

USING_NS_CC;

class Scene_init : public LayerColor {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Scene_init);
	virtual bool onTouchBegan(Touch*, Event*);
	void doClick(Point& location);
	Player *playerObj; //new �� �����ϹǷ� ��Ģ������ delete �� �ʿ��ϴ�.
	Sprite *player;

	virtual void onEnter();
	virtual void onExit();
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
};
