#include "Global.h"

/*
전역 변수가 필요하다면 여기를 활용하세요
새 변수를 만들려면 global.h 도 수정해 주세요
사용법 ex ) Global::screenSizeY //값을 가져오는 것은 물론 수정도 가능하다
*/

int Global::screenSizeX = 1280;
int Global::screenSizeY = 960;
int Global::currentFloor = 5;
char *Global::mapName = new char[256]; //heap Allocation
int **Global::mapData = new int *[10];
int **Global::mapTemplate = new int *[10];
//cocos2d::Point Global::currentPos = cocos2d::Point(0, 0); //내현재위치
int Global::currentPosX = 0;
int Global::currentPosY = 0;
int Global::prevEnterPos = -1;
bool *Global::key = new bool[4];