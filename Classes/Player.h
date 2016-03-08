#pragma once
#include "cocos2d.h"
#include "Character.h"
#include "data_recources.h"
#include "Global.h"

USING_NS_CC;
/**
플레이 가능한 캐릭터이다.
*/
class Player : public Layer {

private:
	Sprite* player; //플레이어 sprite
	Texture2D* playerTexture; //플레이어의 Texture (메모리 관리)

	SpriteBatchNode * playerWalk; //걷는 플레이어의 sprite & Texture
	Texture2D * playerWalk_texture2D;

	Animation* idle; //가만히 서있는 Animation
	Animation* walk; //걷는 Animation
	Animate* _idle; //가만히 서있는 Animation
	Animate* _walk;//걷는 Animation
	RepeatForever* __idle; //애니메이션 반복
	RepeatForever* __walk; //애니메이션 반복
	enum { IDLE, WALK, FLIP }; //애니메이션 지정 enum 상수
	enum { W, A, S, D }; //wasd 키 enum 변수 (0, 1, 2, 3)
	bool fliping;
	bool stz; //character 안정화


	//각종 공격 (Activity Private Func)
	void basicAttackActivity(float dt);


	//능력치
	int attack;
	int defense;
public:
	
	void setflipingFalse(void);
	void stabilization(void);
	enum { LEFT, RIGHT };
	//moving Variable (public is temp)
	double walkSpeed;
	double f; //반발력
	double colMove; //벽에 닿았을 때 튕겨내기 위한 1/60초당 거리 (pixel 단위)
	double vx; //1프레임당 x위치 변화량
	double vy; //1프레임당 y위치 변화량
	double power; //캐릭터에 가해질 힘 (이동)

	//Animation List도 하드코딩
	Sprite* get();
	Player(Sprite* player); //플레이어 오브젝트의 생성자이다. Sprite 객체를 외부에서 만들고 그 포인터만을 매개변수로 받는다.
	void ActWalk(); //캐릭터를 걷는 모션을 재생한다. (매개 변수를 받으나 사실상 필요하지 않다. NULL 삽입해도 무방)
	void ActIdle(); //캐릭터를 가만히 있는 모션을 재생한다. (매개 변수를 받으나 사실상 필요하지 않다.)
	void ActFlip(int direction = LEFT); //캐릭터를 뒤집는 모션을 재생한다. (매개 변수를 받으나 사실상 필요하지 않다.)

	void sendDamage(Vector<Sprite *> enemys, double* damages); //적에게 데미지를 보낸다.
	void receiveDamage(double joule); //피해를 입는다.


	void basicAttack(Scene* ob, Vec2& startPos, double angle);
};
