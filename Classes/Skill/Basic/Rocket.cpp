#include "Rocket.h"
#include "cocos2d.h"
#include "Global.h"
#include "data_recources.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;


Rocket::Rocket(Scene * ob, Vec2 & startPos, double angle) {
	vx = vy = 0;
	speed = 5;
	lifecycleTime = 3000;
	this->ob = ob;
	this->startPos.set(startPos);
	this->angle = angle;
	arrow = Sprite::create(resData::recources[resData::PARTICLE_ROCKET]);
	arrow->setScale(0.5f);
	arrow->setRotation(angle);
	arrow->setPosition(startPos);
	ob->addChild(this); //�̰� ���ٸ� �����췯�� �������� �ʴ´�.
	ob->addChild(this->arrow);
}

Rocket::~Rocket() {
	log("deleted");
	arrow->release();
}

void Rocket::launch() {
	SimpleAudioEngine::getInstance()->playEffect("sound/demo.wav");
	this->schedule(schedule_selector(Rocket::update2)); //�������� �Ǵ� (�� 1/60�ʿ� 1�� �����)
}

void Rocket::update2(float dt) {
	double angleR = CC_DEGREES_TO_RADIANS(angle);
	vx += speed * cos(angleR);
	vy -= speed * sin(angleR);
	this->arrow->setPosition(this->arrow->getPosition() + Vec2(vx, vy));
	lifecycleTime -= Global::fps;
	if (lifecycleTime < 0) {
		log("stopped");
		this->unschedule(schedule_selector(Rocket::update2));
	}
}