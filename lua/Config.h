/*************************************************
Author:            |メ破坏者☆
Date:              |2017-02-05
version：          |0.0.0
Description:       |读取配置、设置语言等等
**************************************************/
#pragma once
#include <Windows.h>
class Config
{
public:
	Config();
	//WCHAR* initialize();

private:
	//char *GetDLLPath();
	const char* fileSet = "YDColorizerConfig.ini";//配置文件名
	const LPCWSTR globalSet = TEXT("Application");//全局配置项
	const LPCWSTR languageSet = TEXT("Language");//语言版本
	const char* defaultSet = "[Application]\nLanguage = 0\n; 语言, 0->简体中文, 1->繁体中文";
	//默认配置文件内容
	UINT language;
};