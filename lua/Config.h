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
	//WCHAR* initialize();
	int GetLanguage();
	LPWSTR WESTRING_COD_TYPE_STRING();// = 字符串
	LPWSTR WESTRING_UE_DLG_EDITVALUE();//=编辑单位值 - %s
	LPWSTR WESTRING_IE_DLG_EDITVALUE();//=编辑物品值 - %s
	LPWSTR WESTRING_AE_DLG_EDITVALUE();//=编辑技能值 - %s
	LPWSTR WESTRING_FE_DLG_EDITVALUE();//=编辑效果值 - %s
	LPWSTR WESTRING_BE_DLG_EDITVALUE();//=编辑可破坏物值 - %s
	LPWSTR WESTRING_DE_DLG_EDITVALUE();//=编辑装饰物值 - %s
	LPWSTR WESTRING_GE_DLG_EDITVALUE();//=编辑科技值 - %s
private:
	//char *GetDLLPath();

	const LPCWSTR globalSet = TEXT("Application");//插件配置项_节名
	const LPCWSTR languageSet = TEXT("Language");//插件语言版本_项名
	const LPCWSTR lpAppName = TEXT("WorldEditStrings");//WorldEditStrings.txt_节名
	//********************************以下为WorldEditStrings.txt_项名
	const LPCWSTR WESTRING_COD_TYPE_STRINGstr = TEXT("WESTRING_COD_TYPE_STRING");//字符串
	const LPCWSTR WESTRING_UE_DLG_EDITVALUEstr = TEXT("WESTRING_UE_DLG_EDITVALUE");//编辑单位值 - %s
	const LPCWSTR WESTRING_IE_DLG_EDITVALUEstr = TEXT("WESTRING_IE_DLG_EDITVALUE");//编辑物品值 - %s
	const LPCWSTR WESTRING_AE_DLG_EDITVALUEstr = TEXT("WESTRING_AE_DLG_EDITVALUE");//编辑技能值 - %s
	const LPCWSTR WESTRING_FE_DLG_EDITVALUEstr = TEXT("WESTRING_FE_DLG_EDITVALUE");//编辑效果值 - %s
	const LPCWSTR WESTRING_BE_DLG_EDITVALUEstr = TEXT("WESTRING_BE_DLG_EDITVALUE");//编辑可破坏物值 - %s
	const LPCWSTR WESTRING_DE_DLG_EDITVALUEstr = TEXT("WESTRING_DE_DLG_EDITVALUE");//编辑装饰物值 - %s
	const LPCWSTR WESTRING_GE_DLG_EDITVALUEstr = TEXT("WESTRING_GE_DLG_EDITVALUE");//编辑科技值 - %s
	//********************************
/********************************默认配置文件内容
[Application]
Language = 0
; 语言, 0->简体中文, 1->繁体中文"
	********************************/
};