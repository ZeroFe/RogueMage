#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"

USING_NS_CC;

class Scene_draw : public LayerColor {
private:
	RenderTexture	*target;
	Sprite			*brush;
	b2World *world_;
	void tick(float dt);
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Scene_draw);
	void addRectangleBetweenPointsToBody(b2Body *body, CCPoint start, CCPoint end);
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	virtual void ccTouchMoved(CCSet* touches, CCEvent* event);
	virtual void onEnter();
	virtual void onExit();
};
