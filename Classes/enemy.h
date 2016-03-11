#pragma once
#include "cocos2d.h"
#include "Character.h"
#include "EnemyObject.h" //적 개체
#include <list>
//적군의 리스트를 관리한다.
//주인공이 때리는것
//싱글톤 객체이고 인스턴스는 Global 단에서 관리
USING_NS_CC;

class Enemy {
private:
	list<EnemyObject> enemy;
	list<EnemyObject>::iterator enemyIterator;
public:
	Enemy() { };
	void add(EnemyObject& enemyObj);
	void remove(EnemyObject& who);
	~Enemy() {};
};