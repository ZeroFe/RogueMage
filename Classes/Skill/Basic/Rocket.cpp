#include "Rocket.h"
#include "cocos2d.h"
#include "data_recources.h"
USING_NS_CC;

Rocket::Rocket(Scene * ob, Vec2 & startPos, double angle) {
	this->ob = ob;
	this->startPos.set(startPos);
	this->angle = angle;
	arrow = Sprite::create(resData::recources[resData::PARTICLE_ROCKET]);
}

void Rocket::launch() {
	
}