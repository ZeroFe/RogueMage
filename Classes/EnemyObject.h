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
private:
	int hp;
	int mp;
	int speed;
	int atk, def;
	int width, height;
	Scene *scene;
	Vec2 position;
	Sprite *sprite; //생김새 (skin)
	string name;
public:
	EnemyObject(string name = "commonOBj", string resource_path = "char/enemy1.png", int hp = 100, int mp = 50, int speed=30);
	void spawn(Vec2& position, Scene *scene); //적을 소환 = spawn
	void sendDamage(); //Parent class ref
	void setPosition(Vec2& point);
	Vec2& getPosition();
	void receiveDamage(double enegy_joule);
	~EnemyObject();
};