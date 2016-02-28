#pragma once
#include "cocos2d.h"

USING_NS_CC;
/**
�÷��� ������ ĳ�����̴�.
*/
class Player {

private:
	Sprite* player; //�÷��̾� sprite
	Texture2D* playerTexture; //�÷��̾��� Texture (�޸� ����)

	Animation* idle; //������ ���ִ� Animation
	Animation* walk; //�ȴ� Animation
	Animate* _idle; //������ ���ִ� Animation
	Animate* _walk;//�ȴ� Animation
	RepeatForever* __idle; //�ִϸ��̼� �ݺ�
	RepeatForever* __walk; //�ִϸ��̼� �ݺ�
	enum { IDLE, WALK, FLIP }; //�ִϸ��̼� ���� enum ���
	enum { W, A, S, D }; //wasd Ű enum ���� (0, 1, 2, 3)
	bool fliping;
	bool stz; //character ����ȭ
public:
	
	void setflipingFalse(void);
	void eval(void);
	enum { LEFT, RIGHT };
	//moving Variable (public is temp)
	double walkSpeed;
	double f; //�ݹ߷�
	double colMove; //���� ����� �� ƨ�ܳ��� ���� 1/60�ʴ� �Ÿ� (pixel ����)
	double vx; //1�����Ӵ� x��ġ ��ȭ��
	double vy; //1�����Ӵ� y��ġ ��ȭ��
	double power; //ĳ���Ϳ� ������ �� (�̵�)

	//Animation List�� �ϵ��ڵ�
	Sprite* get();
	Player(Sprite* player); //�÷��̾� ������Ʈ�� �������̴�. Sprite ��ü�� �ܺο��� ����� �� �����͸��� �Ű������� �޴´�.
	void ActWalk(); //ĳ���͸� �ȴ� ����� ����Ѵ�. (�Ű� ������ ������ ��ǻ� �ʿ����� �ʴ�. NULL �����ص� ����)
	void ActIdle(); //ĳ���͸� ������ �ִ� ����� ����Ѵ�. (�Ű� ������ ������ ��ǻ� �ʿ����� �ʴ�.)
	void ActFlip(int direction = LEFT); //ĳ���͸� ������ ����� ����Ѵ�. (�Ű� ������ ������ ��ǻ� �ʿ����� �ʴ�.)
};
