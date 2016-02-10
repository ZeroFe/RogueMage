#ifndef UI_PopupWindowBase_h
#define UI_PopupWindowBase_h

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

typedef std::function<void(Ref*)> HK_PopupCallback; //콜백에서 인자를 하나만 받을때
typedef std::function<void(Ref*, int)> HK_PopupCallback2;//콜백에서 인자를 두개 받을때

class UI_PopupWindowBase : public cocos2d::Layer
{
public:
	UI_PopupWindowBase(void);
	virtual ~UI_PopupWindowBase(void);

	CREATE_FUNC(UI_PopupWindowBase);    //기본 create()함수 정의

	virtual bool init()final;   //초기화 함수는 다시 오버라이드 되지않고  초기화자를 실행하고자한다만 onInit() 함수를 오버라이드하자
	virtual bool onInit();

	void setCallBackFunc(const HK_PopupCallback& callback); //콜백 함수등록 함수
	void setCallBackFunc2(const HK_PopupCallback2& callback);//콜백 함수등록 함수 (인자를 두개 받을수있는)

	virtual void    showPopup(cocos2d::Layer  *pParrentLayer);    //팝업창을 띄운다
	virtual void    closePopup();

	int    getResult()const { return m_nResult; }  //팝업 클릭동작에대한 리절트리턴
protected:

	virtual void    onCallBackFunc()final;   //콜백 함수 실행
protected:
	HK_PopupCallback m_callback; //콜백
	HK_PopupCallback2 m_callback2; //콜백


	int m_nResult;      //버튼이나 어떤한 동작에 대한 정의할 변수이다 (예: 0= 취소버튼 클릭시, 1= 확인 버튼 클릭시.....)

	cocos2d::Layer *m_ParrentLayer;    //부모 Layer => 팝업은 항상 Layer를 부모를 가져야한다. 만약 부모가 Layer가 아닌경우 그냥 Null을 설정할것

};
#endif
