#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Global.h"
#include "Player.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	TransitionScene* transition(int direction, float t, Scene* s);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
	virtual void onEnter();
	virtual void onExit();
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);


	Node *rootNode;
	Sprite *playerSprite;
	Sprite *HUD;
	TMXTiledMap *map;
	Player *playerObj;
	TMXLayer *metainfo;
	TMXObjectGroup *objects;
	Point HelloWorld::tileCoordForPosition(Point position);
	void HelloWorld::enterFrame(float dt);

	bool moveable(int direction); //다른 클래스로 통폐합 예정
	void moveScene(int direction);

	enum {W, A, S, D};
};

#endif // __HELLOWORLD_SCENE_H__
