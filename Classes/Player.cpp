#include "Player.h"
#include "Character.h"
#include "Global.h"
#include "Skill/Basic/Rocket.h"

Player::Player(Sprite *pObj) {
	player = pObj;
	fliping = false;
	stz = true; //character 안정화
	playerTexture = player->getTexture();
	playerWalk = SpriteBatchNode::create(resData::recources[resData::PLAYER_SPRITE_WALK]);
	playerWalk_texture2D = playerWalk->getTexture();
	//능력치설정
	attack = 100;
	defense = 50;
}

Sprite* Player::get() {
	return player;
}

void Player::setflipingFalse(void) {
	fliping = false;
	//다했으면 걷기 자세를 취한다.
	ActWalk();
}

void Player::stabilization() {
	if (!Global::key[A] && !Global::key[D]) {
		if (!fliping) {
			if (!stz)
				ActIdle();
		}
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
	//auto mySkew = SkewTo::create(0.3f, 15.0f, 0.0f);//flip
	//auto Actions = Spawn::create(myAction, mySkew, NULL);
	//왜곡 효과가 어울리지 않으므로 삭제하였습니다. / 3월 8일
	auto Actions = Spawn::create(myAction, NULL);
	auto Sequence = Sequence::create(Actions, CallFunc::create(CC_CALLBACK_0(Player::setflipingFalse, this)), NULL);
	player->runAction(Sequence);
}

void Player::basicAttack(Scene * ob, Vec2& startPos, double angle) {
		//특정 위치에서 angle의 각도로 마법 발사
		//Debug : Skill/Basic/Rocket 를 기본 스킬로 가정함.
		
	Rocket *rocket = new Rocket((Scene*)ob, startPos, angle);
	
	rocket->launch();
}

//플레이어가 이동 중인 자세를 취함
void Player::ActWalk(void) {
	log("Walk Action Runs");
	Animation *anim = Animation::create();
	anim->setDelayPerUnit(0.5f);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			anim->addSpriteFrameWithTexture(playerWalk_texture2D, Rect(i * 96, j * 96, 96, 96));
		}
	}
	Animate * animCC = Animate::create(anim);
	animCC->setTag(500); //임의지정
	player->runAction(animCC);
}

//플레이어가 가만히 서 있는 자세를 취함
void Player::ActIdle(void) {
		log("stablize");
		stz = true;		
		player->stopAllActions();
		player->stopActionByTag(500);
		
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