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
public:
	EnemyObject(string name = "commonOBj", int hp = 100, int mp = 50, int speed=30);
	void sendDamage(); //Parent class ref
	void receiveDamage(double enegy_joule);
	~EnemyObject();
};