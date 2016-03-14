#ifndef __RECOURCES__
#define __RECOURCES__
/**
���� ��� �� ���ϱ� ���� ������ ���⿡ �����Ѵ�
�߰���� : �ϴ� enum �κ��� ���� ���� ���ϴ� �г����� �ϳ� �߰��Ѵ�.
�׸��� data_resources.cpp ���� ��� �̸��� �߰��ϸ� �ȴ�.
���� : �� ����� ��Ŭ��� �ϰ� resData::resources[resData::enum���� ������ �г���]
ex) resData::recources[resData::SPLASH_IMAGE]
*/
namespace resData {
	enum { SPLASH_IMAGE, MAP0, PARTICLE_CLICK, PARTICLE_BRUSH, PLAYER_SPRITE, MINIMAP_BRICK_NORMAL, ENEMY_ONE, PLAYER_SPRITE_WALK, PARTICLE_ROCKET };
	extern const char * recources[];

	//���� �� ���ø� ���
	extern int number_of_template;
	extern const char * mapTemplate[];

	// HUD ���ҽ� ���� ���
	extern const char * hudResource[];
	extern const char * hudMinimap[];
	
	// CharacterScene ���ҽ� ���� ���
	extern const char * CharIcon[];
}
#endif