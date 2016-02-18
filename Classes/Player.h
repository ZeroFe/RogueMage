#pragma once
#include "cocos2d.h"

USING_NS_CC;
/**
플레이 가능한 캐릭터이다.
스킨 정의, 스킨사이즈 정의
이동 가능/
이동에 따른 애니메이션 정의

*/
class Player {  

private:
	Sprite* player;
	Sprite* playerSprite;
	Texture2D* playerTexture;

	Animation* idle;
	Animation* walk;
	Animate* _idle;
	Animate* _walk;
	RepeatForever* __idle;
	RepeatForever* __walk;
	enum { IDLE, WALK, FLIP };
	enum { TAG_PLAYER = 100 };
	int currentAction;
	int lookAt;





public:

	//moving Variable (public is temp)
	double walkSpeed;
	double f;
	double colMove;
	double vx;
	double vy;
	double power;



	//내부의 범위는 하드코딩(일단)
	//Animation List도 하드코딩
	Sprite* get();
	Player(Sprite* player); //Hardcorded
	Player(const char* filename = "char/character_sprite.png", int size = 0, int width = 0, int height = 0);
	void ActWalk(Scene* s);
	void ActIdle(Scene* s);
	void ActFlip(Scene* p);
};
