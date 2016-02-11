#include "mapGenerator.h"
#include "cocos2d.h"
USING_NS_CC;


createMap::Map::Map()
{
	rCnt = 0;
	cnt = 0;
	bossCnt = 0;
	table = new char*[MAP_SIZE];

	for (int i = 0; i < MAP_SIZE; i++)
		table[i] = new char[MAP_SIZE];

	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			table[i][j] = '\0';
		}
	}

	point = new Spot[ROOM];
	bossRoom = new Spot[3 + 1];
	rSpot = new Spot[ROOM];
}

bool createMap::Map::inTableCheck(Spot spot)
{
	if ((spot.x >= 0 && spot.x < MAP_SIZE) && (spot.y >= 0 && spot.y < MAP_SIZE))
		return true;
	else
		return false;
}

bool createMap::Map::roomCheck(Spot spot)
{
	if (inTableCheck(spot))
		return table[spot.x][spot.y] != '\0';
	else
		return false;
}

void createMap::Map::start()
{
	srand(time(NULL));

	Spot start;

	start.x = rand() % (MAP_SIZE / 2) + MAP_SIZE / 4;
	start.y = rand() % (MAP_SIZE / 2) + MAP_SIZE / 4;

	point[0] = start;
	bossRoom[0] = start;
	cnt++;

	table[start.x][start.y] = START;
	startx = start.x;
	starty = start.y;

	int check;

	check = rand() % 4;


}

bool createMap::Map::makeRoom(Spot spot, int mode)
{
	Spot tmp = spot;
	Spot temp;
	mode %= 4;


	if (mode == 0)
	{
		tmp.x--;
	}
	else if (mode == 1)
	{
		tmp.x++;
	}
	else if (mode == 2)
	{
		tmp.y--;
	}
	else if (mode == 3)
	{
		tmp.y++;
	}

	if (roomCheck(tmp))
		return false;

	if (inTableCheck(tmp))
	{

		if (mode != 0)
		{
			temp.x = tmp.x + 1;
			temp.y = tmp.y;

			if (roomCheck(temp))
			{
				return false;
			}
		}

		if (mode != 1)
		{
			temp.x = tmp.x - 1;
			temp.y = tmp.y;

			if (roomCheck(temp))
			{
				return false;
			}
		}

		if (mode != 2)
		{
			temp.x = tmp.x;
			temp.y = tmp.y + 1;

			if (roomCheck(temp))
			{
				return false;
			}
		}

		if (mode != 3)
		{
			temp.x = tmp.x;
			temp.y = tmp.y - 1;

			if (roomCheck(temp))
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}


	if (table[spot.x][spot.y] == BOSS)
	{
		for (int i = 1; i <= bossCnt; i++)
		{
			if (bossRoom[i] == spot)
			{
				bossRoom[i] = tmp;
				break;
			}
		}
		rSpot[rCnt++] = spot;
		table[spot.x][spot.y] = B_ROOM;
		table[tmp.x][tmp.y] = BOSS;
	}
	else
	{
		if (bossCnt != 3)
		{
			bossCnt++;
			bossRoom[bossCnt] = tmp;
			table[tmp.x][tmp.y] = BOSS;
		}
		else
		{
			table[tmp.x][tmp.y] = N_ROOM;
		}
	}

	point[cnt] = tmp;

	return true;
}

void createMap::Map::make(int floor)
{
	//int rCnt = 0;

	start();

	while (cnt != ROOM - 1)
	{
		if (rCnt < R_ROOM&&bossCnt != 0)
		{
			if (makeRoom(bossRoom[rand() % (bossCnt + 1)], rand() % 4))
				cnt++;
		}
		else
		{
			if (makeRoom(point[rand() % cnt], rand() % 4))
				cnt++;
		}
		//system("cls");
		//std::cout << cnt << std::endl;
		//show();
		//showSpot();
	}


	//make shop
	while (!makeRoom(rSpot[rand() % rCnt], rand() % 4));

	table[point[cnt].x][point[cnt].y] = SHOP;


	//make secret
	if (floor % 2 == 0)
	{
		while (table[point[cnt].x][point[cnt].y] != N_ROOM)
		{
			cnt--;
		}
		table[point[cnt].x][point[cnt].y] = SECRET;
	}

}


void createMap::Map::showSpot()
{
	for (int i = 0; i < cnt; i++)
	{
		std::cout << "x : " << point[i].x << " y : " << point[i].y << std::endl;
	}
}

void createMap::Map::show()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			printf("%2c", table[i][j]);
		}

		printf("\n");
	}
}

void createMap::Map::showlog()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			log("%2c", table[i][j]);
		}

		//printf("\n");
	}
}

void createMap::Map::copyMap(int **mapData) {
	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++)
			mapData[i][j] = table[i][j];
}


//int main()
//{
//	createMap::Map a;
//
//	a.make(2);
//
//	//system("cls");
//	a.show();
//}