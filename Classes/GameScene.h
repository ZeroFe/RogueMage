#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Global.h"
#include "Player.h"
USING_NS_CC;
class GameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	TransitionScene* transition(int direction, float t, Scene* s);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
	virtual void onEnter();
	virtual void onExit();
	virtual void onMouseMove(Event * ev);
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);


	Node *rootNode;
	Sprite *playerSprite;
	Sprite *HUD;
	TMXTiledMap *map;
	Player *playerObj;
	TMXLayer *metainfo;
	TMXObjectGroup *objects;
	Point GameScene::tileCoordForPosition(Point position);
	void GameScene::enterFrame(float dt);

	bool moveable(int direction);
	void moveScene(int direction);

	bool GameScene::colideTestPointAndTile(Point& pos, TMXObjectGroup * Wall);



	//�� ���� ��Ÿ������ �̾ƺ���
	TMXObjectGroup * Wall;
	TMXObjectGroup * Damage;
	SpriteBatchNode * attackSpotListBatchNode;
	Texture2D **aimTexture; //�޸� ���� �ʿ� (new �� ���������Ƿ� Garbage - Collection�� �ڵ����� �� ��)
	Sprite **aimSprite; //�޸� ���� �ʿ�

	enum {W, A, S, D};

	int mouseX, mouseY;
};

#endif // __GameScene_SCENE_H__
