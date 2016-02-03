#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Scene_splash : public LayerColor {
public:
	static Scene* createScene();
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(Touch*, Event*);
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void skip();
	CREATE_FUNC(Scene_splash);
	void nextScene();
};