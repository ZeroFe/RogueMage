#include "UserInput.h"

//Point touchLocation = this->convertTouchToNodeSpace(touch);

UserInput::UserInput(Scene* scene, EventDispatcher *ev) {
	this->scene = scene;
	this->eventDispatcher = ev;
}
void UserInput::start(int eventType) {
	switch (eventType) {
	case UI_KEYBOARD:
		ek = EventListenerKeyboard::create();
		//ek->onKeyPressed = CC_CALLBACK_1(UserInput::onKeyPressed, scene); //this 제어할 필요가 있는지 봐야한다.
		//ek->onKeyReleased = CC_CALLBACK_1(UserInput::onKeyReleased, scene);
		eventDispatcher->addEventListenerWithSceneGraphPriority(ek, scene);
		break;
	default:
		break;
	}
	
}

void UserInput::end(int eventType) {
	eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);
}

void UserInput::onKeyPressed(EventKeyboard::KeyCode KeyCode, Event * event) {
	log("Key Pressed");
}

void UserInput::onKeyReleased(EventKeyboard::KeyCode KeyCode, Event * event) {
	log("Key Released");
}
