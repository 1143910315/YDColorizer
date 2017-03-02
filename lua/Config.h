/*************************************************
Author:            |メ破坏者☆
Date:              |2017-02-28
version：          |0.1.1
Description:       |读取配置
**************************************************/
#pragma once
#include <Windows.h>
#include "Tool.h"
//与配置相关
class Config {
public:
	int GetLanguage();//从配置获取语言
	LPWSTR WESTRING_COD_TYPE_STRING(); //= 字符串
	void WESTRING_COD_TYPE_STRING(LPWSTR target, int size, LPSTR path); //= 字符串
	LPWSTR WESTRING_UE_DLG_EDITVALUE();//= 编辑单位值 - %s
	void WESTRING_UE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path);//= 编辑单位值 - %s
	LPWSTR WESTRING_IE_DLG_EDITVALUE();//= 编辑物品值 - %s
	void WESTRING_IE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path);//= 编辑物品值 - %s
	LPWSTR WESTRING_AE_DLG_EDITVALUE();//= 编辑技能值 - %s
	void WESTRING_AE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path);//= 编辑技能值 - %s
	LPWSTR WESTRING_FE_DLG_EDITVALUE();//= 编辑效果值 - %s
	void WESTRING_FE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path);//= 编辑效果值 - %s
	LPWSTR WESTRING_BE_DLG_EDITVALUE();//= 编辑可破坏物值 - %s
	void WESTRING_BE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path);//= 编辑可破坏物值 - %s
	LPWSTR WESTRING_DE_DLG_EDITVALUE();//= 编辑装饰物值 - %s
	void WESTRING_DE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path);//= 编辑装饰物值 - %s
	LPWSTR WESTRING_GE_DLG_EDITVALUE();//= 编辑科技值 - %s
	void WESTRING_GE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path);//= 编辑科技值 - %s
private:
	Tool T = Tool();//工具类
	const LPCWSTR globalSet = TEXT("Application");//插件配置项_节名
	const LPCWSTR languageSet = TEXT("Language");//插件语言版本_项名
	const char lpAppName[40] = "WorldEditStrings";//WorldEditStrings.txt_节名
	//********************************以下为WorldEditStrings.txt_项名
	const char WESTRING_COD_TYPE_STRINGstr[40] = "WESTRING_COD_TYPE_STRING";  //字符串
	const char WESTRING_UE_DLG_EDITVALUEstr[40] = "WESTRING_UE_DLG_EDITVALUE";//编辑单位值 - %s
	const char WESTRING_IE_DLG_EDITVALUEstr[40] = "WESTRING_IE_DLG_EDITVALUE";//编辑物品值 - %s
	const char WESTRING_AE_DLG_EDITVALUEstr[40] = "WESTRING_AE_DLG_EDITVALUE";//编辑技能值 - %s
	const char WESTRING_FE_DLG_EDITVALUEstr[40] = "WESTRING_FE_DLG_EDITVALUE";//编辑效果值 - %s
	const char WESTRING_BE_DLG_EDITVALUEstr[40] = "WESTRING_BE_DLG_EDITVALUE";//编辑可破坏物值 - %s
	const char WESTRING_DE_DLG_EDITVALUEstr[40] = "WESTRING_DE_DLG_EDITVALUE";//编辑装饰物值 - %s
	const char WESTRING_GE_DLG_EDITVALUEstr[40] = "WESTRING_GE_DLG_EDITVALUE";//编辑科技值 - %s
};