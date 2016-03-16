#include "EnemyObject.h"
#include "cocos2d.h"
#include "Global.h"

EnemyObject::EnemyObject(string name, string resource_path, int hp, int mp, int speed) :name(name), hp(hp), mp(mp), speed(speed) { 
	sprite = Sprite::create(resource_path);
	width = sprite->getContentSize().width;
	height = sprite->getContentSize().height;
	position.set(0.0f, 0.0f);
}

void EnemyObject::spawn(Vec2& position, Scene* s) {
	s->addChild(sprite);
	sprite->setOpacity(127);
	sprite->setPosition(position);
	auto spawn = Sprite::create("char/spawn.png");

	s->addChild(spawn);
	spawn->setPosition(position);

	auto spawn_texture2D = spawn->getTexture();
	Animation *anim = Animation::create();
	anim->setDelayPerUnit(0.1f);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			anim->addSpriteFrameWithTexture(spawn_texture2D, Rect(j * 166, i * 172, 166, 172));
		}
	}
	Animate * animCC = Animate::create(anim);
	Sequence * cst = Sequence::create(animCC, CallFunc::create(CC_CALLBACK_0(EnemyObject::setAlpha, this)),NULL);
	spawn->runAction(cst);
}

void EnemyObject::setAlpha() {
	sprite->setOpacity(255);
}

void EnemyObject::setPosition(Vec2& point) {
	position.set(point);
	sprite->setPosition(position);
}
Vec2& EnemyObject::getPosition() {
	return position;
}

void EnemyObject::sendDamage() {

}

void EnemyObject::receiveDamage(double enegy_joule) {

}

EnemyObject::~EnemyObject() {

}