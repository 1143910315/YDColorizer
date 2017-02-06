/*************************************************
Author:            |メ破坏者☆
Date:              |2017-02-06
version：          |0.0.0
Description:       |封装一些多次使用的函数
**************************************************/
#pragma once
#include <Windows.h>
class Tool
{
public:
	//Config();
	//WCHAR* initialize();
	bool CharAddChar(char* target, int targetSize, const char* source, int sourceSize);
	bool ChartoWCHAR(WCHAR* target, int targetSize, const char* source, int sourceSize);
	WCHAR* ChartoWCHAR(const char* source, int sourceSize);
private:
	//char *GetDLLPath();
	//const char* fileSet = "YDColorizerConfig.ini";//配置文件名
	//const LPCWSTR globalSet = TEXT("Application");//全局配置项
	//const LPCWSTR languageSet = TEXT("Language");//语言版本
	//const char* defaultSet = "[Application]\nLanguage = 0\n; 语言, 0->简体中文, 1->繁体中文";
	//默认配置文件内容
	//UINT language;
};