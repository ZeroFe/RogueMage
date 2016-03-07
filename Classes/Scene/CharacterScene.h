#ifndef __SceneTrans__CharacterScene__
#define __SceneTrans__CharacterScene__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class CharacterScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(CharacterScene);

	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
	virtual void onExit();
	~CharacterScene(void);

	// ���콺 ������ ����
	void onMouseDown(cocos2d::Event *e) {};
	void onMouseUp(cocos2d::Event *e) {};
	void onMouseMove(cocos2d::Event *e) {};
	void onMouseScroll(cocos2d::Event *e) {};

	void doBackScene(Ref* pSender);

private:

};

#endif /* defined(__SceneTrans__CharSelectScene__) */