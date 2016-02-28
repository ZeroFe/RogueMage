#include "data_recources.h"
/**
파일 경로 등 변하기 쉬운 변수는 여기에 선언한다
사용법 : data_recources.h 인클루드 하고 resData::recources[resData::enum으로 정의한 이름]
ex) resData::recources[resData::SPLASH_IMAGE]
*/
const char * resData::recources[] = {
	"misc/splash-800x600.png",
	"maps/orthogonal-test1.tmx",
	"particle/click.png",
	"particle/largeBrush.png"
};
int resData::number_of_template = 15;
const char * resData::mapTemplate[] = {
	"Scene/GameScene/mapTemp01.csb",
	"Scene/GameScene/mapTemp02.csb",
	"Scene/GameScene/mapTemp03.csb",
	"Scene/GameScene/mapTemp04.csb",
	"Scene/GameScene/mapTemp05.csb",
	"Scene/GameScene/mapTemp06.csb",
	"Scene/GameScene/mapTemp07.csb",
	"Scene/GameScene/mapTemp08.csb",
	"Scene/GameScene/mapTemp09.csb",
	"Scene/GameScene/mapTemp10.csb",
	"Scene/GameScene/mapTemp11.csb",
	"Scene/GameScene/mapTemp12.csb",
	"Scene/GameScene/mapTemp13.csb",
	"Scene/GameScene/mapTemp14.csb",
	"Scene/GameScene/mapTemp15.csb"
};
const char * resData::hudResource[] = {
	"char/hud/background.png",
	"char/hud/panel.png",
	"char/hud/hpBar.png",
	"char/hud/mpBar.png",
	"char/hud/stageBar.png"
};
const char * resData::hudMinimap[] = {
	"char/hud/minimap/Normal.png",
	"char/hud/minimap/Dark.png",
	"char/hud/minimap/Boss1.png",
	"char/hud/minimap/Boss2.png",
	"char/hud/minimap/Boss3.png",
	"char/hud/minimap/Secret.png",
	"char/hud/minimap/Shop.png"
};