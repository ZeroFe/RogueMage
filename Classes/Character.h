#pragma once
#include "cocos2d.h"

USING_NS_CC;
/**
플레이어, 적 등등의 캐릭터 (상속하여 사용할 것)
*/
class Character {

private:
	Sprite* player;
	Texture2D* playerTexture;
	Animation* idle;
	Animation* walk;
	Animate* _idle;
	Animate* _walk;
	RepeatForever* __idle;
	RepeatForever* __walk;
	enum { IDLE, WALK, FLIP }; //애니메이션 지정 enum 상수
	bool fliping;
	bool stz;

	/*
	HP,MP,공격력,방어력,HP회복,MP회복,공속,이속
	*/
	int hp;
	int mp;
	int attack;
	int defense;
	int hpgen;
	int mpgen;
	int attack_speed;
	//이동속도는 walkSpeed & power에 정의되어 있다.
public:

	void setflipingFalse(void);
	void eval(void);
	enum { LEFT, RIGHT };
	double walkSpeed;
	double f;
	double colMove;
	double vx;
	double vy;
	double power;
	Sprite* get();
	Character(Sprite* player); 
	void ActWalk();
	void ActIdle();
	void ActFlip(int direction = LEFT);
	void sendDamage(Vector<Character *> enemys, double* damages);
	void receiveDamage(double joule);
};
