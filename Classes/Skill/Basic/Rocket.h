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
public:
	Rocket(Scene* ob, Vec2& startPos, double angle);
	~Rocket();
	void launch();
};