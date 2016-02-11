#include "UIPopup.h"

UIPopup *UIPopup::create(Node* popupLayer)
{
	UIPopup *pRet = new UIPopup();
	if (pRet && pRet->init())
	{
		//pRet->setBackgroundBorard(sprBackgroundBoard);
		//pRet->setBackgroundImage(sprBackgroundImg);
		pRet->setPopupLayer(popupLayer);
		pRet->setTextInit(); //����� ���� UI�ʱ�ȭ

		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool UIPopup::onInit()
{
	m_nZorderCnt = 1;//�߰��� �ڽİ�ü�鿡 ���� Zorder�� ���������
	m_sprBg = NULL;
	pLayer = NULL;

	return true;
}


void UIPopup::onBtnClickCallbackFnc(Ref *pSender, ui::Widget::TouchEventType touchType)
{
	// �����߰��Ǵ� ��ư�� ���� �̺�Ʈ�ڵ鷯 �Լ�����...
	if (touchType == ui::Widget::TouchEventType::ENDED)
	{
		//SimpleAudioEngine::getInstance()->playEffect( DF_SOUND_UI_01); //�̺κ��� ��ưŬ���� ����Ʈ ���� �������ؼ�

		m_nResult = ((cocos2d::ui::Button*)pSender)->getTag();    //� ��ư���� üũ�� ���� ��ư�� �߰��� Tag�� �ɹ��������� �������ֵ��� �Ѵ�.
		onCallBackFunc();   //���� BaseŬ������ �˾� �ݹ��Լ��� ȣ���Ѵ�.
	}
}

/*
set popup Layer and add it
*/
void UIPopup::setPopupLayer(Node* popupLayer)
{
	if (!popupLayer) return;
	pLayer = popupLayer;
	Size size = Director::getInstance()->getWinSize();
	pLayer->setPosition(size.width / 2, size.height / 2);
	addChild(pLayer, -100);
}

void UIPopup::setBackgroundBorard(Sprite  *sprBg)//�˾� �Ʒ��� �����̳� �� �̷���? �Ͽ��� �� �عٴ�
{
	if (!sprBg)return;

	Size size = Director::getInstance()->getWinSize();
	sprBg->setPosition(size.width / 2, size.height / 2);
	addChild(sprBg, -100);
}


void UIPopup::setBackgroundImage(Sprite  *sprBg)
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
	addChild(m_sprBg, -1);
}

void UIPopup::setBackgroundImagePosition(const Point& position)
{
	if (!m_sprBg)return;
	m_sprBg->setPosition(position);
}

void UIPopup::setTextInit() //����� ���� UI�ʱ�ȭ
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

/*
use Cocos Studio -> popupLayer
name : find name of button
tag : set tag of button
*/
void UIPopup::setButton(const std::string &name, const int tag)
{
	Button* pButton = static_cast<Button*>(pLayer->getChildByName(name));
	pButton->setTouchEnabled(true);
	pButton->setTag(tag);
	pButton->addTouchEventListener(CC_CALLBACK_2(UIPopup::onBtnClickCallbackFnc, this));
	pButton->setLocalZOrder((int)m_nZorderCnt);
	m_nZorderCnt++;
}

void UIPopup::addButton(const char* normalTexture, const char* selectedTexture, const char* disabledTexture, Widget::TextureResType texType, const Point &pos, const std::string& text, const int nTag)
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
	// pBtn->addTouchEventListener(this,toucheventselector(UIPopup::onBtnClickCallbackFnc) ); //�̺κ��� 3.0���� ��������ʵ��� ����ȴ�.
	pBtn->addTouchEventListener(CC_CALLBACK_2(UIPopup::onBtnClickCallbackFnc, this)); //��ư�� Ŭ���� �ݹ��Լ� ����

	addChild(pBtn, (int)m_nZorderCnt);
	m_nZorderCnt++;
}


void  UIPopup::setTitleString(const std::string& text)
{
	m_txtTitle->setString(text);
}
void  UIPopup::setMessageString(const std::string& text)
{
	m_txt->setString(text);
}

void UIPopup::setFontSize_Title(int size)   //Ÿ��Ʋ ��Ʈ ����� �����Ѵ�.
{
	m_txtTitle->setFontSize(size);
}
void UIPopup::setColor_Title(const Color3B& color)  //Ÿ��Ʋ ��Ʈ ���� ����
{
	m_txtTitle->setColor(color);

}
void UIPopup::setPosition_Title(const Point& position)
{
	m_txtTitle->setPosition(position);
}
void UIPopup::setFontName_Title(const std::string& name)
{
	m_txtTitle->setFontName(name);
}
void UIPopup::setFontSize_Msg(int size)     //�޽����� ��Ʈ ����� �����Ѵ�.
{
	m_txt->setFontSize(size);
}
void UIPopup::setColor_Msg(const Color3B& color)    //�޽��� ��Ʈ ���� ����
{
	m_txt->setColor(color);
}
void UIPopup::setPosition_Msg(const Point& position)
{
	m_txt->setPosition(position);
}

void UIPopup::setFontName_Msg(const std::string& name)
{
	m_txt->setFontName(name);
}