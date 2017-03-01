/*************************************************
Author:            |メ破坏者☆
Date:              |2017-02-28
version：          |0.1.1
Description:       |寻找窗口
**************************************************/
#pragma once
#include <Windows.h>
#include "Language.h"
typedef wchar_t CHAO[50];
//寻找物编窗口
class WinFind {
public:
	WinFind(const Language* L);
	void Find();//寻找一次物编窗口
private:
	struct win {
		HWND hwnd = NULL;
		win* next = NULL;
	}wininfo;//记录已经找过的窗口
	const Language* L;//语言类
	CHAO westring[8];//储存窗口标题
};