#include "Tool.h"
/*************************************************
Function:         |CharAddChar
Description:      |将两段字节文本相加到第一个字节文本
Input:            |targetSize  ：target的长度
				   source      ：欲加的字节文本
				   sourceSize  ：欲加的字节文本的长度
Output:           |target      ：欲被加的字节文本
Return:           |如果全部都加入了，返回true，空间不足返回false
*************************************************/
bool Tool::CharAddChar(char* target, int targetSize, const char* source, int sourceSize) {
	for (int i = 0; i < targetSize; i++) {
		if (target[i] == '\0') {
			int j = 0;
			for (; i < targetSize - 1 && j < sourceSize; i++, j++) {
				target[i] = source[j];
			}
			target[i] = '\0';//保证字符串收尾。
			if (j == sourceSize) {
				return true;
			}
			break;
		}
	}
	return false;
}
/*************************************************
Function:         |ChartoWCHAR
Description:      |将字节数组转化为宽字符数组
Input:            |targetSize   ：target的长度
				   source       ：字节文本
				   sourceSize   ：字节文本的长度
Output:           |target       ：转换后的宽字符文本
Return:           |如果长度不够，返回false，否则返回true
*************************************************/
bool Tool::ChartoWCHAR(LPWSTR target, int targetSize, const char* source, int sourceSize) {
	int need = MultiByteToWideChar(CP_ACP, 0, source, sourceSize, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, source, sourceSize, target, targetSize);
	if (need <= targetSize) {
		return true;
	}
	return false;
}
/*************************************************
Function:         |ChartoWCHAR
Description:      |将字节数组转化为宽字符数组
Input:            |source     ： 欲被转化的字节数组
				   sourceSize ： 字节数组容量（非占用空间）
Return:           |WCHAR数组的指针
Others:           |source如果不以'\0'结尾可能导致返回的数组同样没有'\0'结尾
				   此方法比另一重载更加安全可靠，返回的WCHAR数组大小也是刚好足够的，缺点就是没有返回WCHAR数组的大小
*************************************************/
LPWSTR Tool::ChartoWCHAR(const char* source, int sourceSize) {
	int need = MultiByteToWideChar(CP_ACP, 0, source, sourceSize, NULL, 0);
	WCHAR* target = (WCHAR*)malloc(need * sizeof(WCHAR));
	MultiByteToWideChar(CP_ACP, 0, source, sourceSize, target, need);
	return target;
}
/*************************************************
Function:         |UTF8ToGBK
Description:      |将宽字符文本的UTF8编码转化为GBK
Input:            |strUTF8  ：源UTF8的宽字符文本
Return:           |转化后的GBK编码的宽字符文本，需要free
*************************************************/
LPWSTR Tool::UTF8ToGBK(const LPWSTR strUTF8) {
	int len = WideCharToMultiByte(CP_ACP, 0, strUTF8, -1, NULL, 0, NULL, NULL);
	LPSTR szGBK = (LPSTR)malloc(len);
	memset(szGBK, 0, len);
	WideCharToMultiByte(CP_ACP, 0, strUTF8, -1, szGBK, len, NULL, NULL);
	len = MultiByteToWideChar(CP_UTF8, 0, szGBK, -1, NULL, 0);
	LPWSTR wszGBK = (LPWSTR)malloc(len * sizeof(WCHAR) + 2);
	memset(wszGBK, 0, len * sizeof(WCHAR));
	MultiByteToWideChar(CP_UTF8, 0, szGBK, -1, wszGBK, len);
	free(szGBK);
	return wszGBK;
}
/*************************************************
Function:         |UTF8ToGBK
Description:      |将字节文本的UTF8编码转化为GBK
Input:            |strUTF8  ：源UTF8的字节文本
Return:           |转化后的GBK编码的宽字符文本，需要free
*************************************************/
LPWSTR Tool::UTF8ToGBK(const LPSTR strUTF8) {
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
	LPWSTR wszGBK = (LPWSTR)malloc(len * sizeof(WCHAR) + 2);
	memset(wszGBK, 0, len * sizeof(WCHAR));
	MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
	return wszGBK;
}
/*************************************************
Function:         |UTF8ToGBK
Description:      |将字节文本的UTF8编码转化为GBK
Input:            |strUTF8  ：源UTF8的字节文本
				   size     ：target的长度
Output:           |target   ：将被写入GBK编码的宽字符文本
*************************************************/
void Tool::UTF8ToGBK(const LPSTR strUTF8, LPWSTR target, int size) {
	MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, target, size);
}
/*************************************************
Function:         |equal
Description:      |判断两个LPWSTR（字符串）是否相等
Input:            |a     ： 第一个字符串
				   b     ： 第二个字符串
				   size  ： 包含NULL的宽字符数，视NULL为字符串结尾
Return:           |size等于0返回true。a、b相等返回true，不全等返回false
Others:           |本函数可支持其他内存类型的强转（不以NULL结尾需正确提供size），size为:占用空间/size(WCHAR)
*************************************************/
bool Tool::equal(const LPWSTR a, const LPWSTR b, UINT32 size) {
	for (UINT32 i = 0; i < size; i++) {
		if (*(a + i) == NULL&&*(b + i) == NULL) {
			return true;
		}
		if (*(a + i) != *(b + i)) {
			return false;
		}
	}
	return true;
}
/*************************************************
Function:         |nextNumIsValid
Description:      |接下来的wcharNum个宽字符文本是否有效，其实是判断是否都不为NULL
Input:            |lpwstr   ：欲被判断的宽字符文本
				   wcharNum ：接下来的要判断的长度
Return:           |如果有NULL返回false，都不为NULL返回true
*************************************************/
bool Tool::nextNumIsValid(const LPWSTR lpwstr, int wcharNum) {
	for (int i = 0; i < wcharNum; i++) {
		if (lpwstr[i] == NULL) {
			return false;
		}
	}
	return true;
}
/*************************************************
Function:         |Wchar2color
Description:      |将16进制宽字节文本转化为整数
Input:            |first  ：第一个16进制宽字符
				   second ：第二个16进制宽字符
Return:           |返回代表这两个字符对应的十进制数，返回-1为无效文本
*************************************************/
int Tool::Wchar2color(WCHAR first, WCHAR second) {
	int a;
	if (first >= TEXT('0') && first <= TEXT('9')) {
		a = (first - TEXT('0')) * 16;
	} else if (first >= TEXT('a') && first <= TEXT('f')) {
		a = (first - TEXT('a') + 10) * 16;
	} else if (first >= TEXT('A') && first <= TEXT('F')) {
		a = (first - TEXT('A') + 10) * 16;
	} else {
		return -1;
	}
	if (second >= TEXT('0') && second <= TEXT('9')) {
		a += second - TEXT('0');
	} else if (second >= TEXT('a') && second <= TEXT('f')) {
		a += second - TEXT('a') + 10;
	} else if (second >= TEXT('A') && second <= TEXT('F')) {
		a += second - TEXT('A') + 10;
	} else {
		return -1;
	}
	return a;
}

bool Tool::color2hex(LPWSTR target, COLORREF color) {
	BYTE R = (BYTE)color;
	BYTE G = (BYTE)(color >> 8);
	BYTE B = (BYTE)(color >> 16);
	int a = R / 16, b = R % 16;
	if (a > 9) {
		target[0] = 'a' + a - 10;
	} else {
		target[0] = '0' + a;
	}
	if (b > 9) {
		target[1] = 'a' + b - 10;
	} else {
		target[1] = '0' + b;
	}
	a = G / 16, b = G % 16;
	if (a > 9) {
		target[2] = 'a' + a - 10;
	} else {
		target[2] = '0' + a;
	}
	if (b > 9) {
		target[3] = 'a' + b - 10;
	} else {
		target[3] = '0' + b;
	}
	a = B / 16, b = B % 16;
	if (a > 9) {
		target[4] = 'a' + a - 10;
	} else {
		target[4] = '0' + a;
	}
	if (b > 9) {
		target[5] = 'a' + b - 10;
	} else {
		target[5] = '0' + b;
	}
	return true;
}


