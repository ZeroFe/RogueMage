#include "Item.h"
#include "XML/pugixml.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace pugi;

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

void Item::setDataSet()
{
	xml_document xmlDoc;

	xml_parse_result result = xmlDoc.load_file("../Resources/Data/Item.xml");

	Data *data = new Data;

	if (!result)
	{
		//log("Error description : %s", result.description());
		//log("Error offset : %d", result.offset);
	}

	xml_node nodeChars = xmlDoc.child("Items");
	xml_node subject;
	xml_attribute num;

	int kind;

	for (xml_node nodeChar = nodeChars.child("Item"); nodeChar; nodeChar = nodeChar.next_sibling("Item"))
	{
		data->name = nodeChar.child("Name").text().get();

		kind = nodeChar.child("Kind").text().as_int();

		if (kind == 0)
		{

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

			//std::cout << "Name : " << data.name << std::endl;
			//std::cout << "HP : " << data.hp << std::endl;
			//std::cout << "MP : " << data.mp << std::endl;
			//std::cout << "MPgen : " << data.mpgen << std::endl;
			//std::cout << "ATK : " << data.atk << std::endl;
			//std::cout << "DEF : " << data.def << std::endl;
			//std::cout << "SPD : " << data.speed_move << std::endl;
			//std::cout << "ASPD : " << data.speed_atk << std::endl;
			//std::cout << std::endl;
		}
		else if (kind == 1)
		{
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

			subject = nodeChar.child("Magic");
			num = subject.first_attribute();
			data->damage_magic = num.as_int();
			num = num.next_attribute();
			data->mp_magic = num.as_int();


			//std::cout << "Name : " << data.name << std::endl;
			//std::cout << "HP : " << data.hp << std::endl;
			//std::cout << "MP : " << data.mp << std::endl;
			//std::cout << "MPgen : " << data.mpgen << std::endl;
			//std::cout << "ATK : " << data.atk << std::endl;
			//std::cout << "DEF : " << data.def << std::endl;
			//std::cout << "SPD : " << data.speed_move << std::endl;
			//std::cout << "ASPD : " << data.speed_atk << std::endl;
			//std::cout << std::endl;
		}
		else if (kind == 2)
		{
			subject = nodeChar.child("HP");
			num = subject.first_attribute();
			data->fast_hp = num.as_int();
			num = num.next_attribute();
			data->slow_hp = num.as_int();
			num = num.next_attribute();
			data->turn_hp = num.as_int();

			subject = nodeChar.child("MP");
			num = subject.first_attribute();
			data->fast_mp = num.as_int();
			num = num.next_attribute();
			data->slow_mp = num.as_int();
			num = num.next_attribute();
			data->turn_mp = num.as_int();

			subject = nodeChar.child("ATK");
			num = subject.first_attribute();
			data->potion_attack = num.as_int();
			num = num.next_attribute();
			data->turn_attack = num.as_int();

			subject = nodeChar.child("DEF");
			num = subject.first_attribute();
			data->potion_defense = num.as_int();
			num = num.next_attribute();
			data->turn_defense = num.as_int();
		}
		else
		{
			//std::cout << "error" << std::endl;
		}

		vecItem.push_back(data);

	}
}

Item::~Item()
{

}