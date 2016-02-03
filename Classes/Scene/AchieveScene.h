#ifndef __ACHIEVE_SCENE_H__
#define __ACHIEVE_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace std;

class AchieveScene : public cocos2d::LayerColor
{
private:
	struct Achieve
	{
		string name;
		string content;

		Achieve()
		{
			name.clear();
			content.clear();
		}
	};
private:
	vector<Achieve*> vecAchieve;
public:
	AchieveScene();
	~AchieveScene();

	static cocos2d::Scene* createScene();

	virtual bool init();
private:
	void onMouseScroll(cocos2d::Event *e);

	void initAchieveData();

	// implement the "static create()" method manually
	CREATE_FUNC(AchieveScene);

	void doBackScene(cocos2d::Ref* pSender);
	TransitionScene* createTransition(float t, Scene* s);
};

#endif // __ACHIEVE_SCENE_H__
