#ifndef __RECOURCES__
#define __RECOURCES__
/**
파일 경로 등 변하기 쉬운 변수는 여기에 선언한다
추가방법 : 일단 enum 부분의 끝에 내가 원하는 닉네임을 하나 추가한다.
그리고 data_resources.cpp 가서 경로 이름을 추가하면 된다.
사용법 : 이 헤더를 인클루드 하고 resData::resources[resData::enum으로 정의한 닉네임]
ex) resData::recources[resData::SPLASH_IMAGE]
*/
namespace resData {
	enum { SPLASH_IMAGE, MAP0, PARTICLE_CLICK, PARTICLE_BRUSH, PLAYER_SPRITE, MINIMAP_BRICK_NORMAL, ENEMY_ONE, PLAYER_SPRITE_WALK, PARTICLE_ROCKET };
	extern const char * recources[];

	//게임 맵 탬플릿 경로
	extern int number_of_template;
	extern const char * mapTemplate[];

	// HUD 리소스 파일 경로
	extern const char * hudResource[];
	extern const char * hudMinimap[];
	
	// CharacterScene 리소스 파일 경로
	extern const char * CharIcon[];
}
#endif