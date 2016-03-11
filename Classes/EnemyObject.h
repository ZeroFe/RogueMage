#pragma once
#include <iostream>
#include "cocos2d.h"
#include "Global.h"
#include "data_recources.h"
using namespace std;
USING_NS_CC;
//�� ��ü�� ���� ��
//���� ���� (���, ��ų ���) ����� Parameter �� �޾ƿ;� �Ѵ�.

class EnemyObject {
private:
	int hp;
	int mp;
	int speed;
	int atk, def;
	int width, height;
	Scene *scene;
	Vec2 position;
	Sprite *sprite; //����� (skin)
	string name;
public:
	EnemyObject(string name = "commonOBj", string resource_path = "char/enemy1.png", int hp = 100, int mp = 50, int speed=30);
	void spawn(Vec2& position, Scene *scene); //���� ��ȯ = spawn
	void sendDamage(); //Parent class ref
	void setPosition(Vec2& point);
	Vec2& getPosition();
	void receiveDamage(double enegy_joule);
	~EnemyObject();
};