#include "Markup.h"
#include <iostream>
#include <cstring>

#define _lpw

void write()
{
	CMarkup xml;

	char *ch = new char[100];

	CString str;
	int cnt;

	int temp;
	int num;

	xml.Load(_T("Test.xml"));

	xml.FindElem(_T("SETTING"));
	xml.IntoElem();
	xml.FindElem(_T("COUNT"));

	str = xml.GetAttrib(_T("NUM"));

	cnt = _ttoi(str);

	std::cin >> temp;

	cnt += temp;



	xml.AddAttrib(_T("NUM"), cnt);
	xml.OutOfElem();

	while (xml.FindElem(_T("CHAR")));

	for (int i = 0; i < temp; i++)
	{
		xml.AddElem(_T("CHAR"));

		std::cout << "캐릭터의 이름 : ";
		std::cin >> ch;
		str = (LPCSTR)(LPSTR)ch;


		xml.AddChildSubDoc(_T("<NAME>") + str + _T("</NAME>"));

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
		xml.OutOfElem();

	}

	xml.Save(_T("Test.xml"));
}

void read()
{
	CMarkup xml;

	char *ch;
	int len;
	
	CString str;
	CString name;
	CString path;

	int stat[7];

	int cnt;

	xml.Load(_T("Test.xml"));

	xml.FindElem(_T("SETTING"));
	xml.IntoElem();
	xml.FindElem(_T("COUNT"));
	str = xml.GetAttrib(_T("NUM"));
	//ch = LPSTR(LPCTSTR(str));
	//cnt = atoi(ch);
	cnt = _ttoi(str);
	xml.OutOfElem();

	std::cout << cnt<<std::endl;

	for (int i = 0; i < cnt; i++)
	{
		xml.FindElem(_T("CHAR"));
		xml.IntoElem();

		xml.FindElem(_T("NAME"));
		name = xml.GetSubDoc();

		xml.FindElem(_T("SPRITE"));
		path = xml.GetSubDoc();

		xml.FindElem(_T("STAT"));
		//xml.IntoElem();

		str = xml.GetAttrib(_T("HP"));
		stat[0] = _ttoi(str);
		str = xml.GetAttrib(_T("MP"));
		stat[1] = _ttoi(str);
		str = xml.GetAttrib(_T("MRegen"));
		stat[2] = _ttoi(str);

		xml.FindElem(_T("STAT"));

		str = xml.GetAttrib(_T("ATK"));
		stat[3] = _ttoi(str);
		str = xml.GetAttrib(_T("DEF"));
		stat[4] = _ttoi(str);
		str = xml.GetAttrib(_T("SPD"));
		stat[5] = _ttoi(str);
		str = xml.GetAttrib(_T("ASPD"));
		stat[6] = _ttoi(str);

		std::cout << "HP = " << stat[0] << std::endl;
		std::cout << "MP = " << stat[1] << std::endl;
		std::cout << "MRegen = " << stat[2] << std::endl;
		std::cout << "ATK = " << stat[3] << std::endl;
		std::cout << "DEF = " << stat[4] << std::endl;
		std::cout << "SPD = " << stat[5] << std::endl;
		std::cout << "ASPD = " << stat[6] << std::endl<<std::endl;

		xml.OutOfElem();
	}

}

int main()
{
	int check;

	std::cout << "select mode(0:read,1:write)";

	std::cin >> check;

	if (check == 0)
		read();
	else
		write();
	
}