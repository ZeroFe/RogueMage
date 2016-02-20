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

	//���� ��ġ�� ���� �߽ɺο� �����ؾ��Ѵ� -> ���� �߽� x
	start.x = rand() % (MAP_SIZE / 2) + MAP_SIZE / 4;
	start.y = rand() % (MAP_SIZE / 2) + MAP_SIZE / 4;

	//ù���� ������ ����
	point[0] = start;
	bossRoom[0] = start;//���ǻ� ���� ���� ���������� ���
	cnt++;//���� ������ �÷��ش�

	table[start.x][start.y] = START;//���̺� ������ġ�� ä��
	startx = start.x;
	starty = start.y;
}

bool createMap::Map::makeRoom(Spot spot, int mode)
{
	
	Spot tmp = spot;
	Spot temp;
	mode %= 4;//4���� �� �ϳ��� ����

	//������ ������ġ�� ã���ش�
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

	//���� ������ ���� ������� üũ
	if (roomCheck(tmp))
		return false;

	//���� ������ ���� ���̺� ������ üũ
	if (inTableCheck(tmp))
	{
		//���� �� ���� �ٸ� ��� �̾����� ���� üũ
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

	//���� �������� �ߴ� ���� �������̿����� ���ο� ���� ���������� ��ü
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

//���� ����
void createMap::Map::make(int floor)
{
	//int rCnt = 0;

	start();//���� ��ġ�� ����ش�

	//���� �����Ѵ�(���ϴ� �� ��ŭ -1��
	while (cnt != ROOM - 1)
	{
		//�������� �������� ����� ���� ���� �������� rCnt�� �̿��� �����뿡 ����Ǵ� ���� ���� �����Ѵ�
		if (rCnt < R_ROOM&&bossCnt != 0)
		{
			if (makeRoom(bossRoom[rand() % (bossCnt + 1)], rand() % 4))
				cnt++;
		}
		else//R_ROOM��ŭ ���� ������ ���� �ƹ� �濷�� ���ο� ���� ���� �� �ְ��Ѵ�
		{
			if (makeRoom(point[rand() % cnt], rand() % 4))
				cnt++;
		}
	}


	//�������� �����
	while (!makeRoom(rSpot[rand() % rCnt], rand() % 4));

	table[point[cnt].x][point[cnt].y] = SHOP;


	//��й��� ���� ���̺� ������ ����
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