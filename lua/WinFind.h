/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-28
version��          |0.1.1
Description:       |Ѱ�Ҵ���
**************************************************/
#pragma once
#include <Windows.h>
#include "Language.h"
typedef wchar_t CHAO[50];
//Ѱ����ര��
class WinFind {
public:
	WinFind(const Language* L);
	void Find();//Ѱ��һ����ര��
private:
	struct win {
		HWND hwnd = NULL;
		win* next = NULL;
	}wininfo;//��¼�Ѿ��ҹ��Ĵ���
	const Language* L;//������
	CHAO westring[8];//���洰�ڱ���
};