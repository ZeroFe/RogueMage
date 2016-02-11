#include "Global.h"
#include "data_recources.h"
#include "AppDelegate.h"
#include "Scene/StartScene.h"
#include "HelloWorldScene.h"
#include "RMAlgorithm/mapGenerator.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(Global::screenSizeX, Global::screenSizeY);

AppDelegate::AppDelegate() {
	log("App loading ...");
	//0. 필요한 메모리 할당

	for (int i = 0; i < 10; i++) {
		Global::mapData[i] = new int[10];
		Global::mapTemplate[i] = new int[10];
	}

	//1. 5층용 맵 생성 (초기)

	createMap::Map s = createMap::Map::Map();
	s.make(1);
	s.copyMap(Global::mapData);
	
	//2. 템플릿 주입
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (Global::mapData[i][j] != '\0')
				Global::mapTemplate[i][j] = rand() % resData::number_of_template;
		}
	}

	//3. 시작점 글로벌 변수 지정하기
	//Global::currentPos = Point(s.startx, s.starty);
	Global::currentPosX = s.startx;
	Global::currentPosY = s.starty;
	log("current Position : %d %d", s.startx, s.starty);
	//4. 맵 이름 주입
	strcpy_s(Global::mapName, 256, resData::mapTemplate[Global::mapTemplate[s.startx][s.starty]]); //시작 맵
}

AppDelegate::~AppDelegate() {
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("RogueMage", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("RogueMage");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
 
    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = StartScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    // if you use SimpleAudioEngine, it must resume here
    //SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
