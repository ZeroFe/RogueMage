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

	//시작 위치는 맵의 중심부에 존재해야한다 -> 완전 중심 x
	start.x = rand() % (MAP_SIZE / 2) + MAP_SIZE / 4;
	start.y = rand() % (MAP_SIZE / 2) + MAP_SIZE / 4;

	//첫방의 정보를 저장
	point[0] = start;
	bossRoom[0] = start;//편의상 시작 방은 보스방으로 취급
	cnt++;//방의 갯수를 늘려준다

	table[start.x][start.y] = START;//테이블에 시작위치를 채움
	startx = start.x;
	starty = start.y;
}

bool createMap::Map::makeRoom(Spot spot, int mode)
{
	
	Spot tmp = spot;
	Spot temp;
	mode %= 4;//4방향 중 하나를 선택

	//선택한 방향위치를 찾아준다
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

	//새로 생성될 방이 비었는지 체크
	if (roomCheck(tmp))
		return false;

	//새로 생성된 방이 테이블 위인지 체크
	if (inTableCheck(tmp))
	{
		//생성 된 방이 다른 방과 이어지는 지를 체크
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

	//만약 이을려고 했던 방이 보스방이였으면 새로운 방을 보스방으로 대체
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

//맵을 생성
void createMap::Map::make(int floor)
{
	//int rCnt = 0;

	start();//시작 위치를 잡아준다

	//방이 생성한다(원하는 것 만큼 -1개
	while (cnt != ROOM - 1)
	{
		//보스룸이 시작점과 가까워 지는 것을 막기위해 rCnt를 이용해 보스룸에 연결되는 방을 먼저 생성한다
		if (rCnt < R_ROOM&&bossCnt != 0)
		{
			if (makeRoom(bossRoom[rand() % (bossCnt + 1)], rand() % 4))
				cnt++;
		}
		else//R_ROOM만큼 방을 생성한 이후 아무 방옆에 새로운 방을 붙일 수 있게한다
		{
			if (makeRoom(point[rand() % cnt], rand() % 4))
				cnt++;
		}
	}


	//상점방을 만든다
	while (!makeRoom(rSpot[rand() % rCnt], rand() % 4));

	table[point[cnt].x][point[cnt].y] = SHOP;


	//비밀방을 만들어서 테이블 정보를 수정
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