/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-07
version��          |0.0.0
Description:       |Ѱ�Ҵ���
**************************************************/
#pragma once
#include <Windows.h>
class WinFind
{
public:
	WinFind();

	//Config();
	//WCHAR* initialize();
	/*bool CharAddChar(char* target, int targetSize, const char* source, int sourceSize);
	bool ChartoWCHAR(WCHAR* target, int targetSize, const char* source, int sourceSize);
	WCHAR* ChartoWCHAR(const char* source, int sourceSize);*/
private:
	//********************************����ΪWorldEditStrings.txt_����
	LPCWSTR WESTRING_COD_TYPE_STRINGstr;//�ַ���
	LPCWSTR WESTRING_UE_DLG_EDITVALUEstr;//�༭��λֵ - %s
	LPCWSTR WESTRING_IE_DLG_EDITVALUEstr;//�༭��Ʒֵ - %s
	LPCWSTR WESTRING_AE_DLG_EDITVALUEstr;//�༭����ֵ - %s
	LPCWSTR WESTRING_FE_DLG_EDITVALUEstr;//�༭Ч��ֵ - %s
	LPCWSTR WESTRING_BE_DLG_EDITVALUEstr;//�༭���ƻ���ֵ - %s
	LPCWSTR WESTRING_DE_DLG_EDITVALUEstr;//�༭װ����ֵ - %s
	LPCWSTR WESTRING_GE_DLG_EDITVALUEstr;//�༭�Ƽ�ֵ - %s
   //********************************
   //char *GetDLLPath();
   //const char* fileSet = "YDColorizerConfig.ini";//�����ļ���
   //const LPCWSTR globalSet = TEXT("Application");//ȫ��������
   //const LPCWSTR languageSet = TEXT("Language");//���԰汾
   //const char* defaultSet = "[Application]\nLanguage = 0\n; ����, 0->��������, 1->��������";
   //Ĭ�������ļ�����
   //UINT language;


/*
		' ��528654�� | ���༭��λֵ - �ַ����� | ��#32770��
		' ��2296770�� | ������༭���� | ��#32770��

		' ��725440�� | ���ַ����� | ��#32770��
		' ��4131942�� | ������ ������ | ��#32770��
		' ��2101072�� | �������༭���� | ��#32770��

		' Edit*/

};