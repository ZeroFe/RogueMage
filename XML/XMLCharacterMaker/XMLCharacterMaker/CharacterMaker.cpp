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
		
		std::cout << "캐릭터의 이름 : ";
		std::cin >> ch;
		str= (LPCSTR)(LPSTR)ch;

		
		xml.AddChildSubDoc(_T("<NAME>")+str+_T("</NAME>"));

		std::cout << "스프라이트 경로 : ";
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
		스킬부분 추가예정
		*/

		xml.AddChildElem(_T("STORY"));
		xml.IntoElem();

		while (1)
		{
			std::cout << "스토리(q입력시 중단) : ";
			std::cin >> ch;

			if (!strcmp(ch, "q"))
				break;
			str = (LPCSTR)(LPSTR)ch;


			xml.AddChildSubDoc(_T("<LINE>") + str + _T("</LINE>"));
		}
	
	}

	xml.Save(_T("Test.xml"));
}