#pragma once
#include "cocos2d.h"

USING_NS_CC;
/**
�÷��� ������ ĳ�����̴�.
��Ų ����, ��Ų������ ����
�̵� ����/
�̵��� ���� �ִϸ��̼� ����

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
	enum { IDLE, WALK };
	enum { TAG_PLAYER = 100 };
	int currentAction;
	int pingpong; //Ű���� ���� vulnable ����
public:
	//������ ������ �ϵ��ڵ�(�ϴ�)
	//Animation List�� �ϵ��ڵ�
	Sprite* get();
	Player(const char* filename = "char/character_sprite.png", int size = 0, int width = 0, int height = 0);
	void ActWalk(Scene* s);
	void ActIdle(Scene* s);
};
