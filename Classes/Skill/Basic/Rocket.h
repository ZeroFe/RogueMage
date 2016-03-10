#pragma once
#include "cocos2d.h"
#include "data_recources.h"
USING_NS_CC;

class Rocket : public Layer {
private:
	Scene* ob;
	Vec2 startPos;
	double angle;
	Sprite* arrow;
	int vx, vy;
	int speed;
	int lifecycleTime; //이 수 나누기 60(fps) 만큼이 생존시간, 지난다면 객체 소멸
	void update2(float dt);
public:
	Rocket(Scene* ob, Vec2& startPos, double angle);
	~Rocket();
	void launch();
};