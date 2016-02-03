#pragma once
/*
전역 변수가 필요하다면 여기를 활용하세요
새 변수를 만들려면 global.cpp 도 수정해 주세요
사용법 ex ) Global::screenSizeY //값을 가져오는 것은 물론 수정도 가능하다
*/
namespace Global {
	extern int screenSizeX;
	extern int screenSizeY;
	extern char* mapName;
}