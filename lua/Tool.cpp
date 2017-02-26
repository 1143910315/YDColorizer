#include "Tool.h"
bool Tool::CharAddChar(char* target, int targetSize, const char* source, int sourceSize)
{
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

bool Tool::ChartoWCHAR(LPWSTR target, int targetSize, const char* source, int sourceSize)
{
	int need = MultiByteToWideChar(CP_ACP, 0, source, sourceSize, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, source, sourceSize, target, targetSize);
	if (need <= targetSize)
	{
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
LPWSTR Tool::ChartoWCHAR(const char* source, int sourceSize)
{
	int need = MultiByteToWideChar(CP_ACP, 0, source, sourceSize, NULL, 0);
	WCHAR* target = (WCHAR*)malloc(need * sizeof(WCHAR));
	MultiByteToWideChar(CP_ACP, 0, source, sourceSize, target, need);
	return target;
}
LPWSTR Tool::UTF8ToGBK(const LPWSTR strUTF8)
{
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
LPWSTR Tool::UTF8ToGBK(const LPSTR strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
	LPWSTR wszGBK = (LPWSTR)malloc(len * sizeof(WCHAR) + 2);
	memset(wszGBK, 0, len * sizeof(WCHAR));
	MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
	return wszGBK;
}
bool Tool::equal(const LPWSTR a, const LPWSTR b, UINT32 size)
{
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
bool Tool::nextNumIsValid(const LPWSTR lpwstr, int wcharNum)
{
	for (int i = 0; i < wcharNum; i++)
	{
		if (lpwstr[i] == NULL) {
			return false;
		}
	}
	return true;
}
int Tool::Wchar2color(WCHAR first, WCHAR second)
{
	int a;
	if (first >= TEXT('0') && first <= TEXT('9'))
	{
		a = (first - TEXT('0')) * 16;
	}
	else if (first >= TEXT('a') && first <= TEXT('f'))
	{
		a = (first - TEXT('a') + 10) * 16;
	}
	else if (first >= TEXT('A') && first <= TEXT('F'))
	{
		a = (first - TEXT('A') + 10) * 16;
	}
	else {
		return -1;
	}
	if (second >= TEXT('0') && second <= TEXT('9'))
	{
		a += second - TEXT('0');
	}
	else if (second >= TEXT('a') && second <= TEXT('f'))
	{
		a += second - TEXT('a') + 10;
	}
	else if (second >= TEXT('A') && second <= TEXT('F'))
	{
		a += second - TEXT('A') + 10;
	}
	else {
		return -1;
	}
	return a;
}
/*
string UTF8ToGBK(const std::string& strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
	unsigned short * wszGBK = new unsigned short[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUTF8.c_str(), -1, wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP,0, wszGBK, -1, szGBK, len, NULL, NULL);
	//strUTF8 = szGBK;
	std::string strTemp(szGBK);
	delete[]szGBK;
	delete[]wszGBK;
	return strTemp;
	}*/