/*************************************************
Author:            |メ破坏者☆
Date:              |2017-02-28
version：          |0.0.2
Description:       |富文本控件
**************************************************/
#pragma once
#include "Language.h"
#include "Tool.h"
#include <Windows.h>
#include <Richedit.h>
//富文本组件
class MyRichEditView {
public:
	MyRichEditView(HWND hwndParent, long top, long width, const Language* L);
	bool SetColor();//应用颜色到选择的文本
	void setText(const LPWSTR text, int len);//设置未格式文本到富文本编辑框
	HWND getHwnd();//获取富文本编辑框句柄
private:
	HWND hRichEdit;//储存富文本编辑框句柄
	Tool T = Tool();//工具类
	CHARFORMATW defaultFormat = CHARFORMATW();//默认的文本格式
};