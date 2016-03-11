#include "Character.h"

Character::Character(Sprite *pObj) {
	player = pObj;
	fliping = false;
	stz = true; //character ����ȭ
	
	//�ɷ�ġ����
	attack = 100;
	defense = 50;
}

/*
�� ���ݷ� ����
��� : Player Class���� �Լ� �������� ��
ex) total_attack = attack + magic_attack; ���� ����
*/
void Character::setTotalAttack()
{
	total_attack = attack;
}

/*
�� ���� ����
��� : Player Class���� �Լ� �������� ��
ex) total_defense = defense + magic_defense; ���� ����
*/
void Character::setTotalDefense()
{
	total_defense = defense;
}

Sprite* Character::get() {
	return player;
}

void Character::setflipingFalse(void) {
	fliping = false;
}

void Character::eval() {
	if (!fliping) {
		if (!stz)
			ActIdle();
	}
}

//�÷��̾��� ���� ��ȯ �ڼ��� ����
void Character::ActFlip(int direction) {
	fliping = true;
	stz = false;
	player->stopAllActions();
	float rotateto = -1.0f;
	if (direction == RIGHT)
		rotateto = -rotateto;
	auto myAction = ScaleTo::create(0.2f, rotateto, 1.0f, 1.0f); //rotation
	auto mySkew = SkewTo::create(0.3f, 15.0f, 0.0f);//flip
	auto Actions = Spawn::create(myAction, mySkew, NULL);
	auto Sequence = Sequence::create(Actions, CallFunc::create(CC_CALLBACK_0(Character::setflipingFalse, this)), NULL);
	player->runAction(Sequence);
}

//�÷��̾ �̵� ���� �ڼ��� ���� (������)
void Character::ActWalk(void) { }

//�÷��̾ ������ �� �ִ� �ڼ��� ����
void Character::ActIdle(void) {
	stz = true;
	player->stopAllActions();
	auto skew1 = SkewTo::create(0.3f, 5.0f, 0.0f);
	auto skew2 = SkewTo::create(0.3f, -5.0f, 0.0f);
	auto regression = SkewTo::create(0.3f, 0.0f, 0.0f);
	auto skew1EaseOut = EaseOut::create(skew1, 2.0f);
	auto skew2EaseOut = EaseOut::create(skew2, 2.0f);
	auto regressionEaseOut = EaseOut::create(regression, 2.0f);
	auto action = Sequence::create(skew1EaseOut, regressionEaseOut, DelayTime::create(0.1f), skew2EaseOut, regressionEaseOut, DelayTime::create(0.1f), NULL);
	auto rep = RepeatForever::create(action);
	player->runAction(rep);
}