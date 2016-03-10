#pragma once
#include "cocos2d.h"
#include "Character.h"

USING_NS_CC;
/**
���� ������ ������ �����ϴ� ü���̴�.
���⼭�� �ϳ��� ���� �������� �ӽ���ġ
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