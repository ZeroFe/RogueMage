#pragma once
#include <iostream>
#include <ctime>
//#include <Windows.h>

#define MAP_SIZE 10

#define ROOM 16

#define R_ROOM ROOM/2
#define BOSS 'B'
#define N_ROOM 'r'
#define B_ROOM 'R'
#define SHOP 'C'
#define SECRET 'T'
#define START 'S'

namespace createMap {
	class Map;
	//좌표
	class Spot
	{
		friend class Map;
	private:
		int x;
		int y;
	public:
		//equal 연산자 재정의
		bool operator ==(const Spot &T) const
		{
			return x == T.x&&y == T.y;
		}
	};

	class Map
	{
	private:


		char **table;//맵의 테이블
		Spot *point;//맵의 방의 집합
		Spot *bossRoom;
		Spot *rSpot;
		int cnt;//방의 개수
		int rCnt;
		void start();//맵의 시작부분 생성
		bool makeRoom(Spot spot, int mode);
		bool inTableCheck(Spot spot);
		bool roomCheck(Spot spot);
		int bossCnt;

	public:
		Map();
		void make(int floor);
		void show();
		void showSpot();
		void showlog();
		void copyMap(int** mapData);
		int startx;
		int starty;
	};

}