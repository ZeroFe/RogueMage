#pragma once
#include "cocos2d.h"

USING_NS_CC;
/**
플레이 가능한 캐릭터이다.
*/
class Player {

private:
	Sprite* player; //객체 생성 당시 외부에서 받아오는 player Sprite의 Pointer 저장
	Sprite* playerSprite; //위와 동일한 객체 (통합 필요)
	Texture2D* playerTexture; //플레이어의 Texture (메모리 관리)

	Animation* idle; //가만히 서있는 Animation
	Animation* walk; //걷는 Animation
	Animate* _idle; //가만히 서있는 Animation
	Animate* _walk;//걷는 Animation
	RepeatForever* __idle; //애니메이션 반복
	RepeatForever* __walk; //애니메이션 반복
	enum { IDLE, WALK, FLIP }; //애니메이션 지정 enum 상수
	enum { TAG_PLAYER = 100 }; //안 쓰이는 enum상수 (deprecated)
	int currentAction; //현재 캐릭터가 취하고 있는 Action 종류 (enum 상수 대입)
	int lookAt;
	bool fliping; //캐릭터 뒤집히는 모션 정지 방지 (ActIdle 대응)
	void falseFlip(void); //flip Cancel 관련 함수 (캐릭터가 뒤집히는 과정이 끝나면 플래그 변수를 바꿈)
	enum {W, A, S, D}; //wasd 키 enum 변수 (0, 1, 2, 3)





public:

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
	Player(const char* filename = "char/character_sprite.png", int size = 0, int width = 0, int height = 0); //디버깅용 over-load함수
	void ActWalk(Scene* s); //캐릭터를 걷는 모션을 재생한다. (매개 변수를 받으나 사실상 필요하지 않다. NULL 삽입해도 무방)
	void ActIdle(Scene* s); //캐릭터를 가만히 있는 모션을 재생한다. (매개 변수를 받으나 사실상 필요하지 않다.)
	void ActFlip(Scene* p); //캐릭터를 뒤집는 모션을 재생한다. (매개 변수를 받으나 사실상 필요하지 않다.)
};
