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
//cocos2d::Point Global::currentPos = cocos2d::Point(0, 0); //��������ġ
int Global::currentPosX = 0;
int Global::currentPosY = 0;
int Global::prevEnterPos = -1;
bool *Global::key = new bool[4];