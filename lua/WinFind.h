/*************************************************
Author:            |メ破坏者☆
Date:              |2017-02-07
version：          |0.0.0
Description:       |寻找窗口
**************************************************/
#pragma once
#include <Windows.h>
class WinFind
{
public:
	WinFind();

	//Config();
	//WCHAR* initialize();
	/*bool CharAddChar(char* target, int targetSize, const char* source, int sourceSize);
	bool ChartoWCHAR(WCHAR* target, int targetSize, const char* source, int sourceSize);
	WCHAR* ChartoWCHAR(const char* source, int sourceSize);*/
private:
	//********************************以下为WorldEditStrings.txt_项名
	LPCWSTR WESTRING_COD_TYPE_STRINGstr;//字符串
	LPCWSTR WESTRING_UE_DLG_EDITVALUEstr;//编辑单位值 - %s
	LPCWSTR WESTRING_IE_DLG_EDITVALUEstr;//编辑物品值 - %s
	LPCWSTR WESTRING_AE_DLG_EDITVALUEstr;//编辑技能值 - %s
	LPCWSTR WESTRING_FE_DLG_EDITVALUEstr;//编辑效果值 - %s
	LPCWSTR WESTRING_BE_DLG_EDITVALUEstr;//编辑可破坏物值 - %s
	LPCWSTR WESTRING_DE_DLG_EDITVALUEstr;//编辑装饰物值 - %s
	LPCWSTR WESTRING_GE_DLG_EDITVALUEstr;//编辑科技值 - %s
   //********************************
   //char *GetDLLPath();
   //const char* fileSet = "YDColorizerConfig.ini";//配置文件名
   //const LPCWSTR globalSet = TEXT("Application");//全局配置项
   //const LPCWSTR languageSet = TEXT("Language");//语言版本
   //const char* defaultSet = "[Application]\nLanguage = 0\n; 语言, 0->简体中文, 1->繁体中文";
   //默认配置文件内容
   //UINT language;


/*
		' “528654” | “编辑单位值 - 字符串” | “#32770”
		' “2296770” | “物体编辑器” | “#32770”

		' “725440” | “字符串” | “#32770”
		' “4131942” | “设置 动作” | “#32770”
		' “2101072” | “触发编辑器” | “#32770”

		' Edit*/

};