/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-28
version��          |0.0.1
Description:       |����ʾ�����й�
**************************************************/
#pragma once
#include <Windows.h>
//���������
class Language {
public:
	Language(int language);//��������
	LPCWSTR lessDLL;//ȱ��DLL
	LPCWSTR error;//����
	LPCWSTR CreateRichEditViewerror;//�������ı��༭��ʧ��
	LPCWSTR CreateWindowError;//��������ʧ��
	LPCWSTR gainText;//��ȡ�ı�
	LPCWSTR applyText;//Ӧ���ı�
	LPCWSTR colorAlarm;//��ɫ����
	LPCWSTR alarm;//����
};