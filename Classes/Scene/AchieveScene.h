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
	/*
	업적 저장 구조체
	name : 업적 이름
	content : 업적 내용
	*/
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
	// 업적 저장 벡터
	vector<Achieve*> vecAchieve;
public:
	AchieveScene();
	~AchieveScene();

	static cocos2d::Scene* createScene();

	virtual bool init();
private:
	// 업적을 마우스 스크롤로 내릴수 있게 함(구현 필요)
	void onMouseScroll(cocos2d::Event *e) {};

	// 업적 데이터 초기화
	void initAchieveData();

	// implement the "static create()" method manually
	CREATE_FUNC(AchieveScene);

	// 메뉴 화면으로 돌아가기
	void doBackScene(cocos2d::Ref* pSender);
	TransitionScene* createTransition(float t, Scene* s);
};

#endif // __ACHIEVE_SCENE_H__
