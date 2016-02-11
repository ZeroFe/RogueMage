#ifndef UIPopup_h
#define UIPopup_h

#include "ui/cocosgui.h"
#include "UIPopupBase.h"

using namespace cocos2d::ui;
class UIPopup : public UIPopupBase
{
public:

	static UIPopup* create(Node* popupLayer); //기본생성시 백그라운드 이미지와  백배경에 반투명 이미지를 설정한다.
	virtual bool onInit();

	virtual void setButton(const std::string &name, const int tag);
	virtual void addButton(const char* normalTexture, const char* selectedTexture, const char* disabledTexture, Widget::TextureResType texType, const Point &pos, const std::string& text, const int nTag); //팝업창에 버튼을 추가한다.

	virtual void onBtnClickCallbackFnc(Ref *pSender, ui::Widget::TouchEventType   touchType);//추가되는 버튼들에 대한 콜백함수 설정


	virtual bool onTouchBegan(Touch* touch, Event* event) { return true; };
	virtual void onTouchMoved(Touch* touch, Event* event) {};
	virtual void onTouchEnded(Touch* touch, Event* event) {};
	virtual void onTouchCancelled(Touch* touch, Event* event) {};
	CREATE_FUNC(UIPopup);    //기본 create()함수 정의
public:
	virtual void setFontSize_Title(int size);   //타이틀 폰트 사이즈를 설정한다.
	virtual void setColor_Title(const Color3B& color);  //타이틀 폰트 색상 설정
	virtual void setPosition_Title(const Point& position);
	virtual void setFontName_Title(const std::string& name);

	virtual void setFontSize_Msg(int size);     //메시지의 폰트 사이즈를 설정한다.
	virtual void setColor_Msg(const Color3B& color);    //메시지 폰트 색상 설정
	virtual void setPosition_Msg(const Point& position);
	virtual void setFontName_Msg(const std::string& name);

	virtual void setTitleString(const std::string& text);
	virtual void setMessageString(const std::string& text);

	virtual void setBackgroundImagePosition(const Point& position);//백그라운드 이미지에 대한 위치 조정

	virtual void setBackgroundBorard(Sprite  *sprBg);//팝업 아래에 투명이나 머 이런거? 하여간 맨 밑바닥
protected:
	virtual void setBackgroundImage(Sprite  *sprBg);//실제 보여질 박스
	virtual void setPopupLayer(Node* popupLayer);

	virtual void setTextInit(); //출력할 문자 UI초기화
protected:

	Node	*pLayer = NULL;
	Sprite  *m_sprBg;   //백그라운드 이미지
	Text    *m_txtTitle;    //타이틀
	Text    *m_txt;         //내용

	long    m_nZorderCnt;
};

#endif
