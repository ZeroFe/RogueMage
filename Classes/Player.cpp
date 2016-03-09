#include "Player.h"
#include "Character.h"
#include "Global.h"
#include "Skill/Basic/Rocket.h"

Player::Player(Sprite *pObj) {
	player = pObj;
	fliping = false;
	stz = true; //character ����ȭ
	playerTexture = player->getTexture();
	playerWalk = SpriteBatchNode::create(resData::recources[resData::PLAYER_SPRITE_WALK]);
	playerWalk_texture2D = playerWalk->getTexture();
	//�ɷ�ġ����
	attack = 100;
	defense = 50;
}

Sprite* Player::get() {
	return player;
}

void Player::setflipingFalse(void) {
	fliping = false;
	//�������� �ȱ� �ڼ��� ���Ѵ�.
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

//�÷��̾��� ���� ��ȯ �ڼ��� ����
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
	//�ְ� ȿ���� ��︮�� �����Ƿ� �����Ͽ����ϴ�. / 3�� 8��
	auto Actions = Spawn::create(myAction, NULL);
	auto Sequence = Sequence::create(Actions, CallFunc::create(CC_CALLBACK_0(Player::setflipingFalse, this)), NULL);
	player->runAction(Sequence);
}

void Player::basicAttack(Scene * ob, Vec2& startPos, double angle) {
		//Ư�� ��ġ���� angle�� ������ ���� �߻�
		//Debug : Skill/Basic/Rocket �� �⺻ ��ų�� ������.
		
	Rocket *rocket = new Rocket((Scene*)ob, startPos, angle);
	
	rocket->launch();
}

//�÷��̾ �̵� ���� �ڼ��� ����
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
	animCC->setTag(500); //��������
	player->runAction(animCC);
}

//�÷��̾ ������ �� �ִ� �ڼ��� ����
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