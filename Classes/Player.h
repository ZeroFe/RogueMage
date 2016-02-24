#pragma once
#include "cocos2d.h"

USING_NS_CC;
/**
�÷��� ������ ĳ�����̴�.
*/
class Player {

private:
	Sprite* player; //��ü ���� ��� �ܺο��� �޾ƿ��� player Sprite�� Pointer ����
	Sprite* playerSprite; //���� ������ ��ü (���� �ʿ�)
	Texture2D* playerTexture; //�÷��̾��� Texture (�޸� ����)

	Animation* idle; //������ ���ִ� Animation
	Animation* walk; //�ȴ� Animation
	Animate* _idle; //������ ���ִ� Animation
	Animate* _walk;//�ȴ� Animation
	RepeatForever* __idle; //�ִϸ��̼� �ݺ�
	RepeatForever* __walk; //�ִϸ��̼� �ݺ�
	enum { IDLE, WALK, FLIP }; //�ִϸ��̼� ���� enum ���
	enum { TAG_PLAYER = 100 }; //�� ���̴� enum��� (deprecated)
	int currentAction; //���� ĳ���Ͱ� ���ϰ� �ִ� Action ���� (enum ��� ����)
	int lookAt;
	bool fliping; //ĳ���� �������� ��� ���� ���� (ActIdle ����)
	void falseFlip(void); //flip Cancel ���� �Լ� (ĳ���Ͱ� �������� ������ ������ �÷��� ������ �ٲ�)
	enum {W, A, S, D}; //wasd Ű enum ���� (0, 1, 2, 3)





public:

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
	Player(const char* filename = "char/character_sprite.png", int size = 0, int width = 0, int height = 0); //������ over-load�Լ�
	void ActWalk(Scene* s); //ĳ���͸� �ȴ� ����� ����Ѵ�. (�Ű� ������ ������ ��ǻ� �ʿ����� �ʴ�. NULL �����ص� ����)
	void ActIdle(Scene* s); //ĳ���͸� ������ �ִ� ����� ����Ѵ�. (�Ű� ������ ������ ��ǻ� �ʿ����� �ʴ�.)
	void ActFlip(Scene* p); //ĳ���͸� ������ ����� ����Ѵ�. (�Ű� ������ ������ ��ǻ� �ʿ����� �ʴ�.)
};
