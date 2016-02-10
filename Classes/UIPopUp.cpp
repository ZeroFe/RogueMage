#include "UIPopup.h"

UIPopupWindow *UIPopupWindow::create(Sprite *sprBackgroundBoard, Sprite *sprBackgroundImg)
{
	UIPopupWindow *pRet = new UIPopupWindow();
	if (pRet && pRet->init())
	{
		pRet->setBackgroundBorard(sprBackgroundBoard);
		pRet->setBackgroundImage(sprBackgroundImg);
		pRet->setTextInit(); //출력할 문자 UI초기화

		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool UIPopupWindow::onInit()
{
	m_nZorderCnt = 1;//추가될 자식객체들에 대한 Zorder를 만들기위해
	m_sprBg = NULL;

	return true;
}


void UIPopupWindow::onBtnClickCallbackFnc(Ref *pSender, ui::Widget::TouchEventType touchType)
{
	// 새로추가되는 버튼에 대한 이벤트핸들러 함수랄까...
	if (touchType == ui::Widget::TouchEventType::ENDED)
	{
		//SimpleAudioEngine::getInstance()->playEffect( DF_SOUND_UI_01); //이부분은 버튼클릭시 이펙트 음을 내기위해서

		m_nResult = ((cocos2d::ui::Button*)pSender)->getTag();    //어떤 버튼인지 체크를 위해 버튼에 추가된 Tag를 맴버변수에서 가지고있도록 한다.
		onCallBackFunc();   //실제 Base클래스의 팝업 콜백함수를 호출한다.
	}
}


void UIPopupWindow::setBackgroundBorard(Sprite  *sprBg)//팝업 아래에 투명이나 머 이런거? 하여간 맨 밑바닥
{
	if (!sprBg)return;

	Size size = Director::getInstance()->getWinSize();
	sprBg->setPosition(size.width / 2, size.height / 2);
	addChild(sprBg, 1);
}


void UIPopupWindow::setBackgroundImage(Sprite  *sprBg)
{
	if (m_sprBg)
	{
#if COCOS2D_DEBUG > 0
		char msg[256] = { 0 };
		sprintf(msg, "Already BackgroundImage");
		CCASSERT(m_sprBg == NULL, msg);
#endif
		return;
	}

	m_sprBg = sprBg;
	if (!m_sprBg)return;

	Size size = Director::getInstance()->getWinSize();
	m_sprBg->setPosition(size.width / 2, size.height / 2);
	addChild(m_sprBg, 2);
}

void UIPopupWindow::setBackgroundImagePosition(const Point& position)
{
	if (!m_sprBg)return;
	m_sprBg->setPosition(position);
}

void UIPopupWindow::setTextInit() //출력할 문자 UI초기화
{
	Size size = Director::getInstance()->getWinSize();

	m_txtTitle = Text::create();    //타이틀
									//m_txtTitle->setFontName(GET_TTF_FONTNAME()); //다국어 지원을 위한 TTF폰트 설정
	m_txtTitle->setString("");
	m_txtTitle->setFontSize(20);
	m_txtTitle->setColor(Color3B(0, 0, 0));

	if (m_sprBg)
	{
		Rect rct = m_sprBg->getTextureRect();
		m_txtTitle->setPosition(Point(size.width / 2, (size.height / 2 + rct.size.height / 2) - 40));
	}

	m_txt = Text::create();
	m_txt->setString("");

	//m_txt->setFontName(GET_TTF_FONTNAME());//다국어 지원을 위한 TTF폰트 설정
	m_txt->setFontSize(20);
	m_txt->setColor(Color3B(255, 255, 255));
	m_txt->setPosition(Point(size.width / 2, (size.height / 2) + 20));

	addChild(m_txtTitle, (int)m_nZorderCnt + 100);
	addChild(m_txt, (int)m_nZorderCnt + 100);

}


void UIPopupWindow::addButton(const char* normalTexture, const char* selectedTexture, const char* disabledTexture, Widget::TextureResType texType, const Point &pos, const std::string& text, const int nTag)
{
	//팝업창에 버튼을 생성한다.
	cocos2d::ui::Button *pBtn = cocos2d::ui::Button::create();
	pBtn->setTouchEnabled(true);
	pBtn->loadTextures(normalTexture, selectedTexture, disabledTexture, texType);
	pBtn->setTitleText(text);
	if (m_sprBg)
	{
		Point pp = m_sprBg->getPosition();
		Point newPoint;
		newPoint.setPoint(pos.x + pp.x, pos.y + pp.y);
		pBtn->setPosition(newPoint);
	}
	else
	{
		pBtn->setPosition(pos);
	}

	pBtn->setTag(nTag);
	// pBtn->addTouchEventListener(this,toucheventselector(UIPopupWindow::onBtnClickCallbackFnc) ); //이부분은 3.0부터 사용하지않도록 권장된다.
	pBtn->addTouchEventListener(CC_CALLBACK_2(UIPopupWindow::onBtnClickCallbackFnc, this)); //버튼이 클릭시 콜백함수 설정

	addChild(pBtn, (int)m_nZorderCnt);
	m_nZorderCnt++;
}


void  UIPopupWindow::setTitleString(const std::string& text)
{
	m_txtTitle->setString(text);
}
void  UIPopupWindow::setMessageString(const std::string& text)
{
	m_txt->setString(text);
}

void UIPopupWindow::setFontSize_Title(int size)   //타이틀 폰트 사이즈를 설정한다.
{
	m_txtTitle->setFontSize(size);
}
void UIPopupWindow::setColor_Title(const Color3B& color)  //타이틀 폰트 색상 설정
{
	m_txtTitle->setColor(color);

}
void UIPopupWindow::setPosition_Title(const Point& position)
{
	m_txtTitle->setPosition(position);
}
void UIPopupWindow::setFontName_Title(const std::string& name)
{
	m_txtTitle->setFontName(name);
}
void UIPopupWindow::setFontSize_Msg(int size)     //메시지의 폰트 사이즈를 설정한다.
{
	m_txt->setFontSize(size);
}
void UIPopupWindow::setColor_Msg(const Color3B& color)    //메시지 폰트 색상 설정
{
	m_txt->setColor(color);
}
void UIPopupWindow::setPosition_Msg(const Point& position)
{
	m_txt->setPosition(position);
}

void UIPopupWindow::setFontName_Msg(const std::string& name)
{
	m_txt->setFontName(name);
}