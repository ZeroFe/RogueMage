#include "Item.h"

USING_NS_CC;

Item::Item()
{
	room_pos = (0, 0);
	pos = (0, 0);

	atk = 0;
	def = 0;
	speed_atk = 0;
	speed_move = 0;

	fast_hp = 0;
	fast_mp = 0;
	slow_hp = 0;
	slow_mp = 0;
	turn_hp = 0;
	turn_mp = 0;

	damage_magic = 0;
}

Item::~Item()
{

}