#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "Global.h"
#include "data_recources.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	//rootNode = CSLoader::createNode(Global::mapName);
	log("GameScene : init");

	srand(time(NULL));
	rootNode = CSLoader::createNode(resData::mapTemplate[0]);
	//임시맵용 하나만 불러온다
	map = (TMXTiledMap *)rootNode->getChildByName("gameMap"); //cocos studio 에서 정의한 TileMap 이름
	objects = map->getObjectGroup("SpawnList"); //SpawnList Object 그룹 가져옴 (Object 속성일 경우)
	addChild(rootNode);


	//test
	auto pLabel = LabelTTF::create(Global::mapName, "Arial", 34); //Current Map template name
	pLabel->setPosition(Point(300, 80));
	pLabel->setColor(Color3B(255, 255, 255));
	this->addChild(pLabel);

	//벽 등의 메타데이터 뽑아보기
	Wall = map->getObjectGroup("Wall");
	Damage = map->getObjectGroup("Damage");


	//1. HUD 생성
	HUD = new UI_HUD();
	HUD->setPosition(Point(0, 960));
	HUD->draw_minimap();
	this->addChild(HUD->getObject());//주의 : this임

	//2. Player 생성 && Player Object 생성
	playerSprite = Sprite::create("char/playable.png");
	playerSprite->setAnchorPoint(Point(0.5, 0));//0.5 0
	rootNode->addChild(playerSprite);
	const char* startPos[] = {
		"start", "SpawnDown", "SpawnUp", "SpawnLeft", "SpawnRight"
	};
	int x = objects->getObject(startPos[Global::prevEnterPos + 1])["x"].asInt();
	int y = objects->getObject(startPos[Global::prevEnterPos + 1])["y"].asInt();
	playerSprite->setPosition(Point(x, y));
	playerObj = new Player(playerSprite);
	playerObj->ActIdle((Scene*)rootNode);

	//3. minimap 그리기
	/*
	auto minimap_room = SpriteBatchNode::create("res/50x29map.png", 50);
	Point hudPos = Point(1100 - Global::currentPosX * 50, 816 - Global::currentPosY * 29);
	minimap_room->setPosition(hudPos);
	//rootNode->addChild(minimap_room, 0, 1);
	this->addChild(minimap_room, 0, 1);

	auto minimap_room_texture = minimap_room->getTexture();

	Point centerPoint(0, 0); //미니맵을 어디에 표시할 지 결정한다.
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (Global::mapData[i][j] != '\0') {
				auto pTemp = Sprite::createWithTexture(minimap_room_texture);
				pTemp->setPosition(Point(centerPoint.x + i * 50, centerPoint.y + j * 29));
				if (i == Global::currentPosX && j == Global::currentPosY) {
					pTemp->setColor(Color3B::RED);
				}
				minimap_room->addChild(pTemp);
			}
		}
	}
	*/
	//4. 플레이어 무빙 설정
	//player moving init
	Player *p = playerObj;//변수 길게 쓰기 귀찮아서 추가한 지역 변수
	p->walkSpeed = 30.0; //플레이어의 이동 속도
	p->f = 0.8; //플레이어의 반발력 (힘에 대한)
	p->colMove = 1; //벽 등의 오브젝트에 충돌시 안 충돌하기 위해 한 프레임당 밀어낼 픽셀
	p->vx = 0; //velocity X (1f / s) initial Value
	p->vy = 0; //velocity Y (1f / s) initial Value
	p->power = 0.7; //the Power of Force
	Global::key[W] = false; //key 눌림시 True로 스위칭될
	Global::key[A] = false;
	Global::key[S] = false;
	Global::key[D] = false;

	this->schedule(schedule_selector(GameScene::enterFrame)); //지속적인 판단 (약 1/60초에 1번 실행됨)

	//5. 플레이어 공격각도 설정 (8향)
	attackSpotListBatchNode = SpriteBatchNode::create("char/aim.png", 50);
	//int squareMaxth = playerSprite->getContentSize().width > playerSprite->getContentSize().height ? playerSprite->getContentSize().width : playerSprite->getContentSize().height;
	rootNode->addChild(attackSpotListBatchNode);
	aimTexture = new Texture2D*[8]; //메모리 해제 필요 (new 로 생성했으므로 Garbage - Collection이 자동으로 안 됨)
	aimSprite = new Sprite*[8]; //메모리 해제 필요
	for (int i = 0; i < 8; i++) {
		aimTexture[i] = attackSpotListBatchNode->getTexture();
		aimSprite[i] = Sprite::createWithTexture(aimTexture[i]);
		aimSprite[i]->setAnchorPoint(Point(-5, 0));
		aimSprite[i]->setRotation(i * 45);
		attackSpotListBatchNode->addChild(aimSprite[i]);
		//aimSprite[i]->setOpacity(127);
		break; //일단 한개만 (dbg)
	}


	//Enemyes, Objects test
	//test : 1 한 마리의 적 (bug)
	//주인공y좌표 - 적y좌표 , 주인공x좌표 - 적y좌표 (원점 기준으로 맞춰주기 위해 탄젠트의 역함수이다)
	auto enemy1Sprite = Sprite::create("char/enemy.png");
	enemy1Sprite->setAnchorPoint(Point(0.5, 0));//적 역시 standing 자세를 취하고 있다.
	enemy1Sprite->setPosition(Point(330, 300));
	rootNode->addChild(enemy1Sprite);
	return true;
}

Point GameScene::tileCoordForPosition(Point position) {
	//이 함수는 어떠한 위치가 주어지면, 타일맵 기준으로 어떤 타일에 있는지 알아보는 함수이다.
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
	return Point(x, y);
}

void GameScene::enterFrame(float dt) {
	//1초에 약 60번 실행되는 지속 판단 함수이다.

	//공격 방향 지정자
	attackSpotListBatchNode->setPosition(playerSprite->getPosition()); //center of player
	attackSpotListBatchNode->setPositionY(playerSprite->getPositionY() + playerSprite->getContentSize().height / 2.0f);


	Player *p = playerObj; //변수명 줄이기
	if (!Global::key[A] && playerObj->vx < -0.0f && playerObj->vx > -0.08f) {
		playerObj->vx = abs(playerObj->vx);
		//부동소수점 계산오차로 왼쪽 키를 눌렀다 땔 때 캐릭터가 부들거리는 현상을 방지하기위한 추가 코드
	}

	p->vx *= p->f; //반발력만큼 velocity 를 줄여준다.
	p->vy *= p->f; //마찬가지이다.
	playerSprite->setPosition(Point(playerSprite->getPositionX() + p->vx, playerSprite->getPositionY() + p->vy));
	//플레이어의 실제적 위치를 조정
	if (Global::key[A]) {
		p->vx -= p->power;
		//해당 키를 누르면 velocity 를 power만큼 조절한다.
	}
	if (Global::key[D]) {
		p->vx += p->power;
	}
	if (Global::key[W]) {
		p->vy += p->power;
	}
	if (Global::key[S]) {
		p->vy -= p->power;
	}

	//충돌체크 
	if (colideTestPointAndTile(Point(playerSprite->getPositionX(), playerSprite->getPositionY()), Wall)) {
		playerSprite->setOpacity(127);
		//벽과 충돌 시 투명처리했다. (일단)
	}
	else {
		playerSprite->setOpacity(255);
	}


	//각도 조정
	//공격할 곳의 타겟을 잡는 역할
	double playerX = attackSpotListBatchNode->getPositionX();
	double playerY = Global::screenSizeY - attackSpotListBatchNode->getPositionY();
	double diffX = mouseX - playerX;
	double diffY = mouseY - playerY;
	double angle = atan2(diffY, diffX) * 180 / M_PI;
	attackSpotListBatchNode->setRotation(angle);
}

TransitionScene* GameScene::transition(int direction, float t, Scene * s) {
	//장면 전환 효과에 사용되었다. 하지만 이 방식은 HUD도 같이 적용되어 곧 폐기될 예정이다.
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

void GameScene::onEnter() {
	Layer::onEnter();
	//키보드 입력으로 캐릭터 움직이기
	auto mouselistener = EventListenerMouse::create();
	auto keylistener = EventListenerKeyboard::create();

	mouselistener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);
	mouselistener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
	keylistener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouselistener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);
}

void GameScene::onExit()
{
	//_eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);
	delete playerObj; //new로 생성한 Object는 수동으로 메모리를 수거해야 한다.
	delete aimTexture;
	delete aimSprite;
	delete HUD;
	Layer::onExit();
}

void GameScene::onMouseMove(Event *ev) {
	EventMouse *e = (EventMouse*)ev;
	mouseX = e->getLocation().x;
	mouseY = e->getLocation().y;
}


void GameScene::onMouseDown(Event *ev) {
	log("%d %d", mouseX, mouseY);
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {
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

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
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


bool GameScene::moveable(int direction) {
	//down, up, left, right
	//플레이어가 맵을 넘어갈 수 있는지의 여부를 알아보는 함수
	//인수로 방향을 받는다.
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

void GameScene::moveScene(int direction) {
	//down, up, left, right
	//실질적으로 scene을 넘겨준다. (다른 맵으로 넘어간다)
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
	strcpy_s(Global::mapName, 256, resData::mapTemplate[Global::mapTemplate[ccx][ccy]]);

	//다음 장면을 붙여놓는다.
	auto nextMap = TMXTiledMap::create("Scene/GameScene/TileMap/01.tmx"); //임시 디버그 (1)
	MoveBy *transAction;
	log("00");
	switch (direction) {
	case 0:
		log("Herre!");
		nextMap->setPositionY(-704); //위로 올라감 맵이;
		transAction = MoveBy::create(0.5, Point(0, 704));
		break;
	case 1:
		nextMap->setPositionY(704); //아래로 올라감 맵이
		transAction = MoveBy::create(0.5, Point(0, -704));
		break;
	case 2:
		nextMap->setPositionX(-1280); //왼
		transAction = MoveBy::create(0.5, Point(1280, 0));
		break;
	case 3:
		nextMap->setPositionX(1280); //오
		transAction = MoveBy::create(0.5, Point(-1280, 0));
		break;
	}
	rootNode->addChild(nextMap, 10, 11);
	//거기로 애니메이션 한다. (rootNode 와 이동)
//	rootNode->runAction(transAction);
	auto Seq = Sequence::create(transAction, CallFunc::create(CC_CALLBACK_0(GameScene::trans, this)), NULL);
	rootNode->runAction(Seq);
	//장면이동
	//auto Sequence = Sequence::create(Actions, CallFunc::create(CC_CALLBACK_0(Player::falseFlip, this)), NULL);
	//auto nextScene = GameScene::createScene();
	//auto trans = TransitionTurnOffTiles::create(0.5, nextScene);
	//srand(time(NULL));
	playerSprite->setOpacity(0);
	//스케쥴러를 중지한다 (게임 상의 정지)
	this->unschedule(schedule_selector(GameScene::enterFrame));
	//Director::getInstance()->replaceScene(transition(direction, 0.5, nextScene));
}

void GameScene::trans() {
	auto nextScene = GameScene::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

bool GameScene::colideTestPointAndTile(Point & player, TMXObjectGroup * tilePos) {
	//플레이어가 특정 Tile에 있는지 Test한다.
	auto objList = tilePos->getObjects();
	for (int i = 0; i < (int)objList.size(); i++) {
		/*coord 기준은 왼쪽 위가 (0, 0)이다.
		점과 사각형의 충돌판정 공식
		플레이어의 x위치가 coord ~ coord + width 이고,
		플레이어의 y위치가 coord ~ coord + heigh 이면
		충돌이다.
		*/
		auto Object = objList.at(i).asValueMap();
		auto x = Object["x"].asInt();
		auto y = Object["y"].asInt();
		auto width = Object["width"].asInt();
		auto height = Object["height"].asInt();
		//log("%d %d %d %d", x, y, width, height);
		if (player.x > x && player.x < x + width && player.y > y && player.y < y + height) {
			return true;
		}
	}
	return false;
}
