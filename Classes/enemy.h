#pragma once
#include "cocos2d.h"
#include "Character.h"

USING_NS_CC;
/**
나를 제외한 적들을 관리하는 체계이다.
여기서는 하나의 적만 나오도록 임시조치
*/
class Enemy {
private:
	int hp;
	int mp;
	Sprite *sprite;
public:
	Enemy();
	void stand();
	void die();
	void sendDamage();
	void receiveDamage();
	~Enemy();
};