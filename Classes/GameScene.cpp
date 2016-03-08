#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "Global.h"
#include "data_recources.h"
USING_NS_CC;
using namespace cocostudio::timeline;
Scene* GameScene::createScene(){auto a=Scene::create();a->addChild(GameScene::create());return a;}
bool GameScene::init() {
	if (!Layer::init()){return false;}

	/*rootNode = CSLoader::createNode(Global::mapName); //�ӽ÷� ���Ƴ���
	srand(time(NULL));*/
	rootNode = CSLoader::createNode(resData::mapTemplate[0]); //Debug : ù��° �ʸ� �ҷ���
	map = (TMXTiledMap *)rootNode->getChildByName("gameMap"); //cocos studio ���� ������ TileMap �̸�
	addChild(rootNode);

	//��Ÿ�����͸� �����´�.
	objects = map->getObjectGroup("SpawnList");
	Wall = map->getObjectGroup("Wall");
	Damage = map->getObjectGroup("Damage");


	//1. HUD ����
	HUD = new UI_HUD();
	HUD->setPosition(Point(0, 960));
	this->addChild(HUD->getObject());//���� : this��

	//2. Player ���� && Player Object ����
	playerSprite = Sprite::create(resData::recources[resData::PLAYER_SPRITE]);
	playerSprite->setAnchorPoint(Point(0.5, 0));//0.5 0
	rootNode->addChild(playerSprite);
	const char* startPos[] = {
		"start", "SpawnDown", "SpawnUp", "SpawnLeft", "SpawnRight"
	};
	int x = objects->getObject(startPos[Global::prevEnterPos + 1])["x"].asInt();
	int y = objects->getObject(startPos[Global::prevEnterPos + 1])["y"].asInt();
	playerSprite->setPosition(Point(x, y));
	playerObj = new Player(playerSprite);
	playerObj->ActIdle();

	//3. minimap �׸���
	auto minimap_room = SpriteBatchNode::create(resData::recources[resData::MINIMAP_BRICK_NORMAL], 50);
	Point hudPos = Point(900, 700);
	minimap_room->setPosition(hudPos);
	this->addChild(minimap_room, 0, 1);
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

	this->schedule(schedule_selector(GameScene::enterFrame)); //�������� �Ǵ� (�� 1/60�ʿ� 1�� �����)

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
	//����� ���� Gid �� 11�̴�.
	//auto layer = map->layerNamed("Background");
	//Point tilePos = tileCoordForPosition(playerSprite->getPosition());
	//log("%u", layer->getTileGIDAt(Vec2(tilePos.x, tilePos.y)));

	//�÷��̾� ��ü�� ����ȭ�Ѵ�.
	playerObj->stabilization();

	//���� ���� ������
	attackSpotListBatchNode->setPosition(playerSprite->getPosition()); //center of player
	attackSpotListBatchNode->setPositionY(playerSprite->getPositionY() + playerSprite->getContentSize().height / 2.0f);


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


	//���� ����
	//������ ���� Ÿ���� ��� ����
	double playerX = attackSpotListBatchNode->getPositionX();
	double playerY = Global::screenSizeY - attackSpotListBatchNode->getPositionY();
	double diffX = mouseX - playerX;
	double diffY = mouseY - playerY;
	double angle = atan2(diffY, diffX) * 180 / M_PI;
	attackSpotListBatchNode->setRotation(angle);
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
	delete playerObj; //new�� ������ Object�� �������� �޸𸮸� �����ؾ� �Ѵ�.
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
	double playerX = attackSpotListBatchNode->getPositionX();
	double playerY = Global::screenSizeY - attackSpotListBatchNode->getPositionY();
	double diffX = mouseX - playerX;
	double diffY = mouseY - playerY;
	double angle = atan2(diffY, diffX) * 180 / M_PI;
	playerObj->basicAttack((Scene*)this, Point(playerSprite->getPositionX(), playerSprite->getPositionY()), angle);
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_W:
		//if (!Global::key[S])
			Global::key[W] = true;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		//if (!Global::key[D])
			Global::key[A] = true;
			playerObj->ActFlip(Player::RIGHT);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		//if (!Global::key[W])
			Global::key[S] = true;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		//if (!Global::key[A])
			Global::key[D] = true;
			playerObj->ActFlip(Player::LEFT);
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
		if (moveable(0)) {
			moveScene(0);
		}
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (moveable(1)) {
			moveScene(1);
		}
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (moveable(2)) {
			moveScene(2);
		}
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (moveable(3)) {
			moveScene(3);
		}
		break;
	}
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
	strcpy_s(Global::mapName, 256, resData::mapTemplate[Global::mapTemplate[ccx][ccy]]);

	//���� ����� �ٿ����´�.
	auto nextMap = TMXTiledMap::create("Scene/GameScene/TileMap/01.tmx"); //�ӽ� ����� (1)
	MoveBy *transAction;
	log("00");
	switch (direction) {
	case 0:
		log("Herre!");
		nextMap->setPositionY(-704); //���� �ö� ����;
		transAction = MoveBy::create(0.5, Point(0, 704));
		break;
	case 1:
		nextMap->setPositionY(704); //�Ʒ��� �ö� ����
		transAction = MoveBy::create(0.5, Point(0, -704));
		break;
	case 2:
		nextMap->setPositionX(-1280); //��
		transAction = MoveBy::create(0.5, Point(1280, 0));
		break;
	case 3:
		nextMap->setPositionX(1280); //��
		transAction = MoveBy::create(0.5, Point(-1280, 0));
		break;
	}
	rootNode->addChild(nextMap, 10, 11);
	//�ű�� �ִϸ��̼� �Ѵ�. (rootNode �� �̵�)
//	rootNode->runAction(transAction);
	auto Seq = Sequence::create(transAction, CallFunc::create(CC_CALLBACK_0(GameScene::trans, this)), NULL);
	rootNode->runAction(Seq);
	//����̵�
	//auto Sequence = Sequence::create(Actions, CallFunc::create(CC_CALLBACK_0(Player::falseFlip, this)), NULL);
	//auto nextScene = GameScene::createScene();
	//auto trans = TransitionTurnOffTiles::create(0.5, nextScene);
	//srand(time(NULL));
	playerSprite->setOpacity(0);
	//�����췯�� �����Ѵ� (���� ���� ����)
	this->unschedule(schedule_selector(GameScene::enterFrame));
	//Director::getInstance()->replaceScene(transition(direction, 0.5, nextScene));
}

void GameScene::trans() {
	auto nextScene = GameScene::createScene();
	Director::getInstance()->replaceScene(nextScene);
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
