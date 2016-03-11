#include "cocos2d.h"

USING_NS_CC;

class Item {
private:
	// 생성시 방 위치 및 방에서의 위치
	Point room_pos;
	Point pos;

	// 아이템 종류
	int type;

	// 사용시 쿨타임 시간
	int cooldown;

	// (주로) 장비 관련
	// 아이템의 능력치(공,방,공속,이속)
	int atk;
	int def;
	int speed_atk;
	int speed_move;

	// 포션 관련
	// 아이템 사용시 적용량(즉발/도트) 및 효과 지속 시간
	// HP, MP 관련
	int fast_hp;
	int fast_mp;
	int slow_hp;
	int slow_mp;
	int turn_hp;
	int turn_mp;

	// 공격력, 방어력 관련
	int potion_attack;
	int potion_defense;
	int turn_attack;
	int turn_defense;

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