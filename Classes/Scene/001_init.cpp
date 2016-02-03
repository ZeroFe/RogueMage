#include "Global.h"
#include "data_recources.h"
#include "001_init.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* Scene_init::createScene() {
	auto scene = Scene::create();
	auto layer = Scene_init::create();
	scene->addChild(layer);
	return scene;
}

bool Scene_init::init() {
	bool is_layer_setted = LayerColor::initWithColor(Color4B(50, 21, 12, 255));
	if (!is_layer_setted) return false;

	//�� ����
	auto map = TMXTiledMap::create(resData::recources[resData::MAP0]);
	this->addChild(map, 0, 11);

	//�÷��̾� ����
	playerObj = new Player();
	player = playerObj->get();
	player->setPosition(Point(500, 200));
	this->addChild(player);
	playerObj->ActIdle((Scene*)this);
	log("%p", playerObj);

	//�÷��̾� �̵��� ī�޶� (this) ���󰡱�
	Point origin = Director::sharedDirector()->getVisibleOrigin();
	Size size = Director::sharedDirector()->getVisibleSize(); //��ũ�� ������
	Point center = Point(size.width / 2 + origin.x, size.height / 2 + origin.y);
	Sprite *followObj = player;
	float playfield_width = size.width * 2.0f;
	float playfield_height = size.height * 2.0f;

	//+enterFrame �� ���� �Լ�ȣ��
	//auto enterFrameV = Sequence::create(DelayTime::create(0.03f), CallFunc::create(CC_CALLBACK_0(Pinit::enterFrame, this)), Follow::create(followObj, Rect(center.x - playfield_width / 2, center.y - playfield_height / 2, playfield_width, playfield_height)), NULL);
	this->runAction(Follow::create(followObj, Rect(center.x - playfield_width / 2, center.y - playfield_height / 2, playfield_width, playfield_height)));
	return true;
}

bool Scene_init::onTouchBegan(Touch* touch, Event* event) {
	Point touchLocation = this->convertTouchToNodeSpace(touch);
	doClick(touchLocation);
	//log("%d, %d\n", touch->getLocation()., touch->getLocation().y);
	//playerObj->ActWalk();
	return true;
}

void Scene_init::doClick(Point& location) {
	ParticleSystem* clickParticle = ParticleFlower::create();
	auto texture = Director::getInstance()->getTextureCache()->addImage(resData::recources[resData::PARTICLE_CLICK]);
	clickParticle->setTexture(texture);
	if (clickParticle) {
		clickParticle->setScale(0.5f);
		clickParticle->setDuration(0.1f);
		clickParticle->setPosition(location);
		this->addChild(clickParticle);
	}
}


void Scene_init::onEnter() {
	LayerColor::onEnter();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Scene_init::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//Ű���� �Է����� ĳ���� �����̱�
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(Scene_init::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(Scene_init::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);
}

void Scene_init::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	_eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);
	LayerColor::onExit();
}

void Scene_init::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	//	enterFrame();
	playerObj->ActWalk((Scene*)this);
	log("%p", playerObj);
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_W:
		//player->setPosition(0, 0);
		break;

	}
}

void Scene_init::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	playerObj->ActIdle((Scene*)this);
}