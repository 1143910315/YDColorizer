/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-27
version��          |0.2.0
Description:       |��װһЩ���ʹ�õĺ���
**************************************************/
#pragma once
#include <Windows.h>
//#include <string>
class Tool
{
public:
	//Config();
	//WCHAR* initialize();
	bool CharAddChar(char* target, int targetSize, const char* source, int sourceSize);
	bool ChartoWCHAR(LPWSTR target, int targetSize, const char* source, int sourceSize);
	LPWSTR ChartoWCHAR(const char* source, int sourceSize);
	LPWSTR UTF8ToGBK(const LPWSTR strUTF8);
	LPWSTR UTF8ToGBK(const LPSTR strUTF8);
	bool equal(const LPWSTR a, const LPWSTR b, UINT32 size);
	bool nextNumIsValid(const LPWSTR lpwstr,int wcharNum);
	int Wchar2color(WCHAR first,WCHAR second);
private:
	//char *GetDLLPath();
	//const char* fileSet = "YDColorizerConfig.ini";//�����ļ���
	//const LPCWSTR globalSet = TEXT("Application");//ȫ��������
	//const LPCWSTR languageSet = TEXT("Language");//���԰汾
	//const char* defaultSet = "[Application]\nLanguage = 0\n; ����, 0->��������, 1->��������";
	//Ĭ�������ļ�����
	//UINT language;
};