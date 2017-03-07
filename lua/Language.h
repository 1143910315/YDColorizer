/*************************************************
Author:            |メ破坏者☆
Date:              |2017-02-28
version：          |0.0.1
Description:       |和显示语言有关
**************************************************/
#pragma once
#include <Windows.h>
//与语言相关
class Language {
public:
	Language(int language);//设置语言
	LPCWSTR lessDLL;//缺少DLL
	LPCWSTR error;//错误
	LPCWSTR CreateRichEditViewerror;//创建富文本编辑框失败
	LPCWSTR CreateWindowError;//创建窗口失败
	LPCWSTR gainText;//获取文本
	LPCWSTR applyText;//应用文本
	LPCWSTR colorAlarm;//颜色警告
	LPCWSTR alarm;//警告
};