#include "Player.h"
#include "Global.h"

Player::Player(Sprite *pObj) {
	player = pObj;
	fliping = false;
	stz = true; //character 안정화
}

Sprite* Player::get() {
	return player;
}

void Player::setflipingFalse(void) {
	log("call graph");
	fliping = false;
}

void Player::eval() {
	if (!fliping) {
		if(!stz)
			ActIdle();
	}
}

//플레이어의 방향 전환 자세를 취함
void Player::ActFlip(int direction) {
	fliping = true;
	stz = false;
	player->stopAllActions();
	float rotateto = -1.0f;
	if (direction == RIGHT)
		rotateto = -rotateto;
	auto myAction = ScaleTo::create(0.2f, rotateto, 1.0f, 1.0f); //rotation
	auto mySkew = SkewTo::create(0.3f, 15.0f, 0.0f);//flip
	auto Actions = Spawn::create(myAction, mySkew, NULL);
	auto Sequence = Sequence::create(Actions, CallFunc::create(CC_CALLBACK_0(Player::setflipingFalse, this)), NULL);
	player->runAction(Sequence);
}

//플레이어가 이동 중인 자세를 취함 (사용안함)
void Player::ActWalk(void) { }

//플레이어가 가만히 서 있는 자세를 취함
void Player::ActIdle(void) {
		stz = true;
		player->stopAllActions();
		auto skew1 = SkewTo::create(0.3f, 5.0f, 0.0f);
		auto skew2 = SkewTo::create(0.3f, -5.0f, 0.0f);
		auto regression = SkewTo::create(0.3f, 0.0f, 0.0f);
		auto skew1EaseOut = EaseOut::create(skew1, 2.0f);
		auto skew2EaseOut = EaseOut::create(skew2, 2.0f);
		auto regressionEaseOut = EaseOut::create(regression, 2.0f);
		auto action = Sequence::create(skew1EaseOut, regressionEaseOut, DelayTime::create(0.1f), skew2EaseOut, regressionEaseOut, DelayTime::create(0.1f), NULL);
		auto rep = RepeatForever::create(action);
		player->runAction(rep);
}