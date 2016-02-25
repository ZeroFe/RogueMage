#include "Markup.h"
#include <iostream>
#include <cstring>


int main()
{
	CMarkup xml;
	
	char *ch = new char[100];

	CString str;
	int cnt;

	int num;

	std::cin >> cnt;

	xml.AddElem(_T("SETTING"));
	xml.AddChildElem(_T("COUNT"));
	xml.IntoElem();
	xml.AddAttrib(_T("NUM"),_T("3"));
	xml.OutOfElem();
	
	for (int i = 0; i < cnt; i++)
	{
		xml.AddElem(_T("CHAR"));
		
		std::cout << "ĳ������ �̸� : ";
		std::cin >> ch;
		str= (LPCSTR)(LPSTR)ch;

		
		xml.AddChildSubDoc(_T("<NAME>")+str+_T("</NAME>"));

		std::cout << "��������Ʈ ��� : ";
		std::cin >> ch;
		str = (LPCSTR)(LPSTR)ch;


		xml.AddChildSubDoc(_T("<SPRITE>") + str + _T("</SPRITE>"));



		xml.AddChildElem(_T("STAT"));

		std::cout << "HP : ";
		std::cin >> num;
		xml.AddChildAttrib(_T("HP"), num);
		std::cout << "MP : ";
		std::cin >> num;
		xml.AddChildAttrib(_T("MP"), num);
		std::cout << "MPRegen : ";
		std::cin >> num;
		xml.AddChildAttrib(_T("MRegen"), num);

		xml.AddChildElem(_T("STAT"));

		std::cout << "ATK : ";
		std::cin >> num;
		xml.AddChildAttrib(_T("ATK"), num);
		std::cout << "DEF : ";
		std::cin >> num;
		xml.AddChildAttrib(_T("DEF"), num);
		std::cout << "SPD : ";
		std::cin >> num;
		xml.AddChildAttrib(_T("SPD"), num);
		std::cout << "ASPD : ";
		std::cin >> num;
		xml.AddChildAttrib(_T("ASPD"), num);

		/*
		��ų�κ� �߰�����
		*/

		xml.AddChildElem(_T("STORY"));
		xml.IntoElem();

		while (1)
		{
			std::cout << "���丮(q�Է½� �ߴ�) : ";
			std::cin >> ch;

			if (!strcmp(ch, "q"))
				break;
			str = (LPCSTR)(LPSTR)ch;


			xml.AddChildSubDoc(_T("<LINE>") + str + _T("</LINE>"));
		}
	
	}

	xml.Save(_T("Test.xml"));
}