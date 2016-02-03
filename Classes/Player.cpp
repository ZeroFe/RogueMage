#include "Player.h"

Player::Player(const char* filename, int size, int width, int height) {
	playerSprite = Sprite::create(filename);
	playerTexture = playerSprite->getTexture();
	player = Sprite::createWithTexture(playerTexture, Rect(0, 0, 128, 128));
	player->setTag(TAG_PLAYER);
}

void Player::ActWalk(Scene* p) {
	//눌린상태
	if (currentAction != WALK) {
		//player->runAction(__walk->clone());
		auto player = p->getChildByTag(TAG_PLAYER);
		//p->stopActionByTag(TAG_PLAYER);
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
		auto player = p->getChildByTag(TAG_PLAYER);
		//p->stopActionByTag(TAG_PLAYER);
		player->stopAllActions();
		Animation* animation = Animation::create();
		animation->setDelayPerUnit(0.3f);
		animation->addSpriteFrameWithTexture(playerTexture, Rect(0 * 128, 2 * 128, 128, 128));
		animation->addSpriteFrameWithTexture(playerTexture, Rect(1 * 128, 2 * 128, 128, 128));
		auto am = Animate::create(animation);
		auto cc = RepeatForever::create(am);
		player->runAction(cc);
		currentAction = IDLE;
	}
}

Sprite* Player::get() {
	return player;
}