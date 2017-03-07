#include "Tool.h"
/*************************************************
Function:         |CharAddChar
Description:      |�������ֽ��ı���ӵ���һ���ֽ��ı�
Input:            |targetSize  ��target�ĳ���
				   source      �����ӵ��ֽ��ı�
				   sourceSize  �����ӵ��ֽ��ı��ĳ���
Output:           |target      �������ӵ��ֽ��ı�
Return:           |���ȫ���������ˣ�����true���ռ䲻�㷵��false
*************************************************/
bool Tool::CharAddChar(char* target, int targetSize, const char* source, int sourceSize) {
	for (int i = 0; i < targetSize; i++) {
		if (target[i] == '\0') {
			int j = 0;
			for (; i < targetSize - 1 && j < sourceSize; i++, j++) {
				target[i] = source[j];
			}
			target[i] = '\0';//��֤�ַ�����β��
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
Description:      |���ֽ�����ת��Ϊ���ַ�����
Input:            |targetSize   ��target�ĳ���
				   source       ���ֽ��ı�
				   sourceSize   ���ֽ��ı��ĳ���
Output:           |target       ��ת����Ŀ��ַ��ı�
Return:           |������Ȳ���������false�����򷵻�true
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
Description:      |���ֽ�����ת��Ϊ���ַ�����
Input:            |source     �� ����ת�����ֽ�����
				   sourceSize �� �ֽ�������������ռ�ÿռ䣩
Return:           |WCHAR�����ָ��
Others:           |source�������'\0'��β���ܵ��·��ص�����ͬ��û��'\0'��β
				   �˷�������һ���ظ��Ӱ�ȫ�ɿ������ص�WCHAR�����СҲ�Ǹպ��㹻�ģ�ȱ�����û�з���WCHAR����Ĵ�С
*************************************************/
LPWSTR Tool::ChartoWCHAR(const char* source, int sourceSize) {
	int need = MultiByteToWideChar(CP_ACP, 0, source, sourceSize, NULL, 0);
	WCHAR* target = (WCHAR*)malloc(need * sizeof(WCHAR));
	MultiByteToWideChar(CP_ACP, 0, source, sourceSize, target, need);
	return target;
}
/*************************************************
Function:         |UTF8ToGBK
Description:      |�����ַ��ı���UTF8����ת��ΪGBK
Input:            |strUTF8  ��ԴUTF8�Ŀ��ַ��ı�
Return:           |ת�����GBK����Ŀ��ַ��ı�����Ҫfree
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
Description:      |���ֽ��ı���UTF8����ת��ΪGBK
Input:            |strUTF8  ��ԴUTF8���ֽ��ı�
Return:           |ת�����GBK����Ŀ��ַ��ı�����Ҫfree
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
Description:      |���ֽ��ı���UTF8����ת��ΪGBK
Input:            |strUTF8  ��ԴUTF8���ֽ��ı�
				   size     ��target�ĳ���
Output:           |target   ������д��GBK����Ŀ��ַ��ı�
*************************************************/
void Tool::UTF8ToGBK(const LPSTR strUTF8, LPWSTR target, int size) {
	MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, target, size);
}
/*************************************************
Function:         |equal
Description:      |�ж�����LPWSTR���ַ������Ƿ����
Input:            |a     �� ��һ���ַ���
				   b     �� �ڶ����ַ���
				   size  �� ����NULL�Ŀ��ַ�������NULLΪ�ַ�����β
Return:           |size����0����true��a��b��ȷ���true����ȫ�ȷ���false
Others:           |��������֧�������ڴ����͵�ǿת������NULL��β����ȷ�ṩsize����sizeΪ:ռ�ÿռ�/size(WCHAR)
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
Description:      |��������wcharNum�����ַ��ı��Ƿ���Ч����ʵ���ж��Ƿ񶼲�ΪNULL
Input:            |lpwstr   �������жϵĿ��ַ��ı�
				   wcharNum ����������Ҫ�жϵĳ���
Return:           |�����NULL����false������ΪNULL����true
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
Description:      |��16���ƿ��ֽ��ı�ת��Ϊ����
Input:            |first  ����һ��16���ƿ��ַ�
				   second ���ڶ���16���ƿ��ַ�
Return:           |���ش����������ַ���Ӧ��ʮ������������-1Ϊ��Ч�ı�
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


