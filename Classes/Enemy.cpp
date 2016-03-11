#include "enemy.h"

Enemy::Enemy() {

}

void Enemy::add(EnemyObject& enemyObj) {
	enemy.push_back(enemyObj);
}

void Enemy::remove(EnemyObject& who) {
		enemy.remove(who);
}

Enemy::~Enemy()
{
}
