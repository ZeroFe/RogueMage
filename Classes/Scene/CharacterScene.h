#ifndef __SceneTrans__CharacterScene__
#define __SceneTrans__CharacterScene__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class CharacterScene : public cocos2d::Layer
{
private:
	struct Data
	{
		std::string name;
		std::string path;
		int stat[7];
	};

	std::vector<Data> vecChar;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
	virtual void onExit();
	~CharacterScene(void);

	// 마우스 리스너 설정
	void onMouseDown(cocos2d::Event *e) {};
	void onMouseUp(cocos2d::Event *e) {};
	void onMouseMove(cocos2d::Event *e) {};
	void onMouseScroll(cocos2d::Event *e) {};

	void doBackScene(Ref* pSender);

private:
	CREATE_FUNC(CharacterScene);

	void initCharacter();
	void goGameScene(Ref* pSender, Data data);
};

#endif /* defined(__SceneTrans__CharSelectScene__) */