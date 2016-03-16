#pragma once



/*
Deprecated
폐기했습니다.

*/

/*
#include "cocos2d.h"
#include "Character.h"
#include "EnemyObject.h" //적 개체
#include <list>
//적군의 리스트를 관리한다.
//주인공이 때리는것
//싱글톤 객체이고 인스턴스는 Global 단에서 관리
USING_NS_CC;
class EnemyObject;
class Enemy {
	friend class EnemyObject;
private:
	list<EnemyObject> enemy;
	//list<EnemyObject>::iterator enemyIterator;
	struct Data {
		int num; //고유번호
		std::string name; //몬스터이름
		Sprite* skin; //생김새 (기본)
		int hp, mp;
		int mpgen;
		int atk, def;
		int speed_move;
		int speed_atk; //공격속도
	};
public:
	Enemy(void);
	void addEnemy(EnemyObject& enemyObj); //적을 예비목록에 추가
	void removeEnemy(EnemyObject& who); //적을 예비목록에서 삭제 (죽거나 그 외 기타 이유)
	~Enemy(void);
};*/