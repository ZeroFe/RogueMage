#include "Global.h"
#include "data_recources.h"
#include "999_draw.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
#define PTM_RATIO 32.0f
using namespace CocosDenshion;

Scene* Scene_draw::createScene() {
	auto scene = Scene::create();
	auto layer = Scene_draw::create();
	scene->addChild(layer);
	return scene;
}

bool Scene_draw::init() {
	bool is_layer_setted = LayerColor::initWithColor(Color4B(0, 0, 0, 255));
	if (!is_layer_setted) return false;

	/*월드 만들기*/
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
	world_ = new b2World(gravity);
	/* 스크린에 맞게 body 구성, edge shape로 외곽 4개의 fixture
	Body : static, dynamic, kinematic 타입
	Shape : Circle, Polygon, Edge 등 2차원 shape.
	Fixture : 밀도(density), 마찰력(friction), 반발계수(restitution)를 설정. shape을 바인딩.
	*/
	b2BodyDef screen_body_def;
	screen_body_def.position.Set(0.0f, 0.0f);

	b2Body *screen_body = world_->CreateBody(&screen_body_def);

	b2EdgeShape screen_edge;
	b2CircleShape pp;
	b2FixtureDef screen_fixture_def;

	screen_fixture_def.shape = &screen_edge; //shape 바인딩

	screen_edge.Set(b2Vec2(0.0f, 0.0f), b2Vec2(Global::screenSizeX / PTM_RATIO, 0));
	screen_body->CreateFixture(&screen_fixture_def);

	screen_edge.Set(b2Vec2(0.0f, 0.0f), b2Vec2(0, Global::screenSizeY / PTM_RATIO));
	screen_body->CreateFixture(&screen_fixture_def);

	screen_edge.Set(b2Vec2(0.0f, Global::screenSizeY / PTM_RATIO), b2Vec2(Global::screenSizeX / PTM_RATIO, Global::screenSizeY / PTM_RATIO));
	screen_body->CreateFixture(&screen_fixture_def);

	screen_edge.Set(b2Vec2(Global::screenSizeX / PTM_RATIO, Global::screenSizeY / PTM_RATIO), b2Vec2(Global::screenSizeX / PTM_RATIO, 0));
	screen_body->CreateFixture(&screen_fixture_def);

	/* 프레임마다 상황을 처리하기 위한 스케쥴러 등록 */
	this->schedule(schedule_selector(Scene_draw::tick));

	
	return true;
}

void Scene_draw::tick(float dt) {
	world_->Step(dt, 10, 10);
	//world_->DrawDebugData();
	//스프라이트도 같이 이동..
	for (b2Body *b = world_->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != NULL) {
			Sprite *sprite = (Sprite *)b->GetUserData();
			sprite->setPosition(ccp(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}

bool Scene_draw::onTouchBegan(Touch* touch, Event* event) {

	return true;
}

void Scene_draw::onTouchMoved(Touch* touch, Event* event) {
	
}

void Scene_draw::onTouchEnded(Touch* touch, Event* event) {
	// 하나의 스프라이트에 대한 body 생성
	// 이미지 생성
	Sprite *icon = Sprite::create(resData::recources[resData::PARTICLE_CLICK]);
	icon->setOpacity(122);
	icon->setPosition(ccp(Global::screenSizeX / 2 - icon->getContentSize().width / 2, Global::screenSizeY / 2 - icon->getContentSize().height / 2));
	this->addChild(icon);

	//위 아이콘과 매칭되는 b2Body 생성, 위치는 meter로 변형해야 된다.
	b2BodyDef icon_body_def;
	icon_body_def.type = b2_dynamicBody;
	icon_body_def.position.Set(icon->getPositionX() / PTM_RATIO, icon->getPositionY() / PTM_RATIO);
	icon_body_def.userData = icon; //유저 데이터 등록

	b2Body *icon_body = world_->CreateBody(&icon_body_def);

	// PolygonShape의 SetAsBox는 스프라이트의 중심점을 잡아주면 된다 */
	b2PolygonShape icon_polygon;
	icon_polygon.SetAsBox(icon->getContentSize().width / PTM_RATIO / 2, icon->getContentSize().width / PTM_RATIO / 2);
	b2FixtureDef icon_fixture_def;
	icon_fixture_def.shape = &icon_polygon; //바인딩2
	icon_fixture_def.density = 1.0f;
	icon_fixture_def.friction = 0.2f;
	icon_fixture_def.restitution = 0.8f;

	icon_body->CreateFixture(&icon_fixture_def);
	//body 생성 완료
	//튀어나간다.
	srand(time(NULL));
	int vx = -30;
	int vy = 40;
	b2Vec2 force = b2Vec2(vx, vy);
	icon_body->ApplyLinearImpulse(force, icon_body_def.position, true);

	icon_body->CreateFixture(&icon_fixture_def);
}

void Scene_draw::ccTouchMoved(CCSet* touches, CCEvent* event) {

}


void Scene_draw::onEnter() {
	LayerColor::onEnter();	
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Scene_draw::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Scene_draw::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Scene_draw::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void Scene_draw::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	LayerColor::onExit();
}

void Scene_draw::addRectangleBetweenPointsToBody(b2Body *body, CCPoint start, CCPoint end) {
	
}