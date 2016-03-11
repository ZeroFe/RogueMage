#include "cocos2d.h"

USING_NS_CC;

class Item {
private:
	// ������ �� ��ġ �� �濡���� ��ġ
	Point room_pos;
	Point pos;

	// ������ ����
	int type;

	// ���� ��Ÿ�� �ð�
	int cooldown;

	// (�ַ�) ��� ����
	// �������� �ɷ�ġ(��,��,����,�̼�)
	int atk;
	int def;
	int speed_atk;
	int speed_move;

	// ���� ����
	// ������ ���� ���뷮(���/��Ʈ) �� ȿ�� ���� �ð�
	// HP, MP ����
	int fast_hp;
	int fast_mp;
	int slow_hp;
	int slow_mp;
	int turn_hp;
	int turn_mp;

	// ���ݷ�, ���� ����
	int potion_attack;
	int potion_defense;
	int turn_attack;
	int turn_defense;

	// ������ ������ �ִ� ����������
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