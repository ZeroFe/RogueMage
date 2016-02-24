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
	srand(time(NULL));
	rootNode = CSLoader::createNode("Scene/GameScene/mapTemp01.csb");
	//�ӽøʿ� �ϳ��� �ҷ��´�
	map = (TMXTiledMap *)rootNode->getChildByName("gameMap"); //cocos studio ���� ������ TileMap �̸�
	log("map : %p", map);
	objects = map->getObjectGroup("SpawnList"); //SpawnList Object �׷� ������ (Object �Ӽ��� ���)
	log("Objects : %p", objects);
	addChild(rootNode);


	//test
	log("current Position : %d %d", Global::currentPosX, Global::currentPosY);
	auto pLabel = LabelTTF::create(Global::mapName, "Arial", 34); //Current Map template name
	pLabel->setPosition(Point(300, 80));
	pLabel->setColor(Color3B(255, 255, 255));
	this->addChild(pLabel);

	//�� ���� ��Ÿ������ �̾ƺ���
	Wall = map->getObjectGroup("Wall");
	Damage = map->getObjectGroup("Damage");


	//1. HUD ����
	HUD = Sprite::create("char/hud2.png");
	HUD->setAnchorPoint(Point(0, 1));
	HUD->setPosition(Point(0, 960));
	rootNode->addChild(HUD);

	//2. Player ���� && Player Object ����
	playerSprite = Sprite::create("char/playable.png");
	playerSprite->setAnchorPoint(Point(0.5, 0));//0.5 0
	rootNode->addChild(HUD);
	rootNode->addChild(playerSprite);
	const char* startPos[] = {
		"start", "SpawnDown", "SpawnUp", "SpawnLeft", "SpawnRight"
	};
	int x = objects->getObject(startPos[Global::prevEnterPos + 1])["x"].asInt();
	int y = objects->getObject(startPos[Global::prevEnterPos + 1])["y"].asInt();
	playerSprite->setPosition(Point(x, y));
	playerObj = new Player(playerSprite);
	playerObj->ActIdle((Scene*)rootNode);

	//3. minimap �׸���
	auto minimap_room = SpriteBatchNode::create("res/50x29map.png", 50);
	Point hudPos = Point(900, 700);
	minimap_room->setPosition(hudPos);
	rootNode->addChild(minimap_room, 0, 1);

	auto minimap_room_texture = minimap_room->getTexture();

	Point centerPoint(0, 0); //�̴ϸ��� ��� ǥ���� �� �����Ѵ�.
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
	//4. �÷��̾� ���� ����
	//player moving init
	Player *p = playerObj;//���� ��� ���� �����Ƽ� �߰��� ���� ����
	p->walkSpeed = 30.0; //�÷��̾��� �̵� �ӵ�
	p->f = 0.8; //�÷��̾��� �ݹ߷� (���� ����)
	p->colMove = 1; //�� ���� ������Ʈ�� �浹�� �� �浹�ϱ� ���� �� �����Ӵ� �о �ȼ�
	p->vx = 0; //velocity X (1f / s) initial Value
	p->vy = 0; //velocity Y (1f / s) initial Value
	p->power = 0.7; //the Power of Force
	Global::key[W] = false; //key ������ True�� ����Ī��
	Global::key[A] = false;
	Global::key[S] = false;
	Global::key[D] = false;

	this->schedule(schedule_selector(GameScene::enterFrame)); //�������� �Ǵ� (�� 1/60�ʿ� 1�� �����)



	//5. �÷��̾� ���ݰ��� ���� (8��)
	attackSpotListBatchNode = SpriteBatchNode::create("char/aim.png", 50);
	//int squareMaxth = playerSprite->getContentSize().width > playerSprite->getContentSize().height ? playerSprite->getContentSize().width : playerSprite->getContentSize().height;
	rootNode->addChild(attackSpotListBatchNode);
	aimTexture = new Texture2D*[8]; //�޸� ���� �ʿ� (new �� ���������Ƿ� Garbage - Collection�� �ڵ����� �� ��)
	aimSprite = new Sprite*[8]; //�޸� ���� �ʿ�
	for (int i = 0; i < 8; i++) {
		aimTexture[i] = attackSpotListBatchNode->getTexture();
		aimSprite[i] = Sprite::createWithTexture(aimTexture[i]);
		aimSprite[i]->setAnchorPoint(Point(-5, 0));
		aimSprite[i]->setRotation(i * 45);
		attackSpotListBatchNode->addChild(aimSprite[i]);
		//aimSprite[i]->setOpacity(127);
		break; //�ϴ� �Ѱ��� (dbg)
	}


	//Enemyes, Objects test
	//test : 1 �� ������ �� (bug)
	//���ΰ�y��ǥ - ��y��ǥ , ���ΰ�x��ǥ - ��y��ǥ (���� �������� �����ֱ� ���� ź��Ʈ�� ���Լ��̴�)
	auto enemy1Sprite = Sprite::create("char/enemy.png");
	enemy1Sprite->setAnchorPoint(Point(0.5, 0));//�� ���� standing �ڼ��� ���ϰ� �ִ�.
	enemy1Sprite->setPosition(Point(330, 300));
	rootNode->addChild(enemy1Sprite);
	return true;
}

Point GameScene::tileCoordForPosition(Point position) {
	//�� �Լ��� ��� ��ġ�� �־�����, Ÿ�ϸ� �������� � Ÿ�Ͽ� �ִ��� �˾ƺ��� �Լ��̴�.
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
	return Point(x, y);
}

void GameScene::enterFrame(float dt) {
	//1�ʿ� �� 60�� ����Ǵ� ���� �Ǵ� �Լ��̴�.

	//���� ���� ������
	attackSpotListBatchNode->setPosition(playerSprite->getPosition()); //center of player
	attackSpotListBatchNode->setPositionY(playerSprite->getPositionY() + playerSprite->getContentSize().height / 2);


	Player *p = playerObj; //������ ���̱�
	if (!Global::key[A] && playerObj->vx < -0.0f && playerObj->vx > -0.08f) {
		playerObj->vx = abs(playerObj->vx);
		//�ε��Ҽ��� �������� ���� Ű�� ������ �� �� ĳ���Ͱ� �ε�Ÿ��� ������ �����ϱ����� �߰� �ڵ�
	}

	p->vx *= p->f; //�ݹ߷¸�ŭ velocity �� �ٿ��ش�.
	p->vy *= p->f; //���������̴�.
	playerSprite->setPosition(Point(playerSprite->getPositionX() + p->vx, playerSprite->getPositionY() + p->vy));
	//�÷��̾��� ������ ��ġ�� ����
	if (Global::key[A]) {
		p->vx -= p->power;
		//�ش� Ű�� ������ velocity �� power��ŭ �����Ѵ�.
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

	//�浹üũ 
	if (colideTestPointAndTile(Point(playerSprite->getPositionX(), playerSprite->getPositionY()), Wall)) {
		playerSprite->setOpacity(127);
		//���� �浹 �� ����ó���ߴ�. (�ϴ�)
	}
	else {
		playerSprite->setOpacity(255);
	}
}

TransitionScene* GameScene::transition(int direction, float t, Scene * s) {
	//��� ��ȯ ȿ���� ���Ǿ���. ������ �� ����� HUD�� ���� ����Ǿ� �� ���� �����̴�.
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
	//Ű���� �Է����� ĳ���� �����̱�
	auto mouselistener = EventListenerMouse::create();
	auto keylistener = EventListenerKeyboard::create();

	mouselistener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);
	keylistener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouselistener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);
}

void GameScene::onExit()
{
	//_eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);
	delete playerObj; //new�� ������ Object�� �������� �޸𸮸� �����ؾ� �Ѵ�.
	delete aimTexture;
	delete aimSprite;
	Layer::onExit();
}

void GameScene::onMouseMove(Event *ev) {
	EventMouse *e = (EventMouse*)ev;
	mouseX = e->getLocation().x;
	mouseY = e->getLocation().y;
	//Global::mouseX = mouseX;
	//Global::mouseY = mouseY;
	/*
	int playerX = playerSprite->getPositionX();
	int playerY = playerSprite->getPositionY();
	int diffX = mouseX - playerX;
	int diffY = mouseY - playerY;
	double angle = abs(atan2(diffY, diffX)) * 180 / 3.1415926535;
	log("%lf", angle);
	attackSpotListBatchNode->setRotation(angle);
	*/
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {
	//	enterFrame();
	playerObj->ActFlip((Scene*)rootNode);
	switch (keyCode) {
		//�Ŀ� MAP �ڷᱸ�� ���� ����
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
	//�س����� ����׿�
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
	//�÷��̾ ���� �Ѿ �� �ִ����� ���θ� �˾ƺ��� �Լ�
	//�μ��� ������ �޴´�.
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
	//���������� scene�� �Ѱ��ش�. (�ٸ� ������ �Ѿ��)
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
	//����ġ ����
	Global::currentPosX = ccx;
	Global::currentPosY = ccy;
	//����̵�
	strcpy_s(Global::mapName, 256, resData::mapTemplate[Global::mapTemplate[ccx][ccy]]);
	auto nextScene = GameScene::createScene();
	auto trans = TransitionTurnOffTiles::create(0.5, nextScene);
	srand(time(NULL));
	playerSprite->setOpacity(0);
	HUD->setOpacity(0);
	Director::getInstance()->replaceScene(transition(direction, 0.5, nextScene));
}

bool GameScene::colideTestPointAndTile(Point & player, TMXObjectGroup * tilePos) {
	//�÷��̾ Ư�� Tile�� �ִ��� Test�Ѵ�.
	auto objList = tilePos->getObjects();
	for (int i = 0; i < (int)objList.size(); i++) {
		/*coord ������ ���� ���� (0, 0)�̴�.
		���� �簢���� �浹���� ����
		�÷��̾��� x��ġ�� coord ~ coord + width �̰�,
		�÷��̾��� y��ġ�� coord ~ coord + heigh �̸�
		�浹�̴�.
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
