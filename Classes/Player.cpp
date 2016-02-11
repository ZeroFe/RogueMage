#include "Player.h"

Player::Player(Sprite *pObj) {
	playerSprite = pObj; //Adjsust . db.
	player = playerSprite; //그대로 대입 (스프라이트가 변하지 않는다.)
						   //playerTexture = playerSprite->getTexture();
						   //player = Sprite::createWithTexture(playerTexture, Rect(0, 0, 66, 193));
	player->setName("Player");
	int lookAt = -1; //right
	currentAction = -1;
}

Player::Player(const char* filename, int size, int width, int height) {
	playerSprite = Sprite::create(filename);
	playerTexture = playerSprite->getTexture();
	player = Sprite::createWithTexture(playerTexture, Rect(0, 0, 128, 128));
	player->setName("Player");
	int lookAt = -1; //right
	currentAction = -1;
}

void Player::ActFlip(Scene* p) {
	//Single-sprite-walking Act.
	if (currentAction != FLIP) {
		player->stopAllActions();
		//auto myAction = ScaleTo::create(0.5, -1.0f);

		if (lookAt == -1) {
			auto myAction = ScaleTo::create(0.2f, -1.0f, 1.0f, 1.0f); //rotation
			auto mySkew = SkewTo::create(0.3f, 15.0f, 0.0f);//flip
			auto Actions = Spawn::create(myAction, mySkew, NULL);
			player->runAction(Actions);
			lookAt = 0;
		}
		else {
			auto myAction = ScaleTo::create(0.2f, 1.0f, 1.0f, 1.0f); //rotation
			auto mySkew = SkewTo::create(0.3f, 15.0f, 0.0f);//flip
			auto Actions = Spawn::create(myAction, mySkew, NULL);
			player->runAction(Actions);
			lookAt = -1;
		}




		currentAction = FLIP;
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