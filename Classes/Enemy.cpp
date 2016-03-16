/*
Deprecated
폐기했습니다.

*/

/*
#include "XML/pugixml.hpp"
#include "enemy.h"
#include "cocostudio/CocoStudio.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace pugi;



Enemy::Enemy(void) {
	xml_document xmlDoc;
	xml_parse_result result = xmlDoc.load_file("../Resources/Data/Enemy.xml");
	Data *data = new Data;
	assert(result);
	xml_node nodeChars = xmlDoc.child("Enemies");
	xml_node subject;
	xml_attribute num;
	for (xml_node nodeChar = nodeChars.child("Enemy"); nodeChar; nodeChar = nodeChar.next_sibling("Enemy")) {
		data->num = nodeChar.child("Num").text().as_int();
		data->name = nodeChar.child("Name").text().get();
		subject = nodeChar.child("STAT");
		
		num = subject.first_attribute();
		data->hp = num.as_int();
		num = num.next_attribute();
		data->mp = num.as_int();
		num = num.next_attribute();
		data->mpgen = num.as_int();

		subject = subject.next_sibling();
		num = subject.first_attribute();
		data->atk = num.as_int();
		num = num.next_attribute();
		data->def = num.as_int();
		num = num.next_attribute();
		data->speed_move = num.as_int();
		num = num.next_attribute();
		data->speed_atk = num.as_int();

		log("Name : %s", data->name);
		log("----------------------");
	}
	log("Enemy Ready");
}

void Enemy::addEnemy(EnemyObject& enemyObj) {
	enemy.push_back(enemyObj);
}

void Enemy::removeEnemy(EnemyObject& who) {
	enemy.remove(who);
}

Enemy::~Enemy(void) {

}
*/