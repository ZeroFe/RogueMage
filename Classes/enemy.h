#pragma once



/*
Deprecated
����߽��ϴ�.

*/

/*
#include "cocos2d.h"
#include "Character.h"
#include "EnemyObject.h" //�� ��ü
#include <list>
//������ ����Ʈ�� �����Ѵ�.
//���ΰ��� �����°�
//�̱��� ��ü�̰� �ν��Ͻ��� Global �ܿ��� ����
USING_NS_CC;
class EnemyObject;
class Enemy {
	friend class EnemyObject;
private:
	list<EnemyObject> enemy;
	//list<EnemyObject>::iterator enemyIterator;
	struct Data {
		int num; //������ȣ
		std::string name; //�����̸�
		Sprite* skin; //����� (�⺻)
		int hp, mp;
		int mpgen;
		int atk, def;
		int speed_move;
		int speed_atk; //���ݼӵ�
	};
public:
	Enemy(void);
	void addEnemy(EnemyObject& enemyObj); //���� �����Ͽ� �߰�
	void removeEnemy(EnemyObject& who); //���� �����Ͽ��� ���� (�װų� �� �� ��Ÿ ����)
	~Enemy(void);
};*/