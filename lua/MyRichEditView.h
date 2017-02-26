/*************************************************
Author:            |メ破坏者☆
Date:              |2017-02-26
version：          |0.0.1
Description:       |富文本控件
**************************************************/
#pragma once
#include <Windows.h>
#include <commctrl.h>
#include <Richedit.h>
//#include <afxrich.h>
#pragma comment(lib,"comctl32.lib")
#include "Language.h"
#include "Tool.h"
class MyRichEditView 
{
public:
	MyRichEditView(HWND hwndParent,long top,long width, const Language* L);
	bool SetColor();
	void setText(const LPWSTR text,int len);
	HWND getHwnd();
	//Config();
	//WCHAR* initialize();
	/*bool CharAddChar(char* target, int targetSize, const char* source, int sourceSize);
	bool ChartoWCHAR(WCHAR* target, int targetSize, const char* source, int sourceSize);
	WCHAR* ChartoWCHAR(const char* source, int sourceSize);*/
private:
	HWND hRichEdit;
	Tool T=Tool();
	//char *GetDLLPath();
	//const char* fileSet = "YDColorizerConfig.ini";//配置文件名
	//const LPCWSTR globalSet = TEXT("Application");//全局配置项
	//const LPCWSTR languageSet = TEXT("Language");//语言版本
	//const char* defaultSet = "[Application]\nLanguage = 0\n; 语言, 0->简体中文, 1->繁体中文";
	//默认配置文件内容
	//UINT language;
};