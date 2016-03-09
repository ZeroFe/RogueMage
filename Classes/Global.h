#pragma once
#include "cocos2d.h"
/*
���� ������ �ʿ��ϴٸ� ���⸦ Ȱ���ϼ���
�� ������ ������� global.cpp �� ������ �ּ���
���� ex ) Global::screenSizeY //���� �������� ���� ���� ������ �����ϴ�
*/
namespace Global {
	extern int screenSizeX; //��ũ�� ������ x��
	extern int screenSizeY; //��ũ�� ������ y��
	extern int currentFloor; //���� �� (�̱���)
	extern char* mapName; //map��� �̸� (�� ���� �� �̰��� �ٲ���� �Ѵ�)
	extern int **mapData; //���� ���� �� ������ ��� �ִ�.
	extern int **mapTemplate; //�� ������ ���� �� ���ø� (mapData�� �������ڸ��� �����Ǿ�߸� �Ѵ�)
	//extern cocos2d::Point currentPos; //�ʿ��� ���� ���� ��ġ (�̴ϸ� ������ �����Ͽ�)
	extern int currentPosX;
	extern int currentPosY;
	extern int prevEnterPos; //������ ��� ���⿡�� �� ���� �����Ͽ����� ��Ÿ���� ��, 0,1,2,3 �� ���� ������ �Ʒ�, ��, ����, �����ʼ���
	extern bool *key; //Ű���� ����
	extern int fps;
}