#include "Global.h"

/*
���� ������ �ʿ��ϴٸ� ���⸦ Ȱ���ϼ���
�� ������ ������� global.h �� ������ �ּ���
���� ex ) Global::screenSizeY //���� �������� ���� ���� ������ �����ϴ�
*/

int Global::screenSizeX = 1280;
int Global::screenSizeY = 960;
int Global::currentFloor = 5;
char *Global::mapName = new char[256]; //heap Allocation
int **Global::mapData = new int *[10];
int **Global::mapTemplate = new int *[10];
int Global::currentPosX = 0;
int Global::currentPosY = 0;
int Global::prevEnterPos = -1;
bool *Global::key = new bool[4];
int Global::fps = 60;
std::vector<EnemyObject *> Global::enemyList; //�� ����Ʈ�� ���⼭ �����ϱ�� �ߴ�.