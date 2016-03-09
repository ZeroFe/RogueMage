#pragma once
#include "cocos2d.h"
/*
전역 변수가 필요하다면 여기를 활용하세요
새 변수를 만들려면 global.cpp 도 수정해 주세요
사용법 ex ) Global::screenSizeY //값을 가져오는 것은 물론 수정도 가능하다
*/
namespace Global {
	extern int screenSizeX; //스크린 사이즈 x픽
	extern int screenSizeY; //스크린 사이즈 y픽
	extern int currentFloor; //현재 층 (미구현)
	extern char* mapName; //map경로 이름 (맵 수정 전 이것을 바꿔줘야 한다)
	extern int **mapData; //현재 층의 맵 구조를 담고 있다.
	extern int **mapTemplate; //맵 구조에 따른 맵 탬플릿 (mapData를 생성하자마자 생성되어야만 한다)
	//extern cocos2d::Point currentPos; //맵에서 현재 나의 위치 (미니맵 생성기 기준하여)
	extern int currentPosX;
	extern int currentPosY;
	extern int prevEnterPos; //이전에 어느 방향에서 이 맵을 진입하였는지 나타내는 수, 0,1,2,3 의 값을 가지고 아래, 위, 왼쪽, 오른쪽순서
	extern bool *key; //키눌림 관련
	extern int fps;
}