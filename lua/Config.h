/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-05
version��          |0.0.0
Description:       |��ȡ���á��������Եȵ�
**************************************************/
#pragma once
#include <Windows.h>
class Config
{
public:
	Config();
	//WCHAR* initialize();

private:
	//char *GetDLLPath();
	const char* fileSet = "YDColorizerConfig.ini";//�����ļ���
	const LPCWSTR globalSet = TEXT("Application");//ȫ��������
	const LPCWSTR languageSet = TEXT("Language");//���԰汾
	const char* defaultSet = "[Application]\nLanguage = 0\n; ����, 0->��������, 1->��������";
	//Ĭ�������ļ�����
	UINT language;
};