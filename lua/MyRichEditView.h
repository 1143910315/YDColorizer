/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-07
version��          |0.0.0
Description:       |���ı��ؼ�
**************************************************/
#pragma once
#include <Windows.h>
#include <commctrl.h>
#include <Richedit.h>
//#include <afxrich.h>
#pragma comment(lib,"comctl32.lib")
#include "Language.h"
class MyRichEditView 
{
public:
	MyRichEditView(HWND hwndParent,long top,long width, const Language* L);
	bool SetColor();
	void setText();
	HWND getHwnd();
	//Config();
	//WCHAR* initialize();
	/*bool CharAddChar(char* target, int targetSize, const char* source, int sourceSize);
	bool ChartoWCHAR(WCHAR* target, int targetSize, const char* source, int sourceSize);
	WCHAR* ChartoWCHAR(const char* source, int sourceSize);*/
private:
	HWND hRichEdit;
	//char *GetDLLPath();
	//const char* fileSet = "YDColorizerConfig.ini";//�����ļ���
	//const LPCWSTR globalSet = TEXT("Application");//ȫ��������
	//const LPCWSTR languageSet = TEXT("Language");//���԰汾
	//const char* defaultSet = "[Application]\nLanguage = 0\n; ����, 0->��������, 1->��������";
	//Ĭ�������ļ�����
	//UINT language;
};