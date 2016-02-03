#include "Global.h"

/*
전역 변수가 필요하다면 여기를 활용하세요
새 변수를 만들려면 global.h 도 수정해 주세요
사용법 ex ) Global::screenSizeY //값을 가져오는 것은 물론 수정도 가능하다
*/

int Global::screenSizeX = 1280;
int Global::screenSizeY = 960;
char *Global::mapName = new char[256]; //heap Allocation