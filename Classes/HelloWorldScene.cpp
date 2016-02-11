#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "Global.h"
#include "data_recources.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	rootNode = CSLoader::createNode(Global::mapName);
	map = (TMXTiledMap *)rootNode->getChildByName("gameMap");
	objects = map->getObjectGroup("Spawnlist");
	addChild(rootNode);


	//test
	log("current Position : %d %d", Global::currentPosX, Global::currentPosY);
	auto pLabel = LabelTTF::create(Global::mapName, "Arial", 34);
	pLabel->setPosition(Point(240, 360));
	pLabel->setColor(Color3B(255, 255, 255));
	this->addChild(pLabel);

	//벽 등의 메타데이터 뽑아보기
	metainfo = map->getLayer("Tile Layer 1");


	//1. HUD 생성
	HUD = Sprite::create("char/hud2.png");
	HUD->setAnchorPoint(Point(0, 1));
	HUD->setPosition(Point(0, 960));
	rootNode->addChild(HUD);
	//2. Player 생성 && Player Object 생성
	playerSprite = Sprite::create("char/playable.png");
	rootNode->addChild(HUD);
	rootNode->addChild(playerSprite);
	const char* startPos[] = {
		"start", "SpawnDown", "SpawnUp", "SpawnLeft", "SpawnRigh"
	};
	int x = objects->getObject(startPos[Global::prevEnterPos + 1])["x"].asInt();
	int y = objects->getObject(startPos[Global::prevEnterPos + 1])["y"].asInt();
	playerSprite->setPosition(Point(x, y));
	playerObj = new Player(playerSprite);
	playerObj->ActIdle((Scene*)rootNode);

	//3. minimap 그리기
	auto minimap_room = SpriteBatchNode::create("res/50x29map.png", 50);
	Point hudPos = Point(900, 700);
	minimap_room->setPosition(hudPos);
	rootNode->addChild(minimap_room, 0, 1);

	auto minimap_room_texture = minimap_room->getTexture();

	Point centerPoint(0, 0); //추후에 변동할.
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (Global::mapData[i][j] != '\0') {
				auto pTemp = Sprite::createWithTexture(minimap_room_texture);
				pTemp->setPosition(Point(centerPoint.x + i * 50, centerPoint.y + j * 29));
				if (i == Global::currentPosX && j == Global::currentPosY) {
					pTemp->setColor(Color3B::RED);
					//pTemp->setOpacity(127);

					//전부 내위치를 기준으로 재조정해라.
				//	centerPoint.x = hudPos.x + 290 / 2;
				//	centerPoint.y = hudPos.y + 200 / 2;

					for (int k = 0; k < 10; k++) {
						for (int t = 0; t < 10; t++) {
							//pTemp->setPosition(Point(centerPoint.x + k * 50, centerPoint.y + t * 29));
						}
					}
				}
				minimap_room->addChild(pTemp);
			}
		}
	}
	//4. 플레이어 무빙 설정
	//player moving init
	Player *p = playerObj;//변수 길게 쓰기 귀찮아서 추가한 지역 변수
	p->walkSpeed = 30.0;
	p->f = 0.8;
	p->colMove = 1;
	p->vx = 0;
	p->vy = 0;
	p->power = 0.7;
	Global::key[W] = false;
	Global::key[A] = false;
	Global::key[S] = false;
	Global::key[D] = false;

	this->schedule(schedule_selector(HelloWorld::enterFrame)); //지속적인 판단 (약 1/60초에 1번 실행됨)
	return true;
}

Point HelloWorld::tileCoordForPosition(Point position) {
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
	return Point(x, y);
}

void HelloWorld::enterFrame(float dt) {
	Player *p = playerObj;
	if (!Global::key[1] && playerObj->vx < -0.0f && playerObj->vx > -0.08f) {
		playerObj->vx = abs(playerObj->vx);
	}

	p->vx *= p->f;
	p->vy *= p->f;
	playerSprite->setPosition(Point(playerSprite->getPositionX() + p->vx, playerSprite->getPositionY() + p->vy));
	if (Global::key[1]) {
		p->vx -= p->power;
	}
	if (Global::key[3]) {
		p->vx += p->power;
	}
	if (Global::key[0]) {
		p->vy += p->power;
	}
	if (Global::key[2]) {
		p->vy -= p->power;
	}

	//충돌체크 
	//현재 유저위치의 tile-gid 구하기
	//int hitType; //Hit 점을 분산하여 체크한다. (캐릭터의 하단중앙, 하단왼쪽, 하단오른쪽 => 벽 체크용)
				 //중앙점 포함의 경우 : 중앙
				 //Point tileCoord = this->tileCoordForPosition(player->getPosition());
	
	Point pos0 = Point(playerSprite->getPositionX(), playerSprite->getPositionY());
	Point tileCoord0 = this->tileCoordForPosition(pos0);
	int tileGid0 = this->metainfo->getTileGIDAt(tileCoord0);


	Point pos1 = Point(playerSprite->getPositionX() + playerSprite->getContentSize().width / 3, playerSprite->getPositionY());
	Point tileCoord1 = this->tileCoordForPosition(pos1);
	int tileGid1 = this->metainfo->getTileGIDAt(tileCoord1);

	Point pos2 = Point(playerSprite->getPositionX() - playerSprite->getContentSize().width / 3, playerSprite->getPositionY());
	Point tileCoord2 = this->tileCoordForPosition(pos2);
	int tileGid2 = this->metainfo->getTileGIDAt(tileCoord2);


	if (tileGid0 == 64 || tileGid0 == 65 || tileGid0 == 78 || tileGid0 == 79) {
		playerSprite->setPositionX(playerSprite->getPositionX() + p->colMove); //정면 왼충돌 (벽이 왼쪽에 있는 경우에 유효)
		p->vx = 0; //~cont
		p->vy = 0; //~cont
		playerSprite->setPositionY(playerSprite->getPositionY() + p->colMove); //정면 아래충돌 (벽이 아래에 있는 경우에 유효)
		return;
	} else {
		playerSprite->setOpacity(255);
	}

	if (tileGid1 == 64 || tileGid1 == 65 || tileGid1 == 78 || tileGid1 == 79) {
		playerSprite->setPositionX(playerSprite->getPositionX() - p->colMove); //정면 왼충돌 (벽이 왼쪽에 있는 경우에 유효)
		p->vx = 0; //~cont
		p->vy = 0; //~cont
		playerSprite->setPositionY(playerSprite->getPositionY() - p->colMove); //정면 아래충돌 (벽이 아래에 있는 경우에 유효)
		return;
	}
	else {
		playerSprite->setOpacity(255);
	}

	if (tileGid2 == 64 || tileGid2 == 65 || tileGid2 == 78 || tileGid2 == 79) {
		playerSprite->setPositionX(playerSprite->getPositionX() + p->colMove); //정면 왼충돌 (벽이 왼쪽에 있는 경우에 유효)
		p->vx = 0; //~cont
		p->vy = 0; //~cont
		playerSprite->setPositionY(playerSprite->getPositionY() + p->colMove); //정면 아래충돌 (벽이 아래에 있는 경우에 유효)
		return;
	}
	else {
		playerSprite->setOpacity(255);
	}
}

TransitionScene* HelloWorld::transition(int direction, float t, Scene * s)
{
	Director::getInstance()->setDepthTest(false);
	switch (direction) {
	case 0:
		return TransitionSlideInB::create(t, s);
	case 1:
		return TransitionSlideInT::create(t, s);
	case 2:
		return TransitionSlideInL::create(t, s);
	case 3:
		return TransitionSlideInR::create(t, s);
	}
	return TransitionPageTurn::create(t, s, false);
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	//키보드 입력으로 캐릭터 움직이기
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);
}

void HelloWorld::onExit()
{
	//_eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);
	delete playerObj;
	Layer::onExit();
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {
	//	enterFrame();
	playerObj->ActFlip((Scene*)rootNode);
	switch (keyCode) {
		//후에 MAP 자료구조 도입 예정
	case EventKeyboard::KeyCode::KEY_W:
		Global::key[W] = true;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		Global::key[A] = true;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		Global::key[S] = true;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		Global::key[D] = true;
		break;
	}

}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_W:
		Global::key[W] = false;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		Global::key[A] = false;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		Global::key[S] = false;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		Global::key[D] = false;
		break;
	}
	//밑내용은 디버그용
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		log("down");
		if (moveable(0)) {
			moveScene(0);
		}
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		log("up");
		if (moveable(1)) {
			moveScene(1);
		}
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		log("left");
		if (moveable(2)) {
			moveScene(2);
		}
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		log("right");
		if (moveable(3)) {
			moveScene(3);
		}
		break;
	}
	
	playerObj->ActIdle((Scene*)rootNode);
}


bool HelloWorld::moveable(int direction) {
	//down, up, left, right
	int ccx, ccy;
	if (direction == 0) {
		ccx = Global::currentPosX;
		ccy = Global::currentPosY - 1;
	}
	else if (direction == 1) {
		ccx = Global::currentPosX;
		ccy = Global::currentPosY + 1;
	}
	else if (direction == 2) {
		ccx = Global::currentPosX - 1;
		ccy = Global::currentPosY;
	}
	else if (direction == 3) {
		ccx = Global::currentPosX + 1;
		ccy = Global::currentPosY;
	}
	if (ccx < 10 && ccy < 10 && ccx > -1 && ccy > -1 && '\0' != Global::mapData[ccx][ccy] && '\0' != Global::mapData[ccx][ccy])
		return true;
	return false;
}

void HelloWorld::moveScene(int direction) {
	//down, up, left, right
	int ccx, ccy;
	if (direction == 0) {
		ccx = Global::currentPosX;
		ccy = Global::currentPosY - 1;
		Global::prevEnterPos = 1;
	}
	else if (direction == 1) {
		ccx = Global::currentPosX;
		ccy = Global::currentPosY + 1;
		Global::prevEnterPos = 0;
	}
	else if (direction == 2) {
		ccx = Global::currentPosX - 1;
		ccy = Global::currentPosY;
		Global::prevEnterPos = 3;
	}
	else if (direction == 3) {
		ccx = Global::currentPosX + 1;
		ccy = Global::currentPosY;
		Global::prevEnterPos = 2;
	}
	//내위치 갱신
	Global::currentPosX = ccx;
	Global::currentPosY = ccy;
	//장면이동
	strcpy_s(Global::mapName, 256, resData::mapTemplate[Global::mapTemplate[ccx][ccy]]);
	auto nextScene = HelloWorld::createScene();
	auto trans = TransitionTurnOffTiles::create(0.5, nextScene);
	srand(time(NULL));
	playerSprite->setOpacity(0);
	HUD->setOpacity(0);
	Director::getInstance()->replaceScene(transition(direction, 0.5, nextScene));
}