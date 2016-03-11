#pragma once
#include <iostream>
#include "cocos2d.h"
#include "Global.h"
#include "data_recources.h"
using namespace std;
USING_NS_CC;
//적 개체에 대한 것
//적의 고유 (모습, 스킬 등등) 모습을 Parameter 로 받아와야 한다.

class EnemyObject {
public:
	EnemyObject(string name = "commonOBj", int hp = 100, int mp = 50, int speed=30);
	void sendDamage(); //Parent class ref
	void receiveDamage(double enegy_joule);
	~EnemyObject();
};