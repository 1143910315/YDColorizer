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
	//WCHAR* initialize();
	int GetLanguage();
	LPWSTR WESTRING_COD_TYPE_STRING();// = �ַ���
	LPWSTR WESTRING_UE_DLG_EDITVALUE();//=�༭��λֵ - %s
	LPWSTR WESTRING_IE_DLG_EDITVALUE();//=�༭��Ʒֵ - %s
	LPWSTR WESTRING_AE_DLG_EDITVALUE();//=�༭����ֵ - %s
	LPWSTR WESTRING_FE_DLG_EDITVALUE();//=�༭Ч��ֵ - %s
	LPWSTR WESTRING_BE_DLG_EDITVALUE();//=�༭���ƻ���ֵ - %s
	LPWSTR WESTRING_DE_DLG_EDITVALUE();//=�༭װ����ֵ - %s
	LPWSTR WESTRING_GE_DLG_EDITVALUE();//=�༭�Ƽ�ֵ - %s
private:
	//char *GetDLLPath();

	const LPCWSTR globalSet = TEXT("Application");//���������_����
	const LPCWSTR languageSet = TEXT("Language");//������԰汾_����
	const LPCWSTR lpAppName = TEXT("WorldEditStrings");//WorldEditStrings.txt_����
	//********************************����ΪWorldEditStrings.txt_����
	const LPCWSTR WESTRING_COD_TYPE_STRINGstr = TEXT("WESTRING_COD_TYPE_STRING");//�ַ���
	const LPCWSTR WESTRING_UE_DLG_EDITVALUEstr = TEXT("WESTRING_UE_DLG_EDITVALUE");//�༭��λֵ - %s
	const LPCWSTR WESTRING_IE_DLG_EDITVALUEstr = TEXT("WESTRING_IE_DLG_EDITVALUE");//�༭��Ʒֵ - %s
	const LPCWSTR WESTRING_AE_DLG_EDITVALUEstr = TEXT("WESTRING_AE_DLG_EDITVALUE");//�༭����ֵ - %s
	const LPCWSTR WESTRING_FE_DLG_EDITVALUEstr = TEXT("WESTRING_FE_DLG_EDITVALUE");//�༭Ч��ֵ - %s
	const LPCWSTR WESTRING_BE_DLG_EDITVALUEstr = TEXT("WESTRING_BE_DLG_EDITVALUE");//�༭���ƻ���ֵ - %s
	const LPCWSTR WESTRING_DE_DLG_EDITVALUEstr = TEXT("WESTRING_DE_DLG_EDITVALUE");//�༭װ����ֵ - %s
	const LPCWSTR WESTRING_GE_DLG_EDITVALUEstr = TEXT("WESTRING_GE_DLG_EDITVALUE");//�༭�Ƽ�ֵ - %s
	//********************************
/********************************Ĭ�������ļ�����
[Application]
Language = 0
; ����, 0->��������, 1->��������"
	********************************/
};