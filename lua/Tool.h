/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-28
version��          |0.2.1
Description:       |��װһЩ���ʹ�õĺ���
**************************************************/
#pragma once
#include <Windows.h>
//�빤���й�
class Tool {
public:
	bool CharAddChar(char* target, int targetSize, const char* source, int sourceSize);//���ֽ��ı����
	bool ChartoWCHAR(LPWSTR target, int targetSize, const char* source, int sourceSize);//�ֽ��ı������ֽ��ı���target��С��Ҫ���㣩
	LPWSTR ChartoWCHAR(const char* source, int sourceSize);//�ֽ��ı������ֽ��ı������ص�ռ�ô�С�պ����㣩
	LPWSTR UTF8ToGBK(const LPWSTR strUTF8);//�ֽ��ı�ת��ΪUTF8����
	LPWSTR UTF8ToGBK(const LPSTR strUTF8);//���ֽ��ı�ת��ΪUTF8����
	void UTF8ToGBK(const LPSTR strUTF8, LPWSTR target, int size);//���ֽ��ı�ת��ΪUTF8���루����������ڴ棩
	bool equal(const LPWSTR a, const LPWSTR b, UINT32 size);//�жϣ����ֽ��ı����Ƿ�ȫ��
	bool nextNumIsValid(const LPWSTR lpwstr, int wcharNum);//��������wcharNum�����ֽ��ı��Ƿ���Ч
	int Wchar2color(WCHAR first, WCHAR second);//�����ֽ��ı�ת��Ϊ����
	bool color2hex(LPWSTR target,COLORREF color);//����ɫת��Ϊ�ı�������6�ֽ�
};