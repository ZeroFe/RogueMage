#include "Rocket.h"
#include "cocos2d.h"
#include "Global.h"
#include "data_recources.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;


Rocket::Rocket(Scene * ob, Vec2 & startPos, double angle) {
	vx = vy = 0;
	speed = 25;
	lifecycleTime = 3000;
	this->ob = ob;
	this->startPos.set(startPos);
	this->angle = angle;
	int angleDiffList[8] = { -90, -60, -30, -15, 30, 60, 90 };
	for (int i = 0; i < 8; i++) {
		//-90 -60 -30 -15 15 30 60 90
		/*
		f(0) = ���� -90
		f(1) = ���� -60 
		...
		*/
		arrow[i] = Sprite::create(resData::recources[resData::PARTICLE_ROCKET]);
		arrow[i]->setScale(0.5f);
		arrow[i]->setRotation(angle + angleDiffList[i]);
		arrow[i]->setPosition(startPos);
		ob->addChild(this); //�̰� ���ٸ� �����췯�� �������� �ʴ´�.
		ob->addChild(this->arrow[i]);
	}

}

Rocket::~Rocket() {
	log("deleted");
	for (int i = 0; i < 8; i++)
		arrow[i]->release();
}

void Rocket::launch(int _level) {
	level = _level;
	SimpleAudioEngine::getInstance()->playEffect("sound/demo.wav");
	this->schedule(schedule_selector(Rocket::update2)); //�������� �Ǵ� (�� 1/60�ʿ� 1�� �����)
}

void Rocket::update2(float dt) {
	int angleDiffList[8] = { -90, -60, -30, -15, 30, 60, 90 };
	int vx[8] = { 0, };
	int vy[8] = { 0, };
	for (int i = 0; i < 8; i++) {
		double angleR = CC_DEGREES_TO_RADIANS(angle + angleDiffList[i]);
		vx[i] += speed * cos(angleR);
		vy[i] -= speed * sin(angleR);
		this->arrow[i]->setOpacity(rand()%256);
		this->arrow[i]->setPosition(this->arrow[i]->getPosition() + Vec2(vx[i], vy[i]));
	}
	lifecycleTime -= Global::fps;
	if (lifecycleTime < 0) {
		log("stopped");
		this->unschedule(schedule_selector(Rocket::update2));
	}
}