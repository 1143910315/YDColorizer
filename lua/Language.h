/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-06
version��          |0.0.0
Description:       |����ʾ�����й�
**************************************************/
#pragma once
#include <Windows.h>
class Language
{
public:
	Language(int language);
	LPCWSTR lessDLL;
	LPCWSTR error;
	LPCWSTR CreateRichEditViewerror;
	//Config();
	//WCHAR* initialize();
	/*bool CharAddChar(char* target, int targetSize, const char* source, int sourceSize);
	bool ChartoWCHAR(WCHAR* target, int targetSize, const char* source, int sourceSize);
	WCHAR* ChartoWCHAR(const char* source, int sourceSize);*/
private:
	//char *GetDLLPath();
	//const char* fileSet = "YDColorizerConfig.ini";//�����ļ���
	//const LPCWSTR globalSet = TEXT("Application");//ȫ��������
	//const LPCWSTR languageSet = TEXT("Language");//���԰汾
	//const char* defaultSet = "[Application]\nLanguage = 0\n; ����, 0->��������, 1->��������";
	//Ĭ�������ļ�����
	//UINT language;
};