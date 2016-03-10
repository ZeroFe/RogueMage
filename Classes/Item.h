#include "cocos2d.h"

USING_NS_CC;

class Item {
private:
	// 방 위치 및 방에서의 위치
	Point room_pos;
	Point pos;

	// 아이템 종류
	int type;

	// 아이템의 능력치(공,방,공속,이속)
	int atk;
	int def;
	int speed_atk;
	int speed_move;

	// 아이템의 회복량(즉발/도트)
	int fast_hp;
	int fast_mp;
	int slow_hp;
	int slow_mp;
	int turn_hp;
	int turn_mp;

	// 아이템 시전시 주는 마법데미지
	int damage_magic;

public:
	Item();
	~Item();

	void setPosition(Point r, Point p);
	
	void setType(int Type);

	void setAttack(int attack);
	void setDefence(int defence);
	void setSpeedAttack(int speed);
	void setSpeedMove(int speed);
};