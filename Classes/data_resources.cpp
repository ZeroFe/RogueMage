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