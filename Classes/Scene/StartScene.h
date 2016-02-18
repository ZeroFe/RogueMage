#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(StartScene);

	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
	virtual void onExit();
	~StartScene(void);

	// 마우스 리스너 설정
	void onMouseDown(cocos2d::Event *e);
	void onMouseUp(cocos2d::Event *e) {};
	void onMouseMove(cocos2d::Event *e) {};
	void onMouseScroll(cocos2d::Event *e) {};

	// 다음 장면(메뉴)로 이동
	void doPushScene(Ref* pSender);

private:
	cocos2d::Label* credit;
};

#endif // __START_SCENE_H__
