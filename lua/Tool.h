/*************************************************
Author:            |メ破坏者☆
Date:              |2017-02-27
version：          |0.2.0
Description:       |封装一些多次使用的函数
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
	//const char* fileSet = "YDColorizerConfig.ini";//配置文件名
	//const LPCWSTR globalSet = TEXT("Application");//全局配置项
	//const LPCWSTR languageSet = TEXT("Language");//语言版本
	//const char* defaultSet = "[Application]\nLanguage = 0\n; 语言, 0->简体中文, 1->繁体中文";
	//默认配置文件内容
	//UINT language;
};