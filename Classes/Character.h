#pragma once
#include "cocos2d.h"

USING_NS_CC;
/**
�÷��̾�, �� ����� ĳ���� (����Ͽ� ����� ��)
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
	enum { IDLE, WALK, FLIP }; //�ִϸ��̼� ���� enum ���
	bool fliping;
	bool stz;

	/*
	HP,MP,���ݷ�,����,HPȸ��,MPȸ��,����,�̼�
	*/
	int hp;
	int mp;
	int attack;
	int defense;
	int hpgen;
	int mpgen;
	int attack_speed;
	//�̵��ӵ��� walkSpeed & power�� ���ǵǾ� �ִ�.
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
