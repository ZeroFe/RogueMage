#pragma once
#include "cocos2d.h"
#include "Character.h"
#include "EnemyObject.h" //�� ��ü
#include <list>
//������ ����Ʈ�� �����Ѵ�.
//���ΰ��� �����°�
//�̱��� ��ü�̰� �ν��Ͻ��� Global �ܿ��� ����
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