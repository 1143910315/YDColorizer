/*************************************************
Author:            |メ破坏者☆
Date:              |2017-02-28
version：          |0.2.1
Description:       |封装一些多次使用的函数
**************************************************/
#pragma once
#include <Windows.h>
//与工具有关
class Tool {
public:
	bool CharAddChar(char* target, int targetSize, const char* source, int sourceSize);//两字节文本相加
	bool ChartoWCHAR(LPWSTR target, int targetSize, const char* source, int sourceSize);//字节文本到宽字节文本（target大小需要计算）
	LPWSTR ChartoWCHAR(const char* source, int sourceSize);//字节文本到宽字节文本（返回的占用大小刚好满足）
	LPWSTR UTF8ToGBK(const LPWSTR strUTF8);//字节文本转化为UTF8编码
	LPWSTR UTF8ToGBK(const LPSTR strUTF8);//宽字节文本转化为UTF8编码
	void UTF8ToGBK(const LPSTR strUTF8, LPWSTR target, int size);//宽字节文本转化为UTF8编码（结果到给定内存）
	bool equal(const LPWSTR a, const LPWSTR b, UINT32 size);//判断（宽字节文本）是否全等
	bool nextNumIsValid(const LPWSTR lpwstr, int wcharNum);//接下来的wcharNum个宽字节文本是否有效
	int Wchar2color(WCHAR first, WCHAR second);//将宽字节文本转化为整数
	bool color2hex(LPWSTR target,COLORREF color);//将颜色转换为文本，必需6字节
};