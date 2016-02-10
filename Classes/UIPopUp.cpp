#include "UIPopup.h"

UIPopupWindow *UIPopupWindow::create(Sprite *sprBackgroundBoard, Sprite *sprBackgroundImg)
{
	UIPopupWindow *pRet = new UIPopupWindow();
	if (pRet && pRet->init())
	{
		pRet->setBackgroundBorard(sprBackgroundBoard);
		pRet->setBackgroundImage(sprBackgroundImg);
		pRet->setTextInit(); //����� ���� UI�ʱ�ȭ

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
	m_nZorderCnt = 1;//�߰��� �ڽİ�ü�鿡 ���� Zorder�� ���������
	m_sprBg = NULL;

	return true;
}


void UIPopupWindow::onBtnClickCallbackFnc(Ref *pSender, ui::Widget::TouchEventType touchType)
{
	// �����߰��Ǵ� ��ư�� ���� �̺�Ʈ�ڵ鷯 �Լ�����...
	if (touchType == ui::Widget::TouchEventType::ENDED)
	{
		//SimpleAudioEngine::getInstance()->playEffect( DF_SOUND_UI_01); //�̺κ��� ��ưŬ���� ����Ʈ ���� �������ؼ�

		m_nResult = ((cocos2d::ui::Button*)pSender)->getTag();    //� ��ư���� üũ�� ���� ��ư�� �߰��� Tag�� �ɹ��������� �������ֵ��� �Ѵ�.
		onCallBackFunc();   //���� BaseŬ������ �˾� �ݹ��Լ��� ȣ���Ѵ�.
	}
}


void UIPopupWindow::setBackgroundBorard(Sprite  *sprBg)//�˾� �Ʒ��� �����̳� �� �̷���? �Ͽ��� �� �عٴ�
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

void UIPopupWindow::setTextInit() //����� ���� UI�ʱ�ȭ
{
	Size size = Director::getInstance()->getWinSize();

	m_txtTitle = Text::create();    //Ÿ��Ʋ
									//m_txtTitle->setFontName(GET_TTF_FONTNAME()); //�ٱ��� ������ ���� TTF��Ʈ ����
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

	//m_txt->setFontName(GET_TTF_FONTNAME());//�ٱ��� ������ ���� TTF��Ʈ ����
	m_txt->setFontSize(20);
	m_txt->setColor(Color3B(255, 255, 255));
	m_txt->setPosition(Point(size.width / 2, (size.height / 2) + 20));

	addChild(m_txtTitle, (int)m_nZorderCnt + 100);
	addChild(m_txt, (int)m_nZorderCnt + 100);

}


void UIPopupWindow::addButton(const char* normalTexture, const char* selectedTexture, const char* disabledTexture, Widget::TextureResType texType, const Point &pos, const std::string& text, const int nTag)
{
	//�˾�â�� ��ư�� �����Ѵ�.
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
	// pBtn->addTouchEventListener(this,toucheventselector(UIPopupWindow::onBtnClickCallbackFnc) ); //�̺κ��� 3.0���� ��������ʵ��� ����ȴ�.
	pBtn->addTouchEventListener(CC_CALLBACK_2(UIPopupWindow::onBtnClickCallbackFnc, this)); //��ư�� Ŭ���� �ݹ��Լ� ����

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

void UIPopupWindow::setFontSize_Title(int size)   //Ÿ��Ʋ ��Ʈ ����� �����Ѵ�.
{
	m_txtTitle->setFontSize(size);
}
void UIPopupWindow::setColor_Title(const Color3B& color)  //Ÿ��Ʋ ��Ʈ ���� ����
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
void UIPopupWindow::setFontSize_Msg(int size)     //�޽����� ��Ʈ ����� �����Ѵ�.
{
	m_txt->setFontSize(size);
}
void UIPopupWindow::setColor_Msg(const Color3B& color)    //�޽��� ��Ʈ ���� ����
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