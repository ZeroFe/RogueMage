#pragma once
#include "cocos2d.h"

USING_NS_CC;

//모든 input은 여기서 캐치된다.

class UserInput : public LayerColor {
private:
	Scene *scene;
	EventDispatcher* eventDispatcher; //external 단에서 가져오는 값
	EventListenerKeyboard* ek;
	void onKeyPressed(EventKeyboard::KeyCode KeyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode KeyCode, Event* event);
public:
	enum {UI_KEYBOARD, UI_MOUSE};
	UserInput(Scene* scene, EventDispatcher *ev);
	void start(int eventType = UI_KEYBOARD);
	void end(int eventType = UI_KEYBOARD);
	void isKeyDown();
};