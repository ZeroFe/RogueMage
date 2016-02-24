#include "Player.h"
#include "Global.h"

Player::Player(Sprite *pObj) {
	playerSprite = pObj;//내부변수에 Sprite* 저장
	player = playerSprite;
	player->setName("Player");
	lookAt = -1; //플레이어가 바라보는 방향이다. -1 : 오른쪽
	currentAction = -1; //플레이어가 현재 취하는 액션
	fliping = false;
}

Player::Player(const char* filename, int size, int width, int height) {
	playerSprite = Sprite::create(filename);
	playerTexture = playerSprite->getTexture();
	player = Sprite::createWithTexture(playerTexture, Rect(0, 0, 128, 128));
	player->setName("Player");
	lookAt = -1;
	currentAction = -1;
}

void Player::falseFlip(void) {
	fliping = false;
	ActIdle(NULL);
}

void Player::ActFlip(Scene* p) {
	//Single-sprite-walking Act.
	if (currentAction != FLIP) {
		player->stopAllActions(); //진행중인 다른 Action을 정지해야 다른 액션을 취할 수있다.
		fliping = true; 
		if (Global::key[D]) {
			auto myAction = ScaleTo::create(0.2f, -1.0f, 1.0f, 1.0f); //rotation
			auto mySkew = SkewTo::create(0.3f, 15.0f, 0.0f);//flip
			auto Actions = Spawn::create(myAction, mySkew, NULL);
			auto Sequence = Sequence::create(Actions, CallFunc::create(CC_CALLBACK_0(Player::falseFlip, this)), NULL);
			player->runAction(Sequence);
			lookAt = 0;
			currentAction = FLIP;
		}
		else if (Global::key[A]) {
			auto myAction = ScaleTo::create(0.2f, 1.0f, 1.0f, 1.0f); //rotation
			auto mySkew = SkewTo::create(0.3f, 15.0f, 0.0f);//flip
			auto Actions = Spawn::create(myAction, mySkew, NULL);
			auto Sequence = Sequence::create(Actions, CallFunc::create(CC_CALLBACK_0(Player::falseFlip, this)), NULL);
			player->runAction(Sequence);
			lookAt = -1;
			currentAction = FLIP;
		}
		else {
			//only skew
			if (lookAt == -1) {
				auto mySkew = SkewTo::create(0.3f, 15.0f, 0.0f);//flip
				player->runAction(mySkew);
			} else {
				auto mySkew = SkewTo::create(0.3f, 15.0f, 0.0f);//flip
				player->runAction(mySkew);
			}
		}
	}
}

void Player::ActWalk(Scene* p) {
	//눌린상태
	if (currentAction != WALK) {
		player->stopAllActions();
		Animation* animation = Animation::create();
		animation->setDelayPerUnit(0.3f);
		for (int i = 0; i < 8; i++)
			animation->addSpriteFrameWithTexture(playerTexture, Rect(i * 128, 0, 128, 128));
		auto am = Animate::create(animation);
		auto cc = RepeatForever::create(am);
		player->runAction(cc);
		currentAction = WALK;
	}
}

void Player::ActIdle(Scene* p) {
	if (currentAction != IDLE) {
		player->stopAllActions();

		auto skew1 = SkewTo::create(0.3f, 5.0f, 0.0f);
		auto skew2 = SkewTo::create(0.3f, -5.0f, 0.0f);
		auto regression = SkewTo::create(0.3f, 0.0f, 0.0f);
		auto skew1EaseOut = EaseOut::create(skew1, 2.0f);
		auto skew2EaseOut = EaseOut::create(skew2, 2.0f);
		auto regressionEaseOut = EaseOut::create(regression, 2.0f);
		//skew1->skew2->regression ->repeat
		auto action = Sequence::create(skew1EaseOut, regressionEaseOut, DelayTime::create(0.1f), skew2EaseOut, regressionEaseOut, DelayTime::create(0.1f), NULL);
		auto rep = RepeatForever::create(action);
		player->runAction(rep);
		currentAction = IDLE;
	}
}

Sprite* Player::get() {
	return player;
}