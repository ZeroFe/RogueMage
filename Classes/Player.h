#pragma once
#include "cocos2d.h"
#include "Character.h"
#include "data_recources.h"
#include "Global.h"

USING_NS_CC;
/**
�÷��� ������ ĳ�����̴�.
*/
class Player : public Layer {

private:
	Sprite* player; //�÷��̾� sprite
	Texture2D* playerTexture; //�÷��̾��� Texture (�޸� ����)

	SpriteBatchNode * playerWalk; //�ȴ� �÷��̾��� sprite & Texture
	Texture2D * playerWalk_texture2D;

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


	//���� ���� (Activity Private Func)
	void basicAttackActivity(float dt);


	//�ɷ�ġ
	int attack;
	int defense;
public:
	
	void setflipingFalse(void);
	void stabilization(void);
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

	void sendDamage(Vector<Sprite *> enemys, double* damages); //������ �������� ������.
	void receiveDamage(double joule); //���ظ� �Դ´�.


	void basicAttack(Scene* ob, Vec2& startPos, double angle);
};
